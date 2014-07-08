/* generateC_au.cc 

5/03 BH (modified from generateC.cc rev. 8/98, TWL and generateFatima.cc FTH)
suffix x is related to row index, suffix y is related to column index

The file fiddle.in specifies pairs of regions whose connection weight is to be 
multiplied by a ratio. If ratio < 1.0, connections is weakened.
If ratio > 1.0, connection is strengthened 

*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<math.h>
#include	<string.h>
#define   num_rows 9
#define   unitlen 4
#define   maxlen 80

#include "win.h"
#include "structs.h"
#include "prototyp.h"

struct weights 
{
   int	ix;
   int	iy;
   float  ww;
 };


int netgen(char *Outfile, struct NetGenStruct Net)
{
  time_t t;
  FILE	*ofs, *readfile;
  int	i,j, k, ii, jj, kk;
  int	row, col, orow, ocol;
  int	outx, outy;
  int	n_weights;

  int   num_wt_set;
  float ratio = 1.0;
  char  area_name[unitlen], line[maxlen];

  const char *BASE = getenv("LSNM");

  float	x,y;
  struct weights *wts;

  strcpy(Outfile,BASE);
  strcat(Outfile,"code/netgenC_au.in");

  ofs = fopen(Outfile,"w");


  if( (readfile = fopen(BASE,"r")) == NULL)
    {
      printf("can't open file %s\n",BASE);
      exit(0);
    }
  fscanf(readfile,"%d ",&num_wt_set);

  kk = 0;
  for(i=0; i<num_wt_set && (kk==0); i++)
    {
      fscanf(readfile,"%s",&area_name);
      if( (strcmp(area_name, Net.InSet)) == 0)
	{
	  fscanf(readfile,"%s",&area_name);
	  if( (strcmp(area_name, Net.OutSet)) == 0)
	    {
	      kk =1;
	      fscanf(readfile,"%f",&ratio);
	    }
	  else   /*skip the line */
	    fgets(line,maxlen,readfile);  
	}
      else /*skip the line */
	fgets(line,maxlen,readfile);
    }  


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
	      // printf("row = %d, col = %d \n", row, col);
              //printf("i = %d, j = %d\n", i, j);
              if (j >= Net.oy)  /* if the input col num is greater than max output col num */
		{ 
		  row = (Net.ostarty) / Net.oy ;
                  col = (Net.ostarty- Net.fy/2 + Net.oy) % Net.oy;  
		  //  printf("j = %d, row = %d, col = %d \n", j, row, col);
		}
	    }
	  k = 0;
	  n_weights = 0;
	  for(orow=0; orow < Net.fx; orow++) 
	    {
	      for(ocol=0; ocol < Net.fy; ocol++) 
		{
		  outx = (row+orow)%Net.ox;
		  //printf("row+orow = %d, Net.ox = %d, outx = %d\n", row+orow, Net.ox, outx);
		  outy = (col+ocol)%Net.oy;
		  //printf("col+ocol = %d, Net.oy = %d, outy = %d\n", col+ocol, Net.oy, outy);
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
		      x *= ratio;

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
	      x *= ratio;
	      fprintf(ofs,"    ([%2d,%2d] %9.6f) ",outx+1,outy+1,x);
	    }

	  fprintf(ofs,"  }\n");
	  Net.ostarty += Net.ody;
	  //printf("Net.ostarty = %d, Net.ody = %d\n", Net.ostarty, Net.ody);
	}
      Net.ostartx += Net.odx;
      //printf("Net.ostartx = %d, Net.odx = %d\n", Net.ostartx, Net.odx);
    }
  fprintf(ofs,"}\n");
  fclose(ofs);

  return(0);
}






