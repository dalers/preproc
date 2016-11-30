#define _WITH_GETLINE

#include <stdio.h>
#include <stdlib.h>
#include <malloc_np.h>

#define DEBUG 0

int help()
{
  printf("\n");
  printf("preproc - moneta pre-processor\n");
  printf("version 0.0.0\n");
  printf("\n");
  printf("Usage:\n");
  printf("preproc < [infname]\n");
  printf("\n");
  return(0);
}

int main()
{
  char *line = NULL;            // input line (pointer to)
  size_t linecap = 0;           // maximum line length (adjusted as necessary)
  ssize_t linelen;              // set to input line length

  int numfields = 0;            // number of fields read from data record
  int numrecords = 0;           // total number of sample data records
  int index;                    // record index
  int prev_index = -1;          // previous record index - for continuity test
  float bx, by, bz, degc;       // record data fields
  
  float bx_min, bx_max, bx_avg, bx_sum = 0; // Bx statistics
  float by_min, by_max, by_avg, by_sum = 0; // By statistics
  float bz_min, bz_max, bz_avg, bz_sum = 0; // Bz statistics
  float degc_min, degc_max, degc_avg, degc_sum = 0; // degc (temperature) statistics

  int state = 0;                // 0 = initial, 1 = reading header,  2= reading body

  if (DEBUG)
  {
    printf("PREPROC - DEBUG ENABLED\n");
    help();
  }
  
  while ((linelen = getline(&line, &linecap, stdin)) > 0)    // read first line - assumed to be header (also required)
  {
    state = 1; // reading header
    
    if (DEBUG)
    {
    printf("DEBUG: START OF HEADER\n");
    fwrite(line, linelen, 1, stdout); // echo first line to output
    printf("DEBUG: line length: %i\n", linelen);
    }
    
    printf("\n");
    printf("preproc - moneta pre-processor\n");
    printf("version 0.0.0\n");
    printf("\n");

    printf("File Header\n");
    while ((linelen = getline(&line, &linecap, stdin)) > 2)  // read lines from header until blank line ends section
    {
      printf("  "); fwrite(line, linelen, 1, stdout); // echo header line to output
    }

    printf("\n");
    printf("Reading data records...\n");
    printf("\n");
    
    if (DEBUG)
      printf("DEBUG: END OF HEADER\n");    
  
    state = 2; // reading body
    if (DEBUG)
      printf("START OF BODY\n");
  
    while ((linelen = getline(&line, &linecap, stdin)) > 0)  // read line of body until end of file
    {
      numrecords = numrecords + 1;
      numfields = sscanf(line, "%i,%f,%f,%f,%f", &index, &bx, &by, &bz, &degc);  // parse line
      
      if (DEBUG)
      {
        printf("DEBUG: "); fwrite(line, linelen, 1, stdout); // echo line read
        printf("DEBUG:   Recordnum: %i, Line length: %i, Fields Parsed = %i\n", numrecords, linelen, numfields);
        printf("DEBUG:   Index = %i, Bx = %f, By = %f, Bz = %f, Temp = %f\n", index, bx, by, bz, degc);
      }
      
      // TODO add data integrity tests
      // - correct number of fields read from record
      // - no unparsed data remains in input line
      // - index is continuous and sequential
      
      if (index - prev_index != 1)
        printf("ERROR: INDEX BREAK (Current index = %i, Previous index = %i)\n", index, prev_index);

      if (numrecords == 1) // boostrap statistics
      {
        bx_min = bx; bx_max = bx;
        by_min = by; by_max = by;
        bz_min = bz; bz_max = bz;
        degc_min = degc; degc_max = degc;
      }          
 
      if (bx < bx_min) bx_min = bx;            // Bx statistics
      if (bx > bx_max) bx_max = bx;
      bx_sum = bx_sum + bx;
      
      if (by < by_min) by_min = by;            // By statistics
      if (by > by_max) by_max = by;
      by_sum = by_sum + by;
      
      if (bz < bz_min) bz_min = bz;            // Bz statistics
      if (bz > bz_max) bz_max = bz;
      bz_sum = bz_sum + bz;
      
      if (degc < degc_min) degc_min = degc;    // degc (temperature) statistics
      if (degc > degc_max) degc_max = degc;
      degc_sum = degc_sum + degc;
      
      prev_index = index;
    }

    if (DEBUG)
      printf("DEBUG: END OF BODY\n");
  
    if (numrecords > index + 1)
      printf("ERROR: TOO MANY RECORDS (Final index = %i, Number of records = %i)\n", index, numrecords);

  }

  /* output statistics */
  printf("\n");
  printf("Data records processed: %i\n", numrecords);
  printf("\n");
  printf("Bx min/avg/max: %f\t%f\t%f\n", bx_min, (bx_sum / numrecords), bx_max);
  printf("By min/avg/max: %f\t%f\t%f\n", by_min, (by_sum / numrecords), by_max);
  printf("Bz min/avg/max: %f\t%f\t%f\n", bz_min, (bz_sum / numrecords), bz_max);
  printf("Temp min/avg/max: %f\t%f\t%f\n", degc_min, (degc_sum / numrecords), degc_max);
  printf("\n");
  
  free(line);
  return(0);
}
