/* rev.  8/98*/
/* readv4wt.cc  reads the v4 to IT weight files and generate a new
weight file, where the weight is the original weight*scale

e.g. If we want to generate eg4c to exgt (left v4 excitatory, corner 
to left IT excitatory), the original weight file is ev4c.wt, and scale = 0.75
at the command line, type:
readv4wt ev4c.wt eg4c exgt 0.75

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define maxlen 80

int main (int argc, char **argv)
{
  FILE *infile, *outfile;
  char Outfile[maxlen],temp[maxlen];
  int inchar;
  float scale,weight;

  if(argc != 5)
    {
      printf("enter\n","readv4wt file_to_be_copied originating_set destination_set scale\n");
      exit(0);
    }

  if( (infile = fopen(argv[1], "r")) == NULL)
    {
      printf("can't open %s\n", argv[1]);
      exit(0);
    }

  strcpy(Outfile, argv[2]);
  strcat(Outfile,argv[3]);
  strcat(Outfile,".w");
  if( (outfile = fopen(Outfile, "w")) == NULL)
    {
      printf("can't open %s\n", Outfile);
      exit(0);
    }

  scale = atof(argv[4]);

  fprintf(outfile,"Connect(%s,%s) {\n",argv[2],argv[3]);
  fgets(temp, maxlen,infile);

  while((inchar = getc(infile)) != EOF)
    {
      ungetc(inchar,infile);
      while( ( (inchar = getc(infile)) != ']') && (inchar != EOF) ) 
	{
	  fprintf(outfile,"%c",inchar);
	}
      if(inchar != EOF)
	{
	  fprintf(outfile,"%c ",inchar);
	  fscanf(infile, "%f", &weight);
	  fprintf(outfile,"%f",weight*scale);
	}/*end of if inchar != EOF, writing weights*/
    }/*end of while inchar !=EOF*/

  fclose(infile);
  fclose(outfile);
}
