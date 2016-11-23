#include <stdio.h>
// #include <ctype.h>
// #include <stdlib.h>

FILE *fp;

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
  int c;                        // holds char read from data file
  int sample;                   // holds sample index read from data file
  float bx, by, bz, temp;       // holds sample values read from data file

  help();                       // output usage for fun

  while ((c = getchar()) != EOF)
    putchar(c);
  return(0);


/* NEW WAY FROM K&R
while (getline(line, sizeof(line)) > 0) {
  if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
    printf("valid: %s\n", line);
  else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
    printf("valid: %s\n", line);
  else
    printf("invalid: %s\n", line);
}
*/

/* OLD WAY
  char filename[12] = "test.log";       // holds input data filename
  int inChar;                           // character read from input data file

  if ((fp=fopen(filename, "r"))==NULL)
  {
    printf("\n\n*** data file does not exist ***\n");
    exit(1);                            // exits program with error condition
  }

  inChar = getc(fp);                    // reads first character from data file
  while (inChar != EOF)
  {
    putchar(inChar);
    inChar = getc(fp);
  }
  fclose(fp);
  return(0);
*/

} 

