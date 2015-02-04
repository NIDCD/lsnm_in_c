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

   This file (outfuncs.cc) was last modified on January 18, 2015.


   Author: Malle Tagamets  
* *************************************************************************/

#include "win.h"
#include "simdefs.h"
#include "simproto.h"
#include "classdef.h"
#include "externs.h"
#include "macros.h"

void SumOut(struct NodeSet *Nset) {

  struct NodeStruct *Sourcenode, *Destnode;
  TWeightClass *Weightptr;
  int      j;
  float       output;
  
  for(int i=0; i < SET_NumNodes(Nset); i++) {
    Sourcenode = SET_NodeAddress(Nset,i);
    j = 0;
    while( j < NODE_NumWts(Sourcenode)) {
      Weightptr = NODE_WeightLoc(Sourcenode);
      Destnode = WT_DestNodePtr(Weightptr,j);
      output = WT_Value(Weightptr,j) * NODE_Act(Sourcenode);
      *(NODE_InputLoc(Destnode)) += output;
      // Sum up excitatory and inhibitory outputs separately at
      // the destination node
      if(output > 0.0)
	NODE_SumExInput(Destnode) += output;
      else
	NODE_SumInhInput(Destnode) += output;
      j++;
    }
  }
  return;
}

