/*
  mkcatout.cc
  Written by:  B. Warner
  07/02/03

  When using mkbatchb.cc, which rebuilds cross-hemisphere connections between
  trials (i.e. stimulus pairs), a pethi sequence file is needed for each
  trial.  Thus, a new set of .out files are generated for each pethi file used.
  These are saved in the output directory in the following hierarchy.
  
  outputdir/subj/b(attn levels)/trial

  mkcatout.cc makes the shell script catout, that systematically traverses the
  trials directories, concatenates corresponding output files, saves the
  results in the attn level directory and rezips everything.

  uses mkcatout.in

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define maxline 80

int main()
{
  FILE *infile, *outfile;
  int i,j,k,attni,n;
  int n_trials,n_subjects,start_a,end_a,inc_a,num_a;
  char Infile[maxline], whereis[maxline], *regions[22];

  char *BASE= "/home/bhguest/brent/visual";

  strcpy(Infile,BASE);
  strcat(Infile,"/code/mkcatout.in");

  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }
  
  outfile = fopen("catout","w");

  fscanf(infile,"%s",whereis);
  fscanf(infile,"%d %d %d %d %d",&n_subjects,&n_trials,&start_a,&end_a,&inc_a);
  
  if(inc_a == 0)
    num_a = 1;
  else
    num_a = (end_a - start_a)/inc_a + 1;

  regions[0] = "efd1.out";
  regions[1] = "efd2.out";
  regions[2] = "eg1h.out";
  regions[3] = "eg1v.out";
  regions[4] = "eg4c.out";
  regions[5] = "eg4h.out";
  regions[6] = "eg4v.out";
  regions[7] = "egd1.out";
  regions[8] = "egd2.out";
  regions[9] = "egfr.out";
  regions[10] = "egfs.out";
  regions[11] = "ev1h.out";
  regions[12] = "ev1v.out";
  regions[13] = "ev4c.out";
  regions[14] = "ev4h.out";
  regions[15] = "ev4v.out";
  regions[16] = "exfr.out";
  regions[17] = "exfs.out";
  regions[18] = "exgt.out";
  regions[19] = "exss.out";
  regions[20] = "ggns.out";
  regions[21] = "lgns.out";


  /*start of output*/
  fprintf(outfile,"#\n#\n#\n");
  fprintf(outfile,"cd %s\n",whereis);

  for(i=1; i<=n_subjects; i++)
    {
      fprintf(outfile,"cd subj%d\n",i);
      fprintf(outfile,"gunzip b*/trial*/*.out.gz\n");
      for(j=0; j<num_a; j++)
	{
	  attni = start_a + inc_a*j;
	  fprintf(outfile,"cd b%d\n",attni);
	  fprintf(outfile,"echo subject %d, attn %d\n",i,attni);
	  for(k=0; k<22; k++)
	    {
	      for(n=1; n<=n_trials; n++)
		{
		  if(n == 1)
		    fprintf(outfile,"cat trial%d/%s ",n,regions[k]);
		  else if(n == n_trials)
		    fprintf(outfile,"trial%d/%s > %s\n",n,regions[k],regions[k]);
		  else
		    fprintf(outfile,"trial%d/%s ",n,regions[k]);
		}
	    }
	  fprintf(outfile,"gzip trial*/*.out\n");
	  fprintf(outfile,"cd ..\n");
	}
      fprintf(outfile,"gzip b*/*.out\n");
      fprintf(outfile,"cd ..\n");
    }

  fprintf(outfile,"cd %s\n",BASE);


fclose(infile);
fclose(outfile);

}
  
