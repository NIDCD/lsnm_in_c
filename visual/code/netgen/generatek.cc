/* generate.cc 
rev. 6/98, TWL
suffix x is related to row index, suffix y is related to column index
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<string.h>

#include "win.h"
#include "structs.h"
#include "prototyp.h"

struct weights 
{
   int	ix;
   int	iy;
   float  ww;
 };

float kern(int centerx, int centery, int x, int y, int option);

int netgen(char *Outfile, struct NetGenStruct Net)
{
  time_t t;
  FILE	*ofs;
  int	i,j;
  int	row, col, orow, ocol, k;
  int	outx, outy;
  int	n_weights;
  int   option = 0;   /*option = 0, apply gaussian kernel, else step kernel*/
  float	x,y;
  struct	weights *wts;

  ofs = fopen(Outfile,"w");

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

		      /* apply kernel*/
		      x *= kern(j,i,outx,outy,0);
		      /* kernel applied*/

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

	      /* apply kernel*/
	      x *= kern(i,j,outx,outy,option);
	      /* kernel applied*/

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
/**********************************************/

float kern(int centerx, int centery, int x, int y, int option)
{
/* gausian kernel without the normalizing 2*pi*sig^2 because we want the
   weight for the center point to be 1 (before scaling).
   Based on a 9x9 patch, center is at (5,5), if sigma reaches the edge,
   then sigma should be 4.

   option = 0, apply gaussian kernel
   else, kernel is a unit step function
*/

  float sig = 4.0, scale = 1.0, weight;
  float dx, dy;

  if(option == 0)
    {
      dx = (float)(x - centerx);
      dy = (float)(y - centery);

      weight = scale*exp(-(dx*dx + dy*dy)/(2.0*sig*sig));
    }

  else
    weight = 1.0;

  return weight;
}


