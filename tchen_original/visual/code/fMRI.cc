/*rev. 5/2000
  fMRI.cc, generate shell script to run sim1 for weakened
  connection strength between regions
  form input right, noisy input left.

  capacity: if capacity is 50 => 50% of the original connection strength
            note that capacity < 99
  attn: attention level, 5 => attention level is 0.05
            note that attn < 50
  start_c, end_c: specifies the range of capacity in the batch run
  start_a, end_a: specifies the range of attention in the batch run
  inc_c, inc_a: increment of capacity, increment of attention
  All are entered as integers, we will convert them to proper units in code

at the command line type
fmri cross_select_seed ggnseed perl_seed

where
cross_select_seed: random number generator seed to determine which of
                   the cross connections exist
ggnseed: random number generator seed to determine which of the input
         pixel will be lit
  if the seed is 0, system clock will be used
perl_seed: if no entry, do not call Fatima's perl_seed script to change the 
      random number gen. for scaling bias of the weight
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define maxline 80
#define maxword 20

void itoa(int p, char sp[]);

void write_w(FILE *outfile,char *BASE,char *bin, char *netgen,int *seed);
void fix_w_seed(FILE *outfile, char *BASE, int perl_seed);
int nsubj;

int main(int argc, char **argv)
{
  FILE *infile, *outfile, *appfile;
  float rightlo, lefthi, leftlo;
  float attn;
  int i,j,k, argv1, argv2,cross_select_seed, ggnseed, perl_seed;
  int num_c,num_a,start_c,end_c, inc_c,start_a,end_a,inc_a;
  int nsubj, C,attni,m,ggns_in;
  char **sc,**sa, cstemp[maxword];
  char bin[maxline],whereto[maxline],netgen[maxline];
  char Infile[maxline];

  char *BASE= "/home/bhguest/brent/visual";

  if(argc < 3)
    {
      printf("usage: fmri cross_select_seed ggnseed\n");
      exit (0);
    }

  argv1 = atoi(argv[2]);
  cross_select_seed = argv1;
  argv2 = atoi(argv[2]);

  if(argc == 4)
    perl_seed = atoi(argv[3]);
  else perl_seed = -1;

  strcpy(bin,BASE);
  strcat(bin,"/bin/");
  strcpy(netgen,bin);
  strcat(netgen,"netgenC");
  strcpy(Infile,BASE);
  strcat(Infile,"/code/fMRI.in");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

  outfile = fopen("fmri.sh","w");
  appfile = fopen("appw","w");
  fprintf(appfile,"#include %s/weights/right/rightlist.txt\n",BASE);
  fprintf(appfile,"#include %s/weights/left/leftlist.txtn\n",BASE);
  fprintf(appfile,"#include %s/weights/cross/crosslist.txt\n",BASE);
  fprintf(appfile,"#include %s/inputs/pethi.rsn\n",BASE);
  fclose(appfile);
  fscanf(infile,"%s", whereto);
  fscanf(infile,"%d %d %d %f %f %f",
      &nsubj, &m,&ggns_in, &lefthi,&leftlo,&rightlo);

  fscanf(infile,"%d %d %d %d %d %d",
              &start_c,&end_c,&inc_c,&start_a,&end_a,&inc_a);

  lefthi /= 100.0;
  leftlo /= 100.0;
  rightlo  /= 100.0;

  if((inc_c == 0) || (start_c > end_c))
    num_c = 1;
  else
    num_c = (end_c - start_c)/inc_c + 1;

  if((inc_a == 0) || (start_a > end_a))
    num_a = 1;
  else
    num_a = (end_a - start_a)/inc_a + 1;

  /* start*/
  fprintf(outfile,"#! /bin/sh \n");
  fprintf(outfile,"#\n#\n#seed for selecting cross connection = %d\n",
             cross_select_seed);
  fprintf(outfile,"#\n#seed for selecting lit input pixels = %d\n",
             argv2);
  if(perl_seed > 0)
    fprintf(outfile,
      "#\n#seed for Fatima's weight bias scaling code = %d\n#\n#\n",perl_seed);
  else
    fprintf(outfile,"#\n# did not use Fatima's code weight bias seed\n#\n#\n");

  /*lo attn on right and attn on left do not change among subjects*/
  fprintf(outfile,"cd %s/sfiles\n",BASE);
  fprintf(outfile,"%smkattn hiattn_l.s %4.2f\n",bin,lefthi);
  fprintf(outfile,"%smkattn loattn_l.s %4.2f\n",bin,leftlo);
  fprintf(outfile,"%smkattn loattn_r.s %4.2f\n",bin,rightlo);

  fprintf(outfile,"#\ncd %s/weights/cross\n",BASE);
  fprintf(outfile,"%scrossws\n",bin);
  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"rm pethi.s\n");
  fprintf(outfile,
"cat weights/right/right.s weights/left/left.sn code/appw > pethi.s\n");
  //  fprintf(outfile,"rm code/appw\nrm code/fmri.sh\n");

  if(argv2 == 0)
    ggnseed = time(NULL);
  else ggnseed = argv2;

  /*make right brain lgn input*/
  fprintf(outfile,"#\ncd inputs\n");
  for(k = 1; k <= m; k++)
    {
      fprintf(outfile,"cp input%d1.inp input%d.inp\n",k,k);
    }

  sc = new (char(*[num_c]));
  for(i = 0; i< num_c; i++)
    {
      sc[i] = new char [maxline];
      strcpy(sc[i],whereto);
    }
  for(i = 0; i < num_c; i++)  /*weakening connection*/
    {
      C = start_c + inc_c*i;
      if(C == 100)
	strcpy(cstemp,"xx");
      else
	itoa(C,cstemp);
      strcat(sc[i],"/wken");
      strcat(sc[i],cstemp);
    }

  sa = new (char(*[num_a]));
  for(i = 0; i< num_a; i++)
    sa[i] = new char [maxword];
  
  //make directory name
  for(i = 0; i < num_a; i++)  /*attn */
    {
      attni = start_a + inc_a*i;
      itoa(attni,cstemp);
      strcpy(sa[i],"b");
      strcat(sa[i],cstemp);
    }



  // set up output directories
  // for each capacity N, we have a directory wkenN
  // under each wkenN, we have the bM dirctories 
  // where M is the att level

  fprintf(outfile,"if [ ! -d %s ]\n then \n mkdir %s\n fi\n",
	  whereto, whereto);

  for(i = 0; i< num_c; i++)
    {
      fprintf(outfile,"mkdir %s\n",sc[i]);
      fprintf(outfile,"cd %s\n", sc[i]);
      for(j = 0; j < num_a; j++)  
	fprintf(outfile,"mkdir %s\n",sa[j]);
    }

  // the within right side, and within left side connections are in
  // the directory weights/right and left.
  // we do not make new .ws for them

  // make .w files and cross connection

  if(perl_seed > 0)
    fix_w_seed(outfile, BASE, perl_seed);
      
  for(j = 0; j < num_a; j++)  /*attn loop*/
    {
      attni = start_a + inc_a*j;
      attn = (float)attni/100.0;

      fprintf(outfile,"#\n#\n");

      for(k = 0; k < num_c; k++)/*capacity loop */
	{
	  C = start_c + inc_c*k;

	  /* make an input file netgenC.in, 
             must be in the code directory*/

	  fprintf(outfile,"cd %s/code\n",BASE);
	  fprintf(outfile,"%sgenw %d\n",bin,C);

	  fprintf(outfile,"#\n");
	  fprintf(outfile,"cd %s/sfiles\n",BASE);
	  fprintf(outfile,"%smkattn hiattn_r.s %4.2f\n",bin,attn);


	  fprintf(outfile,"cd %s/inputs\n",BASE);
	  for(i = 1; i<= m; i++)
	    {
	      fprintf(outfile,"%smkinput l %d %d\n",bin,ggns_in,ggnseed);
	      fprintf(outfile,"mv ggns.inp ggns%d.inp\n",i);
		ggnseed++;
	    }

	  write_w(outfile,BASE,bin,netgen,&cross_select_seed);

	  fprintf(outfile,"%ssim1 pethi\n",bin);
	  fprintf(outfile,"gzip *.out\n");
	  fprintf(outfile,"cd %s\n",BASE);
	  fprintf(outfile, "mv spec_pet.m %s/%s/\n",sc[k], sa[j]);
	  fprintf(outfile, "mv *.out* %s/%s/\n",sc[k], sa[j]);
	}/* end of k loop - weakening strength loop*/

    }/* end of j loop -- attn loop*/

  //recover the .ws weight spec if we changed it using seedfiles.pl
  //earlier
  if(perl_seed > 0)
    {
      perl_seed = 0;
      fix_w_seed(outfile,BASE, 0);
    }

  fprintf(outfile,"cd %s\n",BASE);
  fprintf(outfile,"\nrm weights/right/*.w\n");
  fprintf(outfile,"rm weights/left/*.w\n");

