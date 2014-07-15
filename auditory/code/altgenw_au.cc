/* altgenw_au.cc

written 07/21/03 by B. Warner

produces netgenC_au.in to be used by netgenC_au

Define capacity as the %strength with respect to the original 
connection strength.  It is a command line input so we can incorporate
it in a shell script generator for batch files.  It is entered
as an integer. e.g. if we want the capacity to be 80%, at
the system prompt enter:
genw 80 75 100 94 etc....

This program can receive multiple arguments in the command line
corresponding to multiple region-to-region connections as specified
in the .in file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define maxstring 15
#define maxline 80

int main(int argc,char **argv)
{
  FILE *infile, *outfile;
  char origin[maxstring],dest[maxstring],Infile[maxline],Outfile[maxline];
  int num_pairs, i;
  float capacity[40];

  const char *BASE = getenv("LSNM");

  strcpy(Infile,BASE);
  strcpy(Outfile,BASE);
  strcat(Infile,"code/altgenw_au.in");
  strcat(Outfile,"code/netgenC_au.in");

  if((infile=fopen(Infile,"r")) == NULL)
    {
      printf("can't open %s\n",Infile);
      exit(0);
    }
  
  outfile = fopen(Outfile,"w");
  
  for(i=1; i<argc; i++)
    {
      if(argv[i] != NULL)
	capacity[i] = atof(argv[i])/100.0;
      else
	{
	  capacity[i] = 0.0;
	  printf("you need to enter the capacity in the command line for each source/destination pair\n");
	}
    }
  fscanf(infile,"%d",&num_pairs);
  fprintf(outfile,"%d\n",num_pairs);
  for(i=0; i<num_pairs; i++)
    {
      fscanf(infile,"%s %s",&origin,&dest);
      fprintf(outfile,"%s %s %g\n",origin,dest,capacity[i+1]);
    }
  fclose(infile);
  fclose(outfile);
}
