/* 5/03 BH (modified from crosswt_i.cc by TWL)*/
/*crosswt_au_i.cc, use g++ compiler
read from an input file crosswt_au_i.in
The 1st line of crosswt_au_i.in specifies which version of netgen we want to
use in generating .w files

generates a weight list for cross connection between the left and right brain.
There is a basic set of homologous connections
The rest of the left and right connections can be either randomly selected or
specified

This weight list is in the same form as the original weightlist.txt when
we were doing the right hemisphere only

We also make a shell file sh_cross which specifies how to generate the
weight files listed in crosslist.txt

Because there are several versions of netgen1 (netgen1, netgenA, netgenC),
we make netgen a command line input so we can use it in a shell
script for batch file.
e.g.  if we want to use netgen1, at the system prompt:
crosswt_i netgen1 seed

seed is the seed for random number generator.  If there is no
seed at the command line, system clock will be the seed.

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

void connected(FILE *outfile,char line[],char* source, char **destination,int sourceindex, short ** bitmap, char* netgen);

int main(int argc, char** argv)
{
  FILE *infile, *outfile;
  char *right[2][regions] = 
    {{"ea1u","ea1d","ea2u","ea2d","ea2c","estg","exfs","efd1","efd2","exfr"},
     {"ia1u","ia1d","ia2u","ia2d","ia2c","istg","infs","ifd1","ifd2","infr"}};

  char *left[2][regions] =  
    {{"eg1u","eg1d","eg2u","eg2d","eg2c","egtg","egfs","egd1","egd2","egfr"}, 
     {"ig1u","ig1d","ig2u","ig2d","ig2c","igtg","igfs","igd1","igd2","igfr"}};

  int i,j,k,ex_in,itemp,ii,jj;
  short ***Bmap;
  long int seed = time(NULL);
  char rangen, inchar,line[maxline],area[2];
  char Infile[maxline], netgen[maxline];
  float p;

  char *BASE= "/home/bhguest/sgihome/tchen/auditory/";

  strcpy(netgen,BASE);
  strcat(netgen,"bin/");
  if(argv[1] != NULL)
    strcat(netgen, argv[1]);
  else strcat(netgen,"netgen1");

  if(argc == 3)
    seed = (long)atoi(argv[2]);
  srand48(seed);


  strcpy(Infile,BASE);
  strcat(Infile,"code/crosswt_au_i.in");
  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }

  outfile = fopen("aucrosslist.txt", "w");
 shfile = fopen("sh_cross", "w");
  fprintf(outfile, "%% cross connecting weights between left and right hemispheres\n");
  fprintf(shfile, "#\n#\n#\n");
  
  fscanf(infile, "%d %d",&i, &ex_in);

 switch(i)
    {
    case 1:
      strcpy(area,"A1");
      startregion = 0;
      break;
    case 2:
      strcpy(area,"A2");
      startregion = 2;
      break;
    case 3:
      strcpy(area,"ST");
      startregion = 5;
      break;
    case 4:
      strcpy(area,"PF");
      startregion = 6;
      break;
    }

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
  Bmap = new (short (**[itemp]));
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

  while( (inchar = getc(infile)) == ' ' || inchar == '\n');
  rangen = inchar;

  if(rangen == 'y')
    {
      fscanf(infile, "%f",&p);
      if( (p < 0) || (p > 100) )
	{
	  printf("%f is out of range\n", p);
	  exit(0);
	}
      p /= 100.0;

      fprintf(outfile,
	"\n%%homologous connection between hemispheres\n");

      for( k = 0; k < regions; k++)
	{
	  for(i=0; i<ex_in; i++)
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
	} /* end of homologous excitatory connection */

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
		  }/*end of jj lool*/
	    }/*end of j loop*/

	}/* end of k loop */

    }/* end of if rangen == 'y' */

  else /*select connections individually*/
    {
      /*get rid of the return so that we can do the line by line reading*/
      if( (inchar = getc(infile)) != '\n') ungetc(inchar,infile); 

      for( k = startregion; k < regions; k++)
	{
	  /*excitatory connections only*/
	  fgets(line,maxline,infile);
	  connected(outfile,line,right[0][k],left[0],k,Bmap[0],netgen);

	  if(ex_in == 2)
	    {
	      fgets(line,maxline,infile);
	      connected(outfile,line,right[0][k],left[1],k,Bmap[1],netgen);

	      fgets(line,maxline,infile);
	      connected(outfile,line,right[1][k],left[0],k,Bmap[2],netgen);

	      fgets(line,maxline,infile);
	      connected(outfile,line,right[1][k],left[1],k,Bmap[3],netgen);

	    }/* end of if ex_in ==2 */
	  
	}/* end of k loop */

    }/* end of else for specified connections*/

	    
  for(k = 0; k< itemp; k++)
    {
      for(i = 0; i<regions; i++)
	{
	  delete [](Bmap[k][i]);
	}
      delete [] Bmap[k];
    }

  delete Bmap;

  fclose(infile);
  fclose(outfile);
  fclose(shfile);
}
/*---------------------------------------------*/
void  connected(FILE *outfile,char line[],char* source, char **destination,
                int sourceindex,short** Bmap, char* netgen)
{
  int i= 0,j,k, t = 1;
  char cs[10];

/*index in this code starts at 0, however, at user interface, we let the user
use index starting at 1. Therefore, we  subtract the destination index by 1
so that the user's indication is consistent with the index in the code
*/
  if( line == NULL || line[0] == '\n'|| line[0] == '0')
    return;
  while(t)
    {

      if(isdigit(line[i]))
	{

	  k =i;
	  while( (line[i] != ' ') && (line[i] != '\n') && (line[i] != '\0'))
	    {
	      cs[i-k] = line[i];
	      i++;
	    }
	  cs[i-k] = '\0';
	  j = atoi(cs) - 1;

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
	      Bmap[sourceindex][j] = 1;
	      /*write the shell command for making .w from .ws file*/
	      fprintf(shfile,"%s %s%s.ws\n",netgen,
		      source,destination[j]);  /*forward*/
	      fprintf(shfile,"%s %s%s.ws\n",netgen,
		      destination[j],source);  /*feedback*/

	    }
	}

      while( (line[i]==',') || (line[i]==' ') )
	i++;

      if( (line[i] == '\n') || (line[i] == '\0') )
	t = 0;
    }
}
      