/* there are 800 .ws files in the cross directory, the max number of .w
   files also reaches 800. The memory space 
   for shell script is too small to rm all in one sweep,
   so we split up the chore*/

  fprintf(outfile,"cd weights/cross\n");
  fprintf(outfile,"rm crosslist.txt\n");
  fprintf(outfile,"rm ev*.w\n");
  fprintf(outfile,"rm ev*.ws\n");
  fprintf(outfile,"rm eg*.w\n");
  fprintf(outfile,"rm eg*.ws\n");
  fprintf(outfile,"rm iv*.w\n");
  fprintf(outfile,"rm iv*.ws\n");
  fprintf(outfile,"rm ig*.w\n");
  fprintf(outfile,"rm ig*.ws\n");
  fprintf(outfile,"rm *.w\nrm *.ws\n");
  fprintf(outfile,"cd %s\n",BASE);

  fprintf(outfile,"rm inputs/ggns*.inp\n");
  fprintf(outfile,"rm code/netgenC.in\n");
  fprintf(outfile,"rm sfiles/*attn*.s\n");

  fclose(infile);
  fclose(outfile);

  //clean up
  for(i=0; i<num_a; i++)
    delete [] sa[i];
  delete [] sa;
  for(i=0; i<num_c; i++)
    delete [] sc[i];
  delete [] sc;

}

