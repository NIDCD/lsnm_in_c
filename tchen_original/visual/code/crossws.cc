/* crossws.cc rev.  8/98*/
/* make the .ws files for cross weights
read from input file crossws.in. 
The input file has two lines for fanout specification.
The 1st line is specification for homologous connection
The 2nd line is for nonhomologous connection
if the originating node is inhibitory, the weight will be converted to
    a negative quantity in the code

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxline 80
#define regions 10

int fanr[2],fanc[2],seed;
float perc, base[2],scale[2];

void  writeo(char *source, char * destination,int connect_type, int R, int L);

int main ()
{
  FILE  *infile;
  int i,j,k,ii,jj;

  char *right[2][regions] = 
    {{"ev1h","ev1v","ev4h","ev4v","ev4c","exss","exfs","efd1","efd2","exfr"},
     {"iv1h","iv1v","iv4h","iv4v","iv4c","inss","infs","ifd1","ifd2","infr"}};

  char *left[2][regions] =  
    {{"eg1h","eg1v","eg4h","eg4v","eg4c","exgt","egfs","egd1","egd2","egfr"}, 
     {"ig1h","ig1v","ig4h","ig4v","ig4c","ingt","igfs","igd1","igd2","igfr"}};

  char Infile[maxline];

  char *BASE= "/home/bhguest/brent/visual";

  strcpy(Infile,BASE);
  strcat(Infile,"/code/crossws.in");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

 fscanf(infile,"%d %f",&seed,&perc);

  for(k = 0; k < 2; k++)
    fscanf(infile,"%d %d %f %f", &fanr[k],&fanc[k],&base[k],&scale[k]);

  for(i = 0; i < regions; i++)
    {
      for(j = 0; j < regions; j++)
	{
	  for(ii = 0; ii < 2; ii++)
	    for(jj = 0; jj < 2; jj++)
	      {
		k = ii*2 + jj;
		  {
		    writeo(right[ii][i],left[jj][j],k,i,j);
		    writeo(left[jj][j],right[ii][i],k,j,i);
		  }
	      }    /*end of jj loop */

	}  /*end of j loop */
    }/*end of i loop */
}

/*-----------------*/

/*connect_type 
   0: excitatory to excitatory
   1: excitatory to inhibitory
   2: inhibitory to excitatory, need change base and scale to negative value
   3: inhibitory to inhibitory, need change base and scale to negative value
 R: index of right region
 L: index of left region
 base and scale are for excitatory to excitatory connections, i.e.
   connect_type = 0.  If connect_type = 2 or 3, we reduce the strength by
   3/4.  If connect_type = 4, we reduce the strength by 5/6.  
   This is consistent with the ratio in the basic unit.
*/
void  writeo(char *source, char * destination, int connect_type, int R, int L)
  {
    FILE *outfile;
    char fname[maxline];
    int i, j;

    extern int fanr[2],fanc[2],seed;
    extern float perc, base[2],scale[2];
    int fanr0,fanc0;
    float base0,scale0;

    strcpy(fname,source);
    strcat(fname,destination);
    strcat(fname,".ws");

    if(R == L) /*homologous and connect_type = 0*/
      {
	fanr0 = fanr[0];
	fanc0 = fanr[0];
	base0 = base[0];
	scale0 = scale[0];
      }
    else /*nohomologous and connect_type = 0 */
      {
	fanr0 = fanr[1];
	fanc0 = fanr[1];
	base0 = base[1];
	scale0 = scale[1];
      }

    if(connect_type == 1) /*ex to in */
      {
	base0 /=4.0;
	scale0 /= 4.0;
      }
    if (connect_type == 2) /*inhibitory to excitatory*/
      {
	base0 /= -4.0;
	scale0 /= -4.0;
      }
    if (connect_type == 3) /*inhibitory to inhibitory*/
      {
	base0 /= -6.0;
	scale0 /= -6.0;
      }

    if(seed != 0)
      seed ++;
    outfile = fopen(fname,"w");
    fprintf(outfile,"%s %s SV I(9 9) O(9 9) F(%d %d) %d %g Offset: 0 0\n",
                     source,destination,fanr0,fanc0,seed,perc);
    for(i = 0; i < fanr0; i++)
      {
	for(j = 0; j < fanc0; j++)
	  fprintf(outfile,"%10.6f:%10.6f ",base0,scale0);
	fprintf(outfile,"\n");
      }
    fclose(outfile);
  }

