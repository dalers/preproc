#define _WITH_GETLINE
#include <stdio.h>

#define MAXLINE 1000          // maximum data file line length

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
  int len;                      // current line length
  int max;                      // maximum length seen so far
  char line[MAXLINE];           // current input line

  int sample;                   // holds sample index read from data file
  float bx, by, bz, temp;       // holds sample values read from data file

  ssize_t byteCount;

  help();                       // output usage for fun

  while ((byteCount = getline(line, sizeof(line))) > 0) {
    if (sscanf(line, "%i ; %f ; %f ; %f ; %f", &sample, &bx, &by, &bz, &temp) == 5)
      printf("valid data record: %s\n", line);
    else
      printf("invalid: %s\n", line);
  }

  return(0);
}
 
