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

/* ************************************************************************

   Large-Scale Neural Modeling software (LSNM)

   Section on Brain Imaging and Modeling
   Voice, Speech and Language Branch
   National Institute on Deafness and Other Communication Disorders
   National Institutes of Health

   This file (simulate.cc) was last modified on January 18, 2015.


   Author: Malle Tagamets, last updated by Antonio Ulloa on January 18 2015  
* *************************************************************************/

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "win.h"
#include "simdefs.h"
#include "classdef.h"
#include "externs.h"
#include "simproto.h"
#include "macros.h"


//                   SIMULATE
//              Run the simulation

/***************************************************************/


int simulate(HWND TheWind, FILE *out_fd)


{
   int      iteration, j, n_written;
   DisplayInit(TheWind);
   WriteHeader(out_fd);
   for(j=0; j<N_Sets; j++)  {
     if(Set[j]->InitSet && SET_NumNodes(Set[j]) > 0)
       Set[j]->InitSet(Set[j]);
   }
   for(iteration=1; iteration<=N_Iter; iteration++)   {
     for(j=0; j<N_Sets; j++)   {
       if(Set[j]->OutputRule && SET_NumNodes(Set[j]) > 0)
       Set[j]->OutputRule(Set[j]);
      }
      for(j=0; j<N_Sets; j++)        {
       if(Set[j]->InputRule && SET_NumNodes(Set[j]) > 0)
          Set[j]->InputRule(Set[j]);
      }
      for(j=0; j<N_Sets; j++) {
       if(Set[j]->ActRule && SET_NumNodes(Set[j]) > 0)
          Set[j]->ActRule(Set[j]);
      }
      for(j=0; j<N_Sets; j++)   {
       if(Set[j]->Update && SET_NumNodes(Set[j]) > 0)
          Set[j]->Update(Set[j]);
      }
      for(j=0; j<N_Sets; j++)   {
       if(Set[j]->LearnRule && SET_NumNodes(Set[j]) > 0)
          Set[j]->LearnRule(Set[j]);
      }
      if(WritePet > 0) {
       if((Tot_Iter+iteration)%WritePet == 0)
	      WritePET(Pet_fs);
      }
	  if(WriteAbsPet > 0) {
       if((Tot_Iter+iteration)%WriteAbsPet == 0)
	      Write_APET(Pet_fs);
      }

      n_written = 0;
      for(j=0; j<N_Sets; j++)     {
       if(Set[j]->WriteOut > 0)
          n_written += WriteSet_Matlab(out_fd, Tot_Iter+iteration, Set[j]);
       if(Set[j]->WriteWts > 0)
          WriteWts(out_fd, Tot_Iter+iteration, Set[j]);
      }
   }
   Tot_Iter += N_Iter;


   return(1);
}
