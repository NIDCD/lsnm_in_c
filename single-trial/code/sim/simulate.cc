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


   Author: Malle Tagamets, last updated by Antonio Ulloa on February 4 2015  
* *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "win.h"
#include "simdefs.h"
#include "classdef.h"
#include "externs.h"
#include "simproto.h"
#include "macros.h"

// Declare a matrix where the neural activities from the TVB simulation
// will be stored.
float tvb_v1[1100][2]; 

/***************************************************************/
//                   SIMULATE
//              Run the simulation
//
/***************************************************************/


int simulate(HWND TheWind, FILE *out_fd)

{

   int iteration, j, n_written;

   FILE *tvb_nodes;

   float excitatory, inhibitory;

   DisplayInit(TheWind);
   WriteHeader(out_fd);

   // the following dumps a TVB file of neural activations into an LSNM array
   // so that we can use it in our LSNM simulation
   tvb_nodes = fopen ("tvb_node.txt", "r");
   if (tvb_nodes!=NULL) {
      for(j=0; j<1100; j++) {
         fscanf(tvb_nodes, "%f %f", &excitatory, &inhibitory);
	 tvb_v1[j][0]=0; // insert variable 'excitatory';
	 tvb_v1[j][1]=0; // insert variable 'inhibitory';
      }
   fclose (tvb_nodes);
   } else
     fprintf(stderr, "Cannot read from tvb_node.txt");

   // the following runs a simulation for N_iter number of iterations
   for(iteration=1; iteration<=N_Iter; iteration++)   {

     // The following computes sum of excitatory and sum of inhibitory activities
     // in destination nodes using source nodes and connecting weights provided
     for(j=0; j<N_Sets; j++)   {
       if(Set[j]->OutputRule && SET_NumNodes(Set[j]) > 0)
       Set[j]->OutputRule(Set[j]);      
     }

     // The following updates neural activity in all nodes using Wilson-Cowan
     for(j=0; j<N_Sets; j++) {
       if(Set[j]->ActRule && SET_NumNodes(Set[j]) > 0)
	 Set[j]->ActRule(Set[j]);
     }

     // the following writes neural activity (PET format) to a single file
     // useful for later computing PET and/or fMRI BOLD 
     if(WritePet > 0) {
       if((Tot_Iter+iteration)%WritePet == 0)
	 WritePET(Pet_fs);
     }
     if(WriteAbsPet > 0) {
       if((Tot_Iter+iteration)%WriteAbsPet == 0)
	 Write_APET(Pet_fs);
     }
     
     // the following writes out neural activity to separate files, one
     // file per module/sub-module
     // But note that only those module that the WriteOut flag ON will
     // be written out.
     n_written = 0;
     for(j=0; j<N_Sets; j++)     {
       if(Set[j]->WriteOut > 0)
	 n_written += WriteSet_Matlab(out_fd, Tot_Iter+iteration, Set[j]);
       if(Set[j]->WriteWts > 0)
	 WriteWts(out_fd, Tot_Iter+iteration, Set[j]);
     }

     // the following global variable keep track of the total number of
     // iteration, i.e, time steps
     Cur_Iter++;
   }

   Tot_Iter += N_Iter;
   printf("\nTotal number of iterations was %d\n", Tot_Iter);
   
   return(1);
}
