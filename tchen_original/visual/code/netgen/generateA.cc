/* generateA.cc 
rev. 7/98, TWL
suffix x is related to row index, suffix y is related to column index

   the file netgenA.in specifies which neurons are sick  
need to be in the netgen directory, using the makefile in that directory
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<string.h>
#define   num_rows 9
#define   unitlen 4


#include "win.h"
#include "structs.h"
#include "prototyp.h"

struct weights 
{
   int	ix;
   int	iy;
   float  ww;
 };


netgen(char *Outfile, struct NetGenStruct Net)
{
  time_t t;
  FILE	*ofs, *readfile;
  int	i,j, k, ii, jj, kk;
  int	row, col, orow, ocol;
  int	outx, outy;
  int	n_weights;
  int   num_region, num_sick;

  float	x,y;
  float factord[num_rows][num_rows], capacity;
  char  area_name[unitlen];
  struct weights *wts;

  char *BASE ="/home/bhguest/brent/visual/code/netgenA.in";

  ofs = fopen(Outfile,"w");

/*we need only apply the capacity factor on the weight coming into
  a sick neuron.  This will result in reduced activity of this sick neuron

  all element of the matrix factord is normally set to 1.  If a neuron is sick
  its corresponding position in factord is set to the reduced capacity.
  When we multiply the destination region's incoming weight by factord, only
  the sick neuron will havereducd capacity.
*/
  for(i=0;i<num_rows; i++)
    for(j=0;j<num_rows; j++)
      {
	factord[i][j] = 1.0;
      }


  if( (readfile = fopen(BASE,"r")) == NULL)
    {
      printf("can't open file %s\n",BASE);
      exit(0);
    }
  fscanf(readfile,"%d %d %f",&num_region, &num_sick, &capacity);

  kk = 0;
  for(i=0; i<num_region && (kk==0); i++)
    {
      fscanf(readfile,"%s",&area_name);
      if( (strcmp(area_name, Net.OutSet)) == 0)
	{
	  kk = 1;

/* readfile' index starts from 1, we need to subract 1 from the index
   to make it consistent with the index in the code which starts from 0*/

	  for(j=0; j<num_sick; j++)
	    {
	      fscanf(readfile,"%d %d",&ii,&jj);
		factord[ii-1][jj-1] = capacity;
	    }

	}/* end of if kk = 0*/
    }/*end of i loop */


  time(&t);
  fprintf(ofs, "%% %s\n",ctime(&t));
  fprintf(ofs,"%% Input layer: (%d, %d)\n",Net.ix,Net.iy);
  fprintf(ofs,"%% Output layer: (%d, %d)\n",Net.ox,Net.oy);
  fprintf(ofs,"%% Fanout size: (%d, %d)\n",Net.fx,Net.fy);
  fprintf(ofs,"%% Fanout spacing: (%d, %d)\n",Net.idx,Net.idy);

  if(Net.Type == 'R')
    fprintf(ofs,"%% Random weights:   Scaling = %6.4f   Base value = %6.4f\n\n",
     Net.scale[0], Net.base[0]);
  else if(Net.Type == 'S')
    fprintf(ofs,"%% Specified fanout weights\n\n");
  else if(Net.Type == 'A')
    fprintf(ofs,"%% Absolute weights positions\n\n");

  fprintf(ofs,"Connect(%s, %s)  {\n",Net.InSet,Net.OutSet);
  
  srand48(Net.seed);
  row = col = 0;
  for(i=Net.istartx;i<Net.ix;i+=Net.idx)	
    {
      for(j=Net.istarty;j<Net.iy;j+=Net.idy)	
	{
	  fprintf(ofs,"  From:  (%d, %d)  {\n",i+1,j+1);
	  if(Net.Type == 'S' || Net.Type == 'R') 
	    {
	      row = (Net.ostartx - Net.fx/2 + Net.ox) % Net.ox;
	      col = (Net.ostarty - Net.fy/2 + Net.oy) % Net.oy;
	    }
	  k = 0;
	  n_weights = 0;
	  for(orow=0; orow < Net.fx; orow++) 
	    {
	      for(ocol=0; ocol < Net.fy; ocol++) 
		{
		  outx = (row+orow)%Net.ox;
		  outy = (col+ocol)%Net.oy;

		  x = (float)drand48();
		  if(x < Net.pctzero || Net.base[k] == 0.0) 
		    {
		      /*Verbose output, print blanks at 0 weight locations*/
		      if(Net.OutWrite == 'V')		
			fprintf(ofs,"    | %2s %2s  %6s| "," "," "," ");
		    }
		  else	
		    {
		      x = (float)drand48() - 0.5;
		      x = Net.base[k] + x * Net.scale[k];
		      x *= factord[outx][outy];

		      fprintf(ofs,"    ([%2d,%2d] %9.6f) ",outx+1,outy+1,x);
		      n_weights++;
		    }
		  if(Net.Type == 'S' || Net.Type == 'A')
		    k++;
		}
	      fprintf(ofs,"\n");
	    }
	  /* Make sure we have at least one outgoing weight*/
	  if(Net.pctzero < 1.0 && n_weights == 0) 
	    {
	      k = 0;
	      outx = i/Net.ox;
	      outy = j/Net.oy;
	      x = (float)drand48() - 0.5;
	      x = Net.base[k] + x * Net.scale[k];
	      x *= factord[outx][outy];
	      fprintf(ofs,"    ([%2d,%2d] %9.6f) ",outx+1,outy+1,x);
	    }

	  fprintf(ofs,"  }\n");
	  Net.ostarty += Net.ody;
	}
      Net.ostartx += Net.odx;
    }
  fprintf(ofs,"}\n");
  fclose(ofs);

  return(0);
}

