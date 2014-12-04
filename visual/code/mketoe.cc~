/* mketoe.cc  rev. 8/98
  make the etoe files for left side, based on the right side

  link with namechange.o
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define namelen 16
#define unitlen 4
#define maxline 80

int namechange(char *name);

void main()
{
  FILE *infile, *outfile;
  char fname[namelen],line[maxline];
  int inchar;
  int i, t=1;

  char Infile[maxline];

  char *BASE= "/home/bhguest/brent/visual";

  strcpy(Infile,BASE);
  strcat(Infile,"/weights/right/rightetoe.txt");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

  outfile = fopen("leftetoe.txt","w");

  while(t )
    {
      fgets(line,maxline,infile);
      if( (line[0] == 'c') || (line[0] == 'C'))
	{
	  for(i = 0; i < unitlen; i++)
	    {
	      fname[i] = tolower(line[i+8]);
	    }
	  fname[i] = '\0';
	  namechange(fname);
	  for(i = 0; i < unitlen; i++)
	    {
	      line[i+8] = fname[i];
	      line[i+14] = fname[i];
	    }
	}

      fprintf(outfile,"%s",line);
      if( (inchar = getc(infile)) == EOF)
	t = 0;
      else ungetc(inchar,infile);
    }

  fclose(infile);
  fclose(outfile);
}
