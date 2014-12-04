/*dows.cc   rev.  6/4/98*/
/* make the .ws file for left side, based on the .ws files for the
  right side

  called by makews to write out each .ws file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define namelen 16
#define unitlen 4

extern int namechange (char *name);

void dows (FILE* readfile, FILE* outfile)
{
  char name[unitlen];
  int inchar;
  int i;


  for(i=0; i< 2; i++)
    {
      while( (inchar = getc(readfile)) == ' ');
      ungetc(inchar,readfile);
      fscanf(readfile,"%s",name);

      namechange(name);
      fprintf(outfile,"%s ",name);
    }

  while( (inchar = getc(readfile)) != EOF)
    fprintf(outfile,"%c",inchar);

}/*end of while inchar !=EOF*/




