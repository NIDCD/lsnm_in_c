/*  
rev. 6/98, TWL
suffix x is related to row index, suffix y is related to column index
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "defs.h"
#include "structs.h"
#include "decls.h"

int     netgen(char *Outfile, struct NetGenStruct Net);

void GetNetSpecs(FILE *fs, struct NetGenStruct *Net)
{
  int k = 0;
  char instr[15];

  Net->istartx = Net->istarty = 0;
  Net->ostartx = Net->ostarty = 0;

  fscanf(fs,"%s %s %s",Net->InSet, Net->OutSet, instr);
  Net->Type = instr[0];
  Net->OutWrite = instr[1];
  fscanf(fs," I(%d %d)",&(Net->ix),&(Net->iy));
  fscanf(fs," O(%d %d)",&(Net->ox),&(Net->oy));
  fscanf(fs," F(%d %d)",&(Net->fx),&(Net->fy));
  fscanf(fs,"%d %f",&(Net->seed),&(Net->pctzero));
  if (Net->seed == 0)
     Net->seed = (int)time(NULL);
  fscanf(fs,"%s",instr);
  if(instr[0] == 'O' || instr[0] == 'o')
    fscanf(fs,"%d %d",&(Net->ostartx),&(Net->ostarty));
  if(Net->Type == 'R') /*supplied with only one base, one scale*/
    {
      Net->scale = (float *)calloc(1, sizeof(*Net->scale));
      Net->base = (float *)calloc(1, sizeof(*Net->base));
      fscanf(fs,"%f %f",Net->base,Net->scale);
      Net->scale[0] *= 2.0;
    }
  else if(Net->Type == 'S' || Net->Type == 'A') 
    {
      fscanf(fs,"\n");
      Net->scale = (float *)calloc((Net->fx)*(Net->fy), sizeof(*Net->scale));
      Net->base = (float *)calloc((Net->fx)*(Net->fy), sizeof(*Net->base));

      for(int x=0; x<Net->fx; x++) 
	{
	  for(int y=0; y<Net->fy;y++) 
	    {
	      fscanf(fs,"%f:%f",&(Net->base[k]),&(Net->scale[k]));
	      Net->scale[k] *= 2.0;
	      k++;
	    }
	  fscanf(fs,"\n");
	}
    }

  else 
    {
      return;
    }
  Net->idx = Net->idy = 1;
  Net->odx = Net->ody = 1;
 
  return;
}

main(int argc, char **argv)
{
  FILE *fs;
  char InFile[120], OutFile[120];
  struct NetGenStruct Network;
  int k;

  if(argv[1] == NULL)
    {
      printf("you forgot to enter the name of the .ws file, bye!\n");
      exit(0);
    }
  strcpy(OutFile, argv[1]);
  strcpy(InFile, argv[1]);
  /* input file is *.ws, outfile is *.w*/
  k = strlen(OutFile);
  OutFile[k-1] = '\0';

  fs = fopen(InFile,"r");
  if(fs == NULL)
    exit;

  GetNetSpecs(fs,&Network);

  netgen(OutFile,Network);

  exit;
}

