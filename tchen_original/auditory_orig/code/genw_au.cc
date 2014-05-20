/* genw_au.cc  5/03 BH (modified from genw.cc)
produces netgenC_au.in to be used by netgenC_au

Define capacity as the %strength with respect to the original 
connection strength.  It is a command line input so we can incorporate
it in a shell script generator for batch files.  It is entered
as an integer. e.g. if we want the capacity to be 80%, at
the system prompt enter:
genw 80
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
char origin[maxstring], dest[maxstring], Infile[maxline],Outfile[maxline];
int num_pairs, i;
float capacity;

  char *BASE= "/home/bhguest/brent/auditory/code/";

  strcpy(Infile,BASE);
  strcpy(Outfile,BASE);
  strcat(Infile,"genw_au.in");
  strcat(Outfile,"netgenC_au.in");

if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n",Infile);
      exit(0);
    }
outfile = fopen(Outfile,"w");
if(argv[1] != NULL)
  capacity = atof(argv[1])/100.0;
else 
{
  capacity = 0.0;
  printf("you need to enter capacity in command line\n");
}
fscanf(infile,"%d",&num_pairs);
fprintf(outfile,"%d\n", num_pairs);
for(i=0; i< num_pairs; i++)
   {
     fscanf(infile,"%s %s",origin, dest);
     fprintf(outfile,"%s %s  %g\n",origin, dest,capacity);
   }
fclose(infile);
fclose(outfile);

}


