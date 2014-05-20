/* alz.cc rev.  8/98*/
/* 
There are two input venues: an command line and input file alz.in
The command line input is used so that we can vary the "percent" and "capacity"
parameters in the batch1 file
percent: percent of sick neurons in a region
capacity: the capacity of the sick neuron as compared to when it is healthy
          i.e. if capacity=60 => neuron 's activation is 60%
	          capacity = 0, neuron is dead

input file is alz.in, which specifies regions and % of sick cells

if we define "on" as having sick neurons:
if both hemispheres are involved, and both excitatory and inhibitory units
 have sick neurons.  The input file would have:
1  1  ==> indicating hemisphere[0] (left) on, and hemisphere right on.
          if only left hemisphere on, this line would be 1 0
1  1  ==> indicating excitatory units on, and inhibitory units on
then the next four lines are a sequence of 0's and 1's, representing
left-excitatory regions
left-inhibitory regions
right-excitatory regions
right-inhibitory regions

ex. for left-excitatory regions:
0  1  1  0  1  1  1  0  0  0
which means regions 1,2,4,5,6 have sick neurons.
For the labels of each region, see left[2][regions} in the code

The output file lists the number of regions, number of sick neurons/region
followed by each region and the matrix index of the sick neurons

If we want the percent of sick neuron to be 5, and capacity of the sick
neuron to be 30% of when it is healthy,
at the system prompt type:
alz 5  30
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define regions 10
#define nrow 9
#define maxline 80

int main (int argc, char **argv)
{
  FILE *infile, *outfile;

  char *left[2][regions] =  
    {{"eg1h","eg1v","eg4h","eg4v","eg4c","exgt","egfs","egd1","egd2","egfr"}, 
     {"ig1h","ig1v","ig4h","ig4v","ig4c","ingt","igfs","igd1","igd2","igfr"}};

  char *right[2][regions] = 
    {{"ev1h","ev1v","ev4h","ev4v","ev4c","exss","exfs","efd1","efd2","exfr"},
     {"iv1h","iv1v","iv4h","iv4v","iv4c","inss","infs","ifd1","ifd2","infr"}};


  int i, j, k, ii,jj,kk,num_sick,square,temp[2],rows=0, sum=0;
  int Bmap[2][2][regions],*bmap;
  long seed ;
  float percent_sick, capacity;
  char Infile[maxline],Outfile[maxline];

  char *BASE= "/home/bhguest/brent/visual/code/";

  strcpy(Infile,BASE);
  strcat(Infile,"alz.in");
  strcpy(Outfile,BASE);
  strcat(Outfile,"netgenA.in");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }
  outfile = fopen(Outfile,"w");
  
  square = nrow*nrow;

  for(i=0;i<2;i++)
    for(j=0;j<2;j++)
      for(k=0;k<regions;k++)
	Bmap[i][j][k] = -3;

  bmap = new (int [square]);


  percent_sick = atof(argv[1]);
  capacity = atof(argv[2]);
  capacity /= 100.0;

  fscanf(infile,"%ld",&seed);
  num_sick = (int)( nrow*nrow*percent_sick / 100.0);
  if(seed == 0)
    seed = time(NULL);
  srand48(seed);

/*i=0: left hemisphere
  i=1: right hemisphere
*/
  rows = 0;
  for(i=0;i<2;i++)/*see if both hemispheres are involved*/
    {
      fscanf(infile,"%d",&temp[i]);
      if(temp[i] == 1) /*hemisphere[i] is partially turned on*/
	{
	  for(j=0; j<2; j++)
	    Bmap[i][j][0] = -2;
	}
      rows += temp[i];
    }/*end of turning neurons 1/3 of the way on*/

/* j=0 : excitatory units
   j=1 : inhibitory units
*/
 for(j=0;j<2;j++)
    {
      fscanf(infile,"%d",&temp[j]);
      if(temp[j] == 1)
	{ 
	 for(i=0;i<2;i++)
	   {
	     if(Bmap[i][j][0] == -2)
	       Bmap[i][j][0] = -1;
	   }
	}
    }/*end of turning neurons 2/3 of the way on*/

  rows = rows*(temp[0] + temp[1]);

/* we want to count how many regions have sick neurons
   so we can put this sum at the top of the output file*/
  kk = ftell(infile);

  sum =0;
  for(i = 0; i< rows; i++)
    {
      for(k = 0; k< regions; k++)
	{
	  fscanf(infile,"%d", &ii);
	  sum += ii;
	}
    }
  fprintf(outfile, "%d  %d  %g\n",sum, num_sick, capacity);

  /*reposition the file pointer*/
  fseek(infile, kk, 0);
  

/*READ which regions contain sick neurons*/
  for(i=0;i<2;i++)
    for(j=0;j<2;j++)
      {
	if(Bmap[i][j][0] == -1)
	  {
	    for(k=0;k<regions;k++)
	      {
		fscanf(infile,"%d",&Bmap[i][j][k]);
		if(Bmap[i][j][k] == 1)
		  {
		    if(i==0)
		      fprintf(outfile,"%s\n",left[j][k]);
		    if(i==1)
		      fprintf(outfile,"%s\n",right[j][k]);

		    for(ii=0;ii<square;ii++)
		      bmap[ii] = 0;
		    ii = 0;
		    while(ii<num_sick)
		      {
			kk = (int)(drand48() * square);
			if(bmap[kk] == 0)
			  {
			    bmap[kk] = 1;
			    ii++;
			    jj = kk/nrow;
/* for the output, matrix index starts at 1, therefore, we add 1 to the index*/
			    fprintf(outfile,"%d\t%d\n",(jj +1), (kk - jj*nrow + 1));
			  }
		      }/*end of while ii < num_sick */
		  }/* end of if Bmap[i][j][k] == 1*/
	      }/*end of k loop for regions*/
	  }/*end of if Bmap[i][j][0] == -1*/
      }/*end of j loop*/

  fclose(infile);
  fclose(outfile);
}

