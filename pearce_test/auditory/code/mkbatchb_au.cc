/*
  written by:  B. Warner
  07/21/03

  mkbatchb_au.cc, generates shell script to run au_sim1

  1. changes connection strengths for multiple regions (e to e only)
  in right hemisphere, constituting one subject.

  2. steps through attention levels for each subject

  3. recreates cross-connections between trials

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define maxline 80
#define maxsubjects 35

void itoa(int p, char sp[]);

int main()
{
  FILE *infile, *outfile, *appfile;
  float rightlo, lefthi, leftlo;
  float attn;
  int i,j,k;
  int rweights[maxsubjects][13];
  int num_a,start_a,end_a,inc_a,n_trials;
  int attni,m,ggns_in,ggnseed,n_subj;
  char sa[3], appname[maxline], temp[2];
  char bin[maxline],whereto[maxline],netgen[maxline];
  char Infile[maxline];

  const char *BASE = getenv("LSNM");

  strcpy(bin,BASE);
  strcat(bin,"bin/");
  strcpy(netgen,bin);
  strcat(netgen,"netgenC_au");
  strcpy(Infile,BASE);
  strcat(Infile,"code/mkbatchb_au.in");

  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

  fscanf(infile,"%s",whereto);
  fscanf(infile,"%d %d %d %f %f %f",&m,&ggns_in, &ggnseed, &lefthi,&leftlo,&rightlo);
  fscanf(infile,"%d %d %d %d %d",&n_subj,&n_trials,&start_a,&end_a,&inc_a);

  outfile = fopen("batchb_au","w");

  for(i=1; i<=n_trials; i++)
    {
      strcpy(appname,BASE);
      strcat(appname,"code/appb");
      sprintf(temp,"%d",i);
      strcat(appname,temp);
      appfile = fopen(appname,"w");
      fprintf(appfile,"#include %sweights/right/aurightlist.txt\n",BASE);
      fprintf(appfile,"#include %sweights/left/auleftlist.txtn\n",BASE);
      fprintf(appfile,"#include %sweights/cross/aucrosslist.txt\n",BASE);
      fprintf(appfile,"#include %sinputs/auseq%d.rsb\n",BASE,i);
      fclose(appfile);
    }

  for(i=1; i<=n_subj; i++) /*loop saving connection weights for each subj*/
    {
      fscanf(infile,"%d %d %d %d %d %d %d %d %d %d %d %d %d",&rweights[i][0],&rweights[i][1],&rweights[i][2],&rweights[i][3],&rweights[i][4],&rweights[i][5],&rweights[i][6],&rweights[i][7],&rweights[i][8],&rweights[i][9],&rweights[i][10],&rweights[i][11],&rweights[i][12]);
    } /* end of n_subj loop */

  if(ggnseed == 0)
    ggnseed = time(NULL);

  lefthi /= 100.0;
  leftlo /= 100.0;
  rightlo  /= 100.0;

  if(inc_a == 0)
    num_a = 1;
  else
    num_a = (end_a - start_a)/inc_a + 1;

  /* start of output to batchb_au */

  fprintf(outfile,"#\n#\n#\n");
  fprintf(outfile,"cd %s/sfiles\n",BASE);
  fprintf(outfile,"%smkattn_au hiattn_l.s %4.2f\n",bin,lefthi);
  fprintf(outfile,"%smkattn_au loattn_l.s %4.2f\n",bin,leftlo);
  fprintf(outfile,"%smkattn_au loattn_r.s %4.2f\n",bin,rightlo);

  /* crossws_au creates the same .ws files every time.  so as of now
we are not running it every time we run the batch job.  if we decide
to run it again with the batch simply uncomment this block.
  fprintf(outfile,"cd %s/weights/cross\n",BASE);
  fprintf(outfile,"%scrossws_au\n",bin);
  */

  fprintf(outfile,"cd %s\n",BASE);
  
  for(i=1; i<=n_trials; i++)
    {
      fprintf(outfile,"rm auseq%d.s\n",i);
      fprintf(outfile,"cat $LSNM/weights/right/auright.s $LSNM/weights/left/auleft.sn $LSNM/code/appb%d > auseq%d.s\n",i,i);
      fprintf(outfile,"rm $LSNM/code/appb%d\n",i);
    }

  fprintf(outfile,"rm $LSNM/code/batchb_au\n");

  for(k=1; k<=n_subj; k++) /*subject loop*/
    {
      fprintf(outfile,"#\n#\n");
      fprintf(outfile,"cd %s\n",BASE);
      fprintf(outfile,"mkdir $LSNM/noisy\n");

       /* make an input file for netgenC_au, must be in the code directory*/
      fprintf(outfile,"cd %s/code\n",BASE);
      fprintf(outfile,"%s/altgenw_au %d %d %d %d %d %d %d %d %d %d %d %d %d\n",bin,rweights[k][0],rweights[k][1],rweights[k][2],rweights[k][3],rweights[k][4],rweights[k][5],rweights[k][6],rweights[k][7],rweights[k][8],rweights[k][9],rweights[k][10],rweights[k][11],rweights[k][12]);
      fprintf(outfile,"echo Subject %d\n",k);

      for(j=0; j < num_a; j++) /* attn loop */
	{
	  attni = start_a + inc_a*j;
	  attn = (float)attni/100.0;
	  itoa(attni,sa);
	  fprintf(outfile,"#\n");
	  fprintf(outfile,"cd %ssfiles\n",BASE);
	  fprintf(outfile,"%smkattn_au hiattn_r.s %4.2f\n",bin,attn);

	  fprintf(outfile,"cd %sweights/right\n",BASE);
	  fprintf(outfile,"for file in *.ws ; do\n");
	  // fprintf(outfile,"foreach file (*.ws)\n");
	  fprintf(outfile,"  %s $file\n  done\n",netgen);
	  // fprintf(outfile,"  %s $file\n  end\n",netgen);
	  fprintf(outfile,"cd $LSNM/weights/left\n");
	  fprintf(outfile,"for file in *.ws ; do\n");
	  // fprintf(outfile,"foreach file (*.ws)\n");
	  fprintf(outfile,"  %s $file\n  done\n",netgen);
	  // fprintf(outfile,"  %s $file\n  end\n",netgen);
	  fprintf(outfile,"echo attn level: %4.2f\n",attn);
	  fprintf(outfile,"cd %snoisy\nmkdir b%s\n",BASE,sa);

	   for(i=1; i<=n_trials; i++)
	    {	      
	      fprintf(outfile,"cd %sweights/cross\n",BASE);
	      fprintf(outfile,"%scrosswt_au_i netgenC_au\nchmod u+x sh_cross\n",bin);
	      fprintf(outfile,"echo Building cross connections...\n");
	      fprintf(outfile,"./sh_cross\nrm sh_cross\n");
	      // fprintf(outfile,"sh_cross\nrm sh_cross\n");
	      fprintf(outfile,"cd %s\n",BASE);
	      fprintf(outfile,"%sau_sim1 auseq%d\n",bin,i);
	      fprintf(outfile,"gzip *.out\n");
	      fprintf(outfile,"cd $LSNM/noisy/b%s\nmkdir trial%d\n",sa,i);
	      fprintf(outfile,"cd %s\n",BASE);
	      fprintf(outfile,
 "mv spec_pet.m $LSNM/noisy/b%s/trial%d/\nmv *.out* $LSNM/noisy/b%s/trial%d/\n",sa,i,sa,i);
	      fprintf(outfile,"cp %sweights/cross/aucrosslist.txt $LSNM/noisy/b%s/trial%d/aucrosslist%d.txt\n",BASE,sa,i,i);
	      fprintf(outfile,"#\n");
	    } /* end of stimulus pairs */
	} /* end of j loop - attn loop */

      fprintf(outfile,"mv noisy %s/subj%d\n",whereto,k);
    } /* end of k loop - subject loop */

  fprintf(outfile,"\nrm $LSNM/weights/right/*.w\n");
  fprintf(outfile,"rm $LSNM/weights/left/*.w\n");
  
  fprintf(outfile,"cd $LSNM/weights/cross\n");
  fprintf(outfile,"rm ea*.w\n");
  fprintf(outfile,"rm eg*.w\n");
  fprintf(outfile,"rm *.w\n");
  fprintf(outfile,"rm aucrosslist.txt\n");
  
  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"rm code/netgenC_au.in\n");
  fprintf(outfile,"rm sfiles/*attn*.s\n");

  fclose(infile);
  fclose(outfile);
}
