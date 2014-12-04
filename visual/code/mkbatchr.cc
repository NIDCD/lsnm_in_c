/*mkbatchr.cc for right side,  updated 8/98
attention level parameters are:
rightlo-- for right brain during intertrial period
righthi steps thru "start" to "end" at an increment of "increment

The attention levels are entered as integers.
e.g. if we want attention level of 0.05, we enter 5.
This input will be converted to the proper unit in the code
We want inter entries because when we generate directory for a
subject with attention level 0.05, we will name that directory b05.
It is necessary to keep the directory names to be of the same length
so we can use petmanip.m later for data manipulation

"BASE" below specifies which  directory (hence which computer) we are on
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define maxline 80
#define maxstring 15

void itoa(int p, char sp[]);

int main()
{
  FILE *infile, *outfile, *appfile;
  float attn,rightlo;
  int  nsubj,cleanup,m,num,k,attni,start,end,increment;
  char sp[3],bin[maxline],whereto[maxline],netgen[maxline];
  char Infile[maxline],temp[maxstring];

  const char *BASE= getenv("LSNM");

  strcpy(bin,BASE);
  strcat(bin,"bin/");
  strcpy(netgen,bin);
  strcpy(Infile,BASE);
  strcat(Infile,"code/mkbatchr.in");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

  outfile = fopen("batchr","w");
  appfile = fopen("appr","w");

  fprintf(appfile,"#include %sweights/right/rightlist.txt\n",BASE);
  fprintf(appfile,"#include %sinputs/pethir.rs\n",BASE);
  fclose(appfile);

  fscanf(infile,"%s %s",temp, whereto);
  fscanf(infile,"%d %d %d %f %d %d %d",
	 &nsubj,&cleanup,&m,&rightlo,&start,&end,&increment);

  if(cleanup == 0 && nsubj > 1)
    {
      printf("If you are running multi-subjects, you shouldn't set the cleanup to 0,TSK! TSK!\n");
    }

  strcat(netgen,temp);
  if(increment == 0)
    num = 1;
  else
    num = (end - start)/increment + 1;

  rightlo /= 100.0;

  /* start*/
  fprintf(outfile,"#\n#\n#\n");

  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"mkdir noisy\n");

/*lo attention on right do not change among subjects*/
  fprintf(outfile,"cd sfiles\n");
  fprintf(outfile,"%smkattn loattn_r.s %4.2f\n",bin,rightlo);

  /*make right brain lgn input*/
  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"cd inputs\n");
  for(k = 1; k <= m; k++)
    {
      fprintf(outfile,"cp input%d1.inp input%d.inp\n",k,k);
    }

  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"rm pethi.s\n");
  fprintf(outfile,"cat weights/right/right.s  code/appr > pethi.s\n");
  fprintf(outfile,"rm code/appr\nrm code/batchr\n");

  for(k = 0; k < num; k++)
    {
      attni =start + k* increment;
      attn = (float)attni/100.0;
      itoa(attni,sp);
      fprintf(outfile,"#\n#\n");
      fprintf(outfile,"cd %s\n",BASE);
      if(nsubj > 0)
	{
	  fprintf(outfile,"cd weights/right\n");
	  fprintf(outfile,"for file in *.ws ; do\n");
	  fprintf(outfile,"  %s $file\n  done\n",netgen);
	  if(nsubj == 1)
	    nsubj--;
	}
      fprintf(outfile,"cd %ssfiles\n",BASE);
      fprintf(outfile,"%smkattn hiattn_r.s %4.2f\n",bin,attn);
      fprintf(outfile,"cd %s\n",BASE);
      fprintf(outfile,"%ssim1 pethi\n",bin);
      fprintf(outfile,"gzip *.out\ncd noisy\nmkdir b%s\n",sp);
      fprintf(outfile,"cd %s\n",BASE);
      fprintf(outfile,"mv spec_pet.m noisy/b%s/\nmv *.out.gz noisy/b%s/\n",sp,sp);
    }
  if(cleanup != 0)
    fprintf(outfile,"\nrm weights/right/*.w\n");
  fprintf(outfile,"\nrm sfiles/*attn*.s\n");
  fprintf(outfile,"mv noisy %s/fR\n",whereto);

  fclose(infile);
  fclose(outfile);

}

