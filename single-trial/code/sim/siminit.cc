/*============================================================================
 *
 *                    PUBLIC DOMAIN NOTICE
 *
 *   National Institute on Deafness and Other Communication Disorders
 *
 * This software/database is a "United States Government Work" under the 
 * terms of the United States Copyright Act. It was written as part of 
 * the author's official duties as a United States Government employee and 
 * thus cannot be copyrighted. This software/database is freely available 
 * to the public for use. The NIDCD and the U.S. Government have not placed 
 * any restriction on its use or reproduction. 
 *
 * Although all reasonable efforts have been taken to ensure the accuracy 
 * and reliability of the software and data, the NIDCD and the U.S. Government 
 * do not and cannot warrant the performance or results that may be obtained 
 * by using this software or data. The NIDCD and the U.S. Government disclaim 
 * all warranties, express or implied, including warranties of performance, 
 * merchantability or fitness for any particular purpose.
 *
 * Please cite the author in any work or product based on this material.
 * 
 * ==========================================================================
 *
 */

/* **************************************************************************

   Large-Scale Neural Modeling software (LSNM)

   Section on Brain Imaging and Modeling
   Voice, Speech and Language Branch
   National Institute on Deafness and Other Communication Disorders
   National Institutes of Health

   This file (siminit.cc) was last modified on January 18, 2015.


   Author: Malle Tagamets. Last updated by Antonio Ulloa on January 18 2015  
* **************************************************************************/

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
      Errmsg((char*)"Initialization Error");
      return(-1);
   }

  fclose(Pet_fs);
  fclose(in_fd);
  return(1);
      
}

