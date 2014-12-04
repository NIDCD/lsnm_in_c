/* makews.cc rev.  8/98*/
/* make the .ws files for left side, based on the list of .ws files for the
  right side

  input file is makews.in, which contains the list of all the 
  right side .ws file

  the makews.in file is generated by copy the screen in weights/right
  after we used the command ls *.ws
  link with namechange.o, dows.o
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define namelen 16
#define unitlen 4
#define maxline 80

int namechange(char *name);
void dows(FILE * infile, FILE* outfile);

int main ()
{
  FILE *infile, *readfile, *outfile;
  char fname[namelen],newfname[namelen],part[namelen],line[maxline];
  int inchar;
  int i, j, n,t=1;

  char Infile[maxline];

  const char *BASE= getenv("LSNM");

  strcpy(Infile,BASE);
  strcat(Infile,"code/makews.in");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

  while(t )
    {
      fscanf(infile,"%s",fname);
      fgets(line,maxline,infile);

      if( (readfile = fopen(fname, "r")) == NULL)
	{
	  printf("can't open %s\n",fname);
	  exit(0);
	}
      for(i = 0; i < 2; i++)
	{
	  n= i*unitlen;
	  for(j = 0; j < unitlen; j++)
	    part[j] = fname[n + j];
	  namechange(part);
	  for(j = 0; j < unitlen; j++)
	    newfname[n + j] = part[j];
	}
      j = n+unitlen;
      while(fname[j] != '\0')
	{
	  newfname[j] = fname[j];
	  j++;
	}
      newfname[j] = '\0';
      outfile = fopen(newfname,"w");
      dows(readfile,outfile);
      fclose(readfile);
      fclose(outfile);

      while( (inchar =  getc(infile)) == ' ');
      ungetc(inchar,infile);
      if( (inchar = getc(infile)) == EOF)
	{
	  fclose(infile);
	  t = 0;
	}
      else
	ungetc(inchar,infile);

    }/* end of while inchar != EOF*/

}

