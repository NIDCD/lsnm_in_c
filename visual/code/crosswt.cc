/* rev.  8/98,  TWL*/
/*crosswt.cc use g++ compiler
input from screen

generates a weight list for cross connection between the left and right brain.
There is a basic set of excitatory to excitatory connections between
each region and its counter part.
The rest of the left and right connections can be either randomly selected
or specified

This weight list is in the same form as the original weightlist.txt when
we were doing the right hemisphere only

The destination address for the weight files is relative to where sim1
is invoked. We assume that sim1 is invoked at /u1/optic/fmri

We also make a shell file sh_cross  which uses netgen1 to generate the
weight files listed in crosslist.txt.  Relative address is used for
netgen1 which is in /u1/optic/fmri, and the cross weights are
in /u1/optic/fmri/weights/cross

*/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define regions 10
#define maxline 80
#define probability drand48()
int startregion;

FILE *shfile;

void connected(FILE *outfile,char* source, char **destination,
                int sourceindex, short** Bmap, char *netgen);
char ask(char *source, char **destination, int in, int n);

void main()
{
  FILE *outfile;
  char *right[2][regions] = 
    {{"ev1h","ev1v","ev4h","ev4v","ev4c","exss","exfs","efd1","efd2","exfr"},
     {"iv1h","iv1v","iv4h","iv4v","iv4c","inss","infs","ifd1","ifd2","infr"}};

  char *left[2][regions] =  
    {{"eg1h","eg1v","eg4h","eg4v","eg4c","exgt","egfs","egd1","egd2","egfr"}, 
     {"ig1h","ig1v","ig4h","ig4v","ig4c","ingt","igfs","igd1","igd2","igfr"}};

  int i,j,k,ex_in,itemp,ii,jj;
  short ***Bmap;
  long int seed = time(NULL);
  char rangen, area[2], netgen[maxline], temp[maxline];
  float p;

  const char *BASE= getenv("LSNM");

  strcpy(netgen,BASE);

  outfile = fopen("crosslist.txt", "w");
  fprintf(outfile, "%% cross connecting weights between left and right hemisphers\n");
  shfile = fopen("sh_cross", "w");
  fprintf(shfile, "#\n#\n#\n");

  printf("enter name of generator, e.g. netgen1\n");
  scanf("%s",temp);
  strcat(netgen,temp);

  printf("Enter the index of the first region to start random connection\n 1:V1/V2, 2:V4, 3:IT, 4:Prefrontal\n");
  scanf("%d",&i);
  switch(i)
    {
    case 1:
      strcpy(area,"V1");
      startregion = 0;
      break;
    case 2:
      strcpy(area,"V4");
      startregion = 2;
      break;
    case 3:
      strcpy(area,"IT");
      startregion = 5;
      break;
    case 4:
      strcpy(area,"PF");
      startregion = 6;
      break;
    }

  printf("Enter 1 or 2 where 1 => excitatory connections only,\n");
  printf("      2 => both excitatory and inhibitory connections\n");
  scanf("%d",&ex_in);
  if( (ex_in != 1) && (ex_in != 2) )
    {
      printf("choice of %d is out of range\n", ex_in);
      exit(0);
    }

  if(ex_in == 1)  /*excitatory-excitatory*/
    {
      itemp = 1;
      fprintf(outfile,"%%excitatory cross connections only\n");
    }

  else            /*excitatory & inhibitory, 4 types of connection*/
    {
      itemp = 4;
      fprintf(outfile,
        "%%cross connection with excitatory and inhibitory units\n");
    }
/*Bmap[0]:ex <--> ex
  Bmap[1]:ex <--> in
  Bmap[2]:in <--> ex
  Bmap[3]:in <--> in
*/
  
  Bmap = new (short(**[itemp]));
  for(k = 0; k < itemp; k++)
    {
      Bmap[k] = new (short (*[regions]));
      for(i = 0; i < regions; i++)
	{
	  Bmap[k][i] = new (short [regions]);
	  for(j = 0; j < regions; j++)
	    Bmap[k][i][j] = 0;
	}
    }

  printf("Do you want connections randomly generated?  (y or n)\n ");

/*need to use the while loop for character input because space or any
control charcters are interpreted as character.  thus the program
may terminate when it gets a space which is neither 'y' nor 'n'
*/
  while ( (rangen = getchar())!= 'y' && rangen != 'n');

  if(rangen == 'y')
    {
      printf("Enter the %% of connections (between 0 and 100):\n");
      scanf("%f",&p);
      if( (p < 0) || (p > 100) )
	{
	  printf("%f is out of range\n", p);
	  exit(0);
	}
      p /= 100.0;

      printf("Enter an integer seed. If seed=0, sys clock is default seed\n");
      scanf("%d",&i);
      if(i != 0)  seed = (long)i;
      srand48(seed);


      fprintf(outfile,
       "\n%%homologous connection between hemispheres\n");

      for( k = 0; k < regions; k++)
	{
	  for(i=0; i < ex_in; i++)
	    {
	      fprintf(outfile,"#include weights/cross/%s%s.w\n",
		      left[i][k],right[i][k]);  /*forward*/
	      fprintf(outfile,"#include weights/cross/%s%s.w\n",
		      right[i][k],left[i][k]);  /*feedback*/
	      Bmap[i][k][k] = 1;
	      /*write the shell command for making .w from .ws file*/
	      fprintf(shfile,"%s %s%s.ws\n",netgen,
		      left[i][k],right[i][k]);  /*forward*/
	      fprintf(shfile,"%s %s%s.ws\n",netgen,
		      right[i][k],left[i][k]);  /*feedback*/


	    }
	} /* end of homologous  connection */

      fprintf(outfile,
  "\n%%nonhomologous connection with probability %g\n\n",p);

  
      fprintf(outfile,
      "%%First region in visual path for nonhomologous connection is %s\n",area);

      for( k = startregion; k < regions; k++)
	{
	  for(j = startregion; j < regions; j++) 
	    {
	      for(ii=0; ii<ex_in; ii++)
		for(jj=0; jj<ex_in; jj++)
		  {
		    i = ii*2 + jj;
		    if(probability <= p && Bmap[i][k][j] == 0 )
		      {
			fprintf(outfile,"#include weights/cross/%s%s.w\n",
			    left[ii][k],right[jj][j]);  /*forward*/
			fprintf(outfile,"#include weights/cross/%s%s.w\n",
			    right[jj][j],left[ii][k]);  /*feedback*/

			Bmap[i][k][j] = 1;

	      /*write the shell command for making .w from .ws file*/
	      fprintf(shfile,"%s %s%s.ws\n",netgen,
		      left[ii][k],right[jj][j]);  /*forward*/
	      fprintf(shfile,"%s %s%s.ws\n",netgen,
		      right[jj][j],left[ii][k]);  /*feedback*/


		      }
		  }/*end of jj loop*/
	    }/*end of j loop*/

	}/* end of k loop */

    }/* end of if rangen == 'y' */

  if(rangen == 'n') /*select connections individually*/
    {
      
      for( k = startregion; k < regions; k++)
	{
	  /*excitatory connections only*/
	  connected(outfile,right[0][k],left[0],k,Bmap[0],netgen);

	  if(ex_in == 2)
	    {
	      /*ex to in */
	      printf("excitatory to inhibitiry connection\n");
	      connected(outfile,right[0][k],left[1],k,Bmap[1],netgen);


	      /*in to ex*/
	      printf("inhibitory to excitatory connection\n");
	      connected(outfile,right[1][k],left[0],k,Bmap[2],netgen);

	      /*in to in*/
	      printf("inhibitory to inhibitory connection\n");
	      connected(outfile,right[1][k],left[1],k,Bmap[3],netgen);
	    }/* end of if ex_in ==2 */

	}/* end of k loop */

    }/* end of else for specified connections*/

  for(k=0; k< itemp; k++)
    {
      for(i=0; i< regions; i++)
	delete [] Bmap[k][i];
      delete [] Bmap[k];
    }
  delete Bmap;

  fclose(outfile);
}
      
