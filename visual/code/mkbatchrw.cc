/*rev. 8/98
  right hemisphere only
  mkbatchrw.cc, generate shell script to run sim1 for weakened
  connection strength between regions

  capacity: if capacity is 50 => 50% of the original connection strength
            note that capacity < 99
  attn: attention level, 5 => attention level is 0.05
            note that attn < 50
  start_c, end_c: specifies the range of capacity in the batch run
  start_a, end_a: specifies the range of attention in the batch run
  inc_c, inc_a: increment of capacity, increment of attention
  All are entered as integers, we will convert them to proper units in code

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define maxline 80

void itoa(int p, char sp[]);

int main()
{
  FILE *infile, *outfile, *appfile;
  float rightlo;
  float attn;
  int j,k;
  int num_c,num_a,start_c,end_c, inc_c,start_a,end_a,inc_a;
  int C,attni,m;
  char sc[3],sa[3];
  char bin[maxline],whereto[maxline],netgen[maxline];
  char Infile[maxline];

  const char *BASE= getenv("LSNM");

  strcpy(bin,BASE);
  strcat(bin,"bin/");
  strcpy(netgen,bin);
  strcat(netgen,"netgenC");
  strcpy(Infile,BASE);
  strcat(Infile,"code/mkbatchrw.in");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

  outfile = fopen("batchrw","w");
  appfile = fopen("apprw","w");
  fprintf(appfile,"#include %sweights/right/rightlist.txt\n",BASE);
  fprintf(appfile,"#include %sinputs/pethir.rs\n",BASE);
  fclose(appfile);
  fscanf(infile,"%s",whereto);
  fscanf(infile,"%d %f ",
      &m,&rightlo);

  fscanf(infile,"%d %d %d %d %d %d",
              &start_c,&end_c,&inc_c,&start_a,&end_a,&inc_a);

  rightlo  /= 100.0;

  if(inc_c == 0)
    num_c = 1;
  else
    num_c = (end_c - start_c)/inc_c + 1;

  if(inc_a == 0)
    num_a = 1;
  else
    num_a = (end_a - start_a)/inc_a + 1;

  /* start*/
  fprintf(outfile,"#\n#\n#\n");

  fprintf(outfile,"cd %s\n",BASE);
  /*lo attn on right do not change among subjects*/
  fprintf(outfile,"cd sfiles\n");
  fprintf(outfile,"%smkattn loattn_r.s %4.2f\n",bin,rightlo);
  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"rm pethi.s\n");
  fprintf(outfile,
   "cat weights/right/right.s code/apprw > pethi.s\n");
  fprintf(outfile,"rm code/apprw\nrm code/batchrw\n");

  /*make right brain lgn input*/
  fprintf(outfile,"cd inputs\n");
  for(k = 1; k <= m; k++)
    {
      fprintf(outfile,"cp input%d1.inp input%d.inp\n",k,k);
    }

  for(k = 0; k < num_c; k++)
    {
      C = start_c + inc_c*k;
      itoa(C,sc);

      fprintf(outfile,"#\n#\n");

      fprintf(outfile,"cd %s\n",BASE);
      fprintf(outfile,"mkdir noisy\n");
      /* make an input file for netgenC, must be in code directory*/

      fprintf(outfile,"cd %scode\n",BASE);
      fprintf(outfile,"%sgenw %d\n",bin,C);
      for(j = 0; j < num_a; j++)
	{
	  attni = start_a + inc_a*j;
	  attn = (float)attni/100.0;
	  itoa(attni,sa);
	  fprintf(outfile,"#\n");
	  fprintf(outfile,"cd %s\n",BASE);
	  fprintf(outfile,"cd sfiles\n");
	  fprintf(outfile,"%smkattn hiattn_r.s %4.2f\n",bin,attn);

	  fprintf(outfile,"cd %sweights/right\n",BASE);
	  fprintf(outfile,"for file in *.ws ; do\n");
	  fprintf(outfile,"  %s $file\n  done\n",netgen);
	  fprintf(outfile,"cd %s\n",BASE);
	  fprintf(outfile,"%ssim1 pethi\n",bin);
	  fprintf(outfile,"gzip *.out\n");
	  fprintf(outfile,"cd noisy\nmkdir b%s\n",sa);
	  fprintf(outfile,"cd %s\n",BASE);
	  fprintf(outfile,
	"mv spec_pet.m noisy/b%s/\nmv *.out* noisy/b%s/\n",sa,sa);
	}/* end of j loop*/
      fprintf(outfile,"mv noisy %s/sken%s\n",whereto,sc);

    }/* end of k loop*/

  fprintf(outfile,"\nrm weights/right/*.w\n");


  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"rm code/netgenC.in\n");
  fprintf(outfile,"rm sfiles/*attn*.s\n");

  fclose(infile);
  fclose(outfile);
}
