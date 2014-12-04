/* mklist.cc rev.  8/98*/
/* make the leftlist.txt file for left side, based on the rightlist.txt
  of the right side.  Use "namechange" to switch the region labels

  use global delete to delete right/ in every line before we run the code.
  after the change,use global paste to put in left/ where right/ was.
 
  link with namechange.o
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define namelen 16
#define unitlen 4
#define maxline 80

int namechange(char *name);

int main ()
{
  FILE *infile,  *outfile;
  char fname[namelen],part[namelen],line[maxline];
  char *cs, *cs1;
  int inchar;
  int i, j, n,t=1;

  char Infile[maxline];

  char *BASE= "/home/bhguest/brent/visual";

  strcpy(Infile,BASE);
  strcat(Infile,"/weights/right/rightlist.txt");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

  outfile = fopen("leftlist.txt","w");
  while(t)
    {
      fgets(line,maxline,infile);
      
      if((cs = strstr(line, "/")) != NULL)
	{
	  cs++;
	  cs1 = cs;

	  for(i = 0; i < unitlen*2; i++)
	    {
	      fname[i] = *cs1;
	      cs1++;
	    }
	  for(i = 0; i < 2; i++)
	    {
	      n= i*unitlen ;
	      for(j = 0; j < unitlen; j++)
		part[j] = fname[ n + j];
	      namechange(part);
	      for(j = 0; j < unitlen; j++)
		fname[n + j] = part[j];
	    }
	  for(i = 0; i < unitlen*2; i++)
	    {
	      *cs =fname[i];
	      cs++;
	    }
	}

      fprintf(outfile,"%s", line);

      if( (inchar = getc(infile)) == EOF)
	{
	  t = 0;
	  fclose(infile);
	  fclose(outfile);
	}
      else
	ungetc(inchar,infile);
    }/* end of while(t)  */
}
