/*rev. 8/98
  alzbatchr.cc, generate shell script to run sim1 for right side
  for alzheimer disease
  capacity: if capacity is 50 => neuron activation is 50% of a healthy one
            note that capacity < 99
  percent: percent of neuron sick, 20=> 20% of neurons are sick
            note that percent < 99
  attn: attention level, 5 => attention level is 0.05
            note that attn < 50
  start_c, end_c: specifies the range of capacity in the batch run
  start_p, end_p: specifies the range of percent sick neurons in the batch run
  start_a, end_a: specifies the range of attention in the batch run
  inc_c, inc_p, inc_a: increment capacity,percent, attention
  All are input s integers, we will convert them to proper units in code
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
  float rightlo;
  float attn;
  int i,j,k;
  int num_p, num_c,num_a,start_p,inc_p, start_c, inc_c,start_a,inc_a;
  int end_p,end_c,end_a;
  int P,C,attni,m;
  char sc[3],sp[3],sa[3];
  char bin[maxline],whereto[maxline];
  char Infile[maxline];

  char *BASE= "/home/bhguest/brent/visual";

  strcpy(bin,BASE);
  strcat(bin,"/bin/");
  strcpy(Infile,BASE);
  strcat(Infile,"/code/alzbatchr.in");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

  outfile = fopen("batchalz","w");
  appfile = fopen("appalz","w");

  fprintf(appfile,"#include %s/weights/right/rightlist.txt\n",BASE);
  fprintf(appfile,"#include %s/inputs/pethir.rs\n",BASE);
  fclose(appfile);

  fscanf(infile,"%s",whereto);
  fscanf(infile,"%d %f ",&m,&rightlo);
  fscanf(infile,"%d %d %d %d %d %d %d %d %d",&start_p,&end_p,
	 &inc_p, &start_c,&end_c,&inc_c,&start_a,&end_a,&inc_a);

  rightlo /= 100.0;

  if(inc_p == 0)
    num_p = 1;
  else
    num_p = (end_p - start_p)/inc_p + 1;

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
  fprintf(outfile,"mkdir noisy\n");

  /*lo attention on right do not change among subjects*/
  fprintf(outfile,"cd sfiles\n");
    for(k = 1; k <= m; k++)
    {
      fprintf(outfile,"cp input%d1.inp input%d.inp\n",k,k);
    }
  fprintf(outfile,"%smkattn loattn_r.s %4.2f\n",bin,rightlo);
  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"rm pethi.s\n");
  fprintf(outfile,"cat weights/right/right.s  code/appalz > pethi.s\n");
  fprintf(outfile,"rm code/appalz\nrm code/batchalz\n");

  for(k = 0; k < num_a; k++)
    {
      attni = start_a + inc_a*k;
      attn = (float)attni/100.0;
      itoa(attni,sa);
      fprintf(outfile,"#\n#\n");
      fprintf(outfile,"cd %s\n",BASE);
      fprintf(outfile,"cd sfiles\n");
      fprintf(outfile,"%smkattn hiattn_r.s %4.2f\n",bin,attn);
      fprintf(outfile,"cd %s\n",BASE);

      if(start_p != 0)
	{    /* we will run a base case with no sick neurons*/
	  /*generate weight files*/
	  fprintf(outfile,"cd weights/right\n");

	  fprintf(outfile,"foreach file (*.ws)\n");
	  fprintf(outfile," %snetgen1 $file\n end\n",bin);
	  fprintf(outfile,"cd %s\n",BASE);

	  fprintf(outfile,"%ssim1 pethi\n",bin);
	  fprintf(outfile,"gzip *.out\ncd noisy\nmkdir a%sp00c00\n",sa);
	  fprintf(outfile,"cd %s\n",BASE);
	  fprintf(outfile,"mv spec_pet.m noisy/a%sp00c00/\nmv *.out.gz noisy/a%sp00c00/\n",sa,sa);
	  fprintf(outfile,"#\n");
	}/* end of doing a base case for this attention*/

      for(i = 0; i < num_p; i++)
	{
	  P = start_p + inc_p*i;
	  itoa(P,sp);
	  for(j = 0; j < num_c; j++)
	    {
	      C = start_c + inc_c*j;
	      itoa(C,sc);
	      fprintf(outfile,"#\n");
	      fprintf(outfile,"cd %s\n",BASE);
	      /* make a bad.neuron file to run netgenA in the BASE directory*/
	      fprintf(outfile,"%salz %d  %d\n",bin,P,C);
	      /*generate weight files*/
 	      fprintf(outfile,"cd weights/right\n");
	      fprintf(outfile,"foreach file (*.ws)\n");
	      fprintf(outfile," %snetgenA $file\n end\n",bin);
	      fprintf(outfile,"cd %s\n",BASE);

	      fprintf(outfile, "%ssim1 pethi\n",bin);
	      fprintf(outfile,"gzip *.out\ncd noisy\nmkdir a%sp%sc%s\n",sa,sp,sc);
	      fprintf(outfile,"cd %s\n",BASE);
	      fprintf(outfile,"mv spec_pet.m noisy/a%sp%sc%s/\nmv *.out.gz noisy/a%sp%sc%s/\n",sa,sp,sc,sa,sp,sc);
	    }/* end of j loop*/
	}/* end of i loop*/
    }/* end of k loop*/

  fprintf(outfile,"\nrm weights/right/*.w\n");
  fprintf(outfile,"\nrm sfiles/*attn*.s\n");
  fprintf(outfile,"rm bad.neuron\n");
  fprintf(outfile,"mv noisy %s/alzz\n",whereto);
  fclose(infile);
  fclose(outfile);
}