void write_w(FILE *outfile, char *BASE, char *bin, 
                char *netgen, int *seed)
{
  fprintf(outfile,"cd %s/weights/right\n",BASE);
  fprintf(outfile,"for file in `ls *.ws`\n do\n");
  fprintf(outfile,"  %s $file\n  done\n",netgen);
  fprintf(outfile,"cd ../left\n");
  fprintf(outfile,"for file in `ls *.ws`\ndo\n");
  fprintf(outfile,"  %s $file\n  done\n",netgen);
  fprintf(outfile,"cd ../cross\n");
  fprintf(outfile,"%scrosswt_i netgenC %d\n",bin, *seed);
  fprintf(outfile,"chmod u+x sh_cross\n");
  fprintf(outfile,"sh_cross\nrm sh_cross\n");

  fprintf(outfile,"cd %s\n",BASE);

  //change seed if there is more than 1 subject
  if(nsubj > 1)
    *seed++;

  return;
}

void fix_w_seed(FILE *outfile,char *BASE, int perl_seed)
{
  fprintf(outfile,"cd %s/weights/right\n",BASE);
  fprintf(outfile,"%s/seedfiles.pl %d\n",BASE,perl_seed);
  if(perl_seed > 0) perl_seed++;
  fprintf(outfile,"cd %s/weights/left\n",BASE);
  fprintf(outfile,"%s/seedfiles.pl %d\n",BASE,perl_seed);
  if(perl_seed > 0) perl_seed++;
  fprintf(outfile,"cd %s/weights/cross\n",BASE);
  fprintf(outfile,"%s/seedfiles.pl %d\n",BASE,perl_seed);
  return;
}
