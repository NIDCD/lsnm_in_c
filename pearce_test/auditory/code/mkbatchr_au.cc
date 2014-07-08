/* mkbatchr_au.cc
   
   written 07/08/03
   by: B. Warner

   form input to right hemisphere only

   attention level parameters are:
   rightlo-- for right brain during intertrial period
   righthi steps thru "start" to "end" at an increment of "increment

   "BASE" below specifies which  directory (hence which computer) we are on

   mod. 07/09/03
   model contains a left hemisphere MGN unit.  thus, the model can take
   a left hemisphere input that can be visualized in this unit.

  Pearce Decker 2013
This script seems to be outdated as it calls for an input (auseqr) that does not exist anywhere in the current copy of the model.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define maxline 80
#define maxstring 15

void itoa(int p, char sp[]);

int main()
{
  FILE *infile, *outfile, *appfile;
  float attn, rightlo, lefthi;
  int nsubj,cleanup,num,k,attni,start,end,increment;
  char sp[3],bin[maxline],whereto[maxline],netgen[maxline];
  char Infile[maxline],temp[maxstring];

  const char *BASE = getenv("LSNM");
 

  strcpy(bin,BASE);
  strcat(bin,"bin/");
  strcpy(netgen,bin);
  strcpy(Infile,BASE);
  strcat(Infile,"code/mkbatchr_au.in");
  if((infile = fopen(Infile,"r")) == NULL)
    {
      printf("can't open %s\n",Infile);
      exit(0);
    }

  outfile = fopen("batchr_au","w");
  appfile = fopen("appr_au","w");

  fprintf(appfile,"#include %s/weights/right/aurightlist.txt\n",BASE);
  fprintf(appfile,"#include %s/inputs/auseqr.rs\n",BASE);
  fclose(appfile);

  fscanf(infile,"%s %s",temp,whereto);
  fscanf(infile,"%d %d %f %d %d %d",
	 &nsubj,&cleanup,&rightlo,&start,&end,&increment);

  if(cleanup == 0 && nsubj > 1)
    {
      printf("If you are running multi-subjects, you should not set cleanup to 0.\n");
    }

  strcat(netgen,temp);
  if(increment == 0)
    num = 1;
  else
    num = (end-start)/increment + 1;

  rightlo /= 100.0;

  lefthi = 0.30;

  /* start of output */

  fprintf(outfile,"#\n#\n#\n");
  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"mkdir $LSNM/noisy\n");

  fprintf(outfile,"cd $LSNM/sfiles\n");
  fprintf(outfile,"%smkattn_au hiattn_l.s %4.2f\n",bin,lefthi);
  fprintf(outfile,"%smkattn_au loattn_r.s %4.2f\n",bin,rightlo);

  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"rm auseqr.s\n");
  fprintf(outfile,"cat $LSNM/weights/right/auright_r.s $LSNM/code/appr_au > auseqr.s\n");
  fprintf(outfile,"rm $LSNM/code/appr_au\nrm $LSNM/code/batchr_au\n");

  fprintf(outfile,"cd %s/code\n",BASE);
  fprintf(outfile,"%sgenw_au 100\n",bin);

  for(k=0; k < num; k++)
    {
      attni = start + k*increment;
      attn = (float)attni/100.0;
      itoa(attni,sp);
      fprintf(outfile,"#\n#\n");
      fprintf(outfile,"cd %s\n",BASE);
      if(nsubj > 0)
	{
	  fprintf(outfile,"cd $LSNM/weights/right\n");
	  fprintf(outfile,"for file in *.ws ; do\n");
	  // fprintf(outfile,"foreach file (*.ws)\n");
	  fprintf(outfile,"  %s $file\n  done\n",netgen);
	  // fprintf(outfile,"  %s $file\n  end\n",netgen);
	  if(nsubj == 1)
	    nsubj--;
	}
      
      fprintf(outfile,"cd %ssfiles\n",BASE);
      fprintf(outfile,"%smkattn_au hiattn_r.s %4.2f\n",bin,attn);
      fprintf(outfile,"cd %s\n",BASE);
      fprintf(outfile,"%sau_sim1 auseqr\n",bin);
      fprintf(outfile,"gzip *.out\ncd $LSNM/noisy\nmkdir b%s\n",sp);
      fprintf(outfile,"cd %s\n",BASE);
      fprintf(outfile,"mv spec_pet.m $LSNM/noisy/b%s/\nmv *.out.gz $LSNM/noisy/b%s/\n",sp,sp);
    }
  if(cleanup != 0)
    fprintf(outfile,"\nrm $LSNM/weights/right/*.w\n");
  fprintf(outfile,"\nrm $LSNM/sfiles/*attn*.s\n");
  fprintf(outfile,"mv $LSNM/noisy %s/fR\n",whereto);

  fclose(infile);
  fclose(outfile);
}
