/*
  mkcatout_au.cc
  Written by:  B. Warner
  updated for auditory model 07/21/03

  When using mkbatchb.cc, which rebuilds cross-hemisphere connections between
  trials (i.e. stimulus pairs), a pethi sequence file is needed for each
  trial.  Thus, a new set of .out files are generated for each pethi file used.
  These are saved in the output directory in the following hierarchy.
  
  outputdir/subj/b(attn levels)/trial

  mkcatout.cc makes the shell script catout, that systematically traverses the
  trials directories, concatenates corresponding output files, saves the
  results in the attn level directory and rezips everything.

  uses mkcatout_au.in

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
  int num_regions = 22;
  char Infile[maxline], whereis[maxline], *regions[num_regions];

  const char *BASE= (char*)"$LSNM";

  strcpy(Infile,BASE);
  strcat(Infile,"/code/mkcatout_au.in");

  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }
  
  outfile = fopen("catout_au","w");

  fscanf(infile,"%s",whereis);
  fscanf(infile,"%d %d %d %d %d",&n_subjects,&n_trials,&start_a,&end_a,&inc_a);
  
  if(inc_a == 0)
    num_a = 1;
  else
    num_a = (end_a - start_a)/inc_a + 1;

  regions[0] = (char*)"efd1.out";
  regions[1] = (char*)"efd2.out";
  regions[2] = (char*)"eg1d.out";
  regions[3] = (char*)"eg1u.out";
  regions[4] = (char*)"eg2c.out";
  regions[5] = (char*)"eg2d.out";
  regions[6] = (char*)"eg2u.out";
  regions[7] = (char*)"egd1.out";
  regions[8] = (char*)"egd2.out";
  regions[9] = (char*)"egfr.out";
  regions[10] = (char*)"egfs.out";
  regions[11] = (char*)"ea1d.out";
  regions[12] = (char*)"ea1u.out";
  regions[13] = (char*)"ea2c.out";
  regions[14] = (char*)"ea2d.out";
  regions[15] = (char*)"ea2u.out";
  regions[16] = (char*)"exfr.out";
  regions[17] = (char*)"exfs.out";
  regions[18] = (char*)"egtg.out";
  regions[19] = (char*)"estg.out";
  regions[20] = (char*)"gmgn.out";
  regions[21] = (char*)"mgns.out";


  /*start of output*/
  fprintf(outfile,"#\n#\n#\n");
  fprintf(outfile,"cd %s\n",whereis);

  for(i=1; i<=n_subjects; i++)
    {
      fprintf(outfile,"cd subj%d\n",i);
      for(j=0; j<num_a; j++)
	{
	  attni = start_a + inc_a*j;
	  if (attni > 9)
	    {
	      fprintf(outfile,"cd b%d\n",attni);
	    }
	  else 
	    {
	      fprintf(outfile,"cd b%s%d\n","0",attni);
	    }
	  fprintf(outfile,"echo subject %d, attn %d\n",i,attni);
	  fprintf(outfile,"mkdir catout\n");
	  fprintf(outfile,"gunzip trial*/*.gz\n");
	  for(k=0; k<num_regions; k++)
	    {
	      for(n=1; n<=n_trials; n++)
		{
		  if(n == 1)
		    fprintf(outfile,"cat trial%d/%s ",n,regions[k]);
		  else if(n == n_trials)
		    fprintf(outfile,"trial%d/%s > catout/%s\n",n,regions[k],regions[k]);
		  else
		    fprintf(outfile,"trial%d/%s ",n,regions[k]);
		}
	    }
	  fprintf(outfile,"gzip trial*/*.out\n");
	  fprintf(outfile,"gzip catout/*.out\n");
	  fprintf(outfile,"cd ..\n");
	}
      fprintf(outfile,"cd ..\n");
    }

  fprintf(outfile,"cd %s\n",BASE);


fclose(infile);
fclose(outfile);

}
  
