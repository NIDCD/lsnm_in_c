/* mklgns.cc  rev. 7/10/98
   make  a random input pattern for the right brain's LGNS. 
   Random numbers are generated for all elements of
   the input matrix.  The max value for random number is
   entered in the command line.  e.g if we want all the inputs to be
   between 0 and 0.3, we enter the following at the prompt:
   mklgns 0.3
   if we want to enter a seed, say 679
   >mklgns 0.3 679
   If no seed is entered, system clock will be used as seed
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main(int argc, char **argv)
{
  FILE *outfile;
  int i, j, length = 9,square;
  long seed = time(NULL);
  float scale = 0.3;
  if(argv[1] != NULL)
    scale = atof(argv[1]);
  if((argv[2] != NULL))
    seed = (int)atoi(argv[2]);

  srand48(seed);
  square = length*length;
  outfile = fopen("lgns.inp","w");
  fprintf(outfile,"set  (LGNs,  %d)        %% Turn on LGN,  the Input\n\n",square);  
  fprintf(outfile,"{\nNode activation  {ALL 0.0 }\n\nNode activation  {\n");

  
  for(i = 1; i <= length; i++)
    {
      for(j = 1; j <= length; j++)
	{
	  fprintf(outfile,"([%d,%d]   %5.3f) ",i,j,drand48()*scale);
	}
      fprintf(outfile,"\n");
    }
  fprintf(outfile,"}\n");
  fclose(outfile);
}