/*---------------------------------------------*/
void  connected(FILE *outfile,char* source, char **destination,
                int sourceindex,short** Bmap, char *netgen)
{
  int i= 0,j,k=0, t = 1;
  char cs[10], line1[maxline],line[maxline] ;

/*index in this code starts at 0, however, at user interface, we let the user
use index starting at 1. Therefore, we subtract the destination index by 1
so that the user's indication is consistent with the index in the code
*/

/*the function gets(), unlike fgets(), appends '\0' at end instead of '\n'*/
  line[0] = ask(source,destination, sourceindex, regions);

  if(isdigit(line[0]))
    line[1] = '\0';
  else line[0] == '\0';
  gets(line1);

  strcat(line,line1);

  while(t)
    {
      if(isdigit(line[i]))
	{
	  k = i;
	  while( isdigit(line[i]))
	    {
	      cs[i-k] = line[i];
	      i++;
	    }
	  cs[i-k] = '\0';

	  j = atoi(cs) - 1;

	  if(j < 0) /*user entered a 0 for no choice*/
	    return;

	  /* j+1 is for user's index*/
	  if(j > (regions-1) )
	    {
	      printf("you have selected an out of range index %d\n",j+1);
	      exit(0);
	    }

	  if(Bmap[sourceindex][j] == 0)
	    {
	      fprintf(outfile,
               "#include weights/cross/%s%s.w\n",source,destination[j]);
	      fprintf(outfile,
               "#include weights/cross/%s%s.w\n",destination[j],source);
	      Bmap[sourceindex][j]  = 1;
	      /*write the shell command for making .w from .ws file*/
	      fprintf(shfile,"%s %s%s.ws\n",netgen,
		      source,destination[j]);  /*forward*/
	      fprintf(shfile,"%s %s%s.ws\n",netgen,
		      destination[j],source);  /*feedback*/

	    }
	}

      while( (line[i]==',') || (line[i]==' ') )
	i++;

      if(line[i] == '\n' || line[i] == '\0')
	t = 0;
    }
  return;
}

/*---------------------------------------------*/
char ask(char *source, char **destination, int sourceindex, int n)
{
  int j, k;
  char cs;
  extern int startregion;

  /* sourceindex+1 is for user's index*/
  sourceindex += 1;
  k = (n - startregion)/2;

  /* k is used to cut the print list into two small lists, which
     looks better on the screen*/

  printf("\nCONNECT right region %d (%s) to regions in left side.\n",sourceindex,source);
  printf("Indexed left regions are:\n");

  for(j = startregion; j < k; j++)
    {
      printf("%d:%s, ",(j+1),destination[j]);
    }
  printf("\n");

  for(j = k; j < n; j++)
    {
      printf("%d:%s, ",(j+1),destination[j]);
    }
  printf("\n");

  printf("Select indices of left side regions to be connected\n");
  printf("       as a sequence of numbers separated by a space.\n");
  printf("       enter 0 if no connection is desired\n");
  /*It seems that the first time
   ask is acitvated, the code gets out of her too quick before
   we get a chance to read the screen so we use while lop to slow it down
   so we*/

  while(!isdigit(cs = getchar()) );

  return cs;
}

/*---------------------------------------------*/





