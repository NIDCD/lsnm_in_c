/* rev.  8/98*/
/* addwt.cc  
This code is used to get the total weights of a weight file when we want
to compute the afferent proportions from different origins.

e.g. If we want to compute the summed weights in a weight file named ev4c.wt
at the promp type:
addwt ev4c.wt

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



int main (int argc, char **argv)
{
  FILE *infile;
  int inchar;
  float weight,sum = 0;

  if( (infile = fopen(argv[1], "r")) == NULL)
    {
      printf("can't open %s\n", argv[1]);
      exit(0);
    }


  while( (inchar = getc(infile)) != EOF)
    {
      ungetc(inchar,infile);
      while( ((inchar = getc(infile)) != ']') && (inchar != EOF)); 
      if(inchar == ']')
	{
	  fscanf(infile,"%f",&weight);
	  sum += weight;
	}/*end of if inchar = ']', writing weights*/
      else
	ungetc(inchar,infile);
    }/*end of while !=EOF*/
  printf("sum = %g\n",sum);
  fclose(infile);

}
