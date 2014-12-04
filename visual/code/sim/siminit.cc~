#include <stdio.h>
#include <stdlib.h>

#include "win.h"
#include "simdefs.h"
#include "simproto.h"
#include "classdef.h"
#include "externs.h"

int        init(HWND ThisWind, FILE *ifd, FILE *ofd);


void ClearAll()               //  Clear all current data structures
{
  if(N_Sets <= 0)
     return;
  while(N_Sets-- > 0)
     DeleteNodeSet(Set[N_Sets]);
  CurSet = 0;

  return;
}

int siminit(HWND ThisWind, char *infile, FILE *ofs)
{
     FILE    *in_fd;

/*       Open file for input
     and get out if there is no input file           */

      if( (in_fd = fopen(infile,"r")) == NULL)        {
          sprintf(MsgStr, "Cannot open file %s", infile);
          Errmsg(MsgStr);
          return(NULL);
        }
      if( (Pet_fs = fopen("spec_pet.m","a")) == NULL)        {
          sprintf(MsgStr, "Cannot open file %s", infile);
          Errmsg(MsgStr);
          return(NULL);
       }

  if(init(ThisWind, in_fd, ofs) < 0) {
      fclose(in_fd);
      fclose(Pet_fs);
      Errmsg("Initialization Error");
      return(-1);
   }

  fclose(Pet_fs);
  fclose(in_fd);
  return(1);
      
}

