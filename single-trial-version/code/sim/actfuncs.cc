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

   This file: actfuncs.cc
   Author: Malle Tagamets
   Last updated by Antonio Ulloa on January 18 2015  
* *************************************************************************/


#include <string.h>
#include <stdlib.h>
#include <time.h>
#include  <math.h>
    
#include "win.h"
#include "simdefs.h"
#include "simproto.h"
#include "classdef.h"
#include "externs.h"
#include "macros.h"

/**************************************************************
       Activation Rule  DSigAct
    
       Differential equation style sigmoid
    
       Sigmoid rule which adds sigmoid of (input - threshold)
       to old activation, and subtracts decay * old activation.
***************************************************************/
    
#define N_DSIG_PARAMS 5
    
#define DSIG_K_INDEX                   0
#define DSIG_THRESH_INDEX              1
#define DSIG_DELTA_INDEX               2
#define DSIG_DECAY_INDEX               3
#define DSIG_NOISE_INDEX               4
    
#define DSIG_K(nset)           SET_ParamVal(nset,DSIG_K_INDEX)
#define DSIG_THRESH(nset)        SET_ParamVal(nset,DSIG_THRESH_INDEX)
#define DSIG_DELTA(nset)    SET_ParamVal(nset,DSIG_DELTA_INDEX)
#define DSIG_DECAY(nset)     SET_ParamVal(nset,DSIG_DECAY_INDEX)
#define DSIG_NOISE(nset)     SET_ParamVal(nset,DSIG_NOISE_INDEX)
    
    
/* The set parameter initilalization function*/
    
void DSigInitParams(struct NodeSet *Nset) 
{
    
  if(SET_ParamAddress(Nset) == NULL) 
    {
      SET_ParamAddress(Nset) =
	(struct ParamStruct*)calloc(N_DSIG_PARAMS,sizeof(*SET_ParamAddress(Nset)));
      SET_NumParams(Nset) = N_DSIG_PARAMS;
      strcpy(SET_ParamName(Nset,DSIG_K_INDEX),"K");
      strcpy(SET_ParamName(Nset,DSIG_THRESH_INDEX),"thresh");
      strcpy(SET_ParamName(Nset,DSIG_DELTA_INDEX),"delta");
      strcpy(SET_ParamName(Nset,DSIG_DECAY_INDEX),"decay");
      strcpy(SET_ParamName(Nset,DSIG_NOISE_INDEX),"noise");
      DSIG_K(Nset) = 10.0;
      DSIG_THRESH(Nset) = 0.5;
      DSIG_DELTA(Nset) = 0.1;
      DSIG_DECAY(Nset) = 0.1;
      DSIG_NOISE(Nset) = 0.0;
    }
}
    
/* Initialization of the sigmoid activation function*/
/* Call once at beginning*/
    
void DSigActInit(struct NodeSet *Nset) 
{
    
  struct NodeStruct *Nodeptr;
    
  DSigInitParams(Nset);
  for(int i=0; i<SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      NODE_OldAct(Nodeptr) = NODE_Act(Nodeptr);
      NODE_SumAct(Nodeptr) = 0.0;
      NODE_SumInput(Nodeptr) = 0.0;
      NODE_SumExInput(Nodeptr) = 0.0;
      NODE_SumInhInput(Nodeptr) = 0.0;
      
    }

}
    
void DSigAct(struct NodeSet *Nset) 
{
    
  struct NodeStruct *Nodeptr;
  float  invalue, rval;
    
  for(int i=0; i < SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      invalue = NODE_InputVal(Nodeptr,0) - DSIG_THRESH(Nset);
      rval = (float)drand48() - 0.5;
      invalue +=  rval * DSIG_NOISE(Nset);
      invalue = SIGMOID(invalue,DSIG_K(Nset));
      NODE_Act(Nodeptr) += DSIG_DELTA(Nset)*invalue - DSIG_DECAY(Nset)*NODE_Act(Nodeptr);
      NODE_SumAct(Nodeptr) += NODE_Act(Nodeptr);
      NODE_SumInput(Nodeptr) += fabs(NODE_InputVal(Nodeptr,0));
      NODE_InputVal(Nodeptr,0) = 0.0;
    }
}
    
    
/********* TVB activation matrix ****************/
#define TVB_PARAMS 0

void TvbInitParams(struct NodeSet *Nset)
{

  if(SET_ParamAddress(Nset) == NULL) 
    {
      SET_ParamAddress(Nset) =
	(struct ParamStruct*)calloc(TVB_PARAMS,sizeof(*SET_ParamAddress(Nset)));
      SET_NumParams(Nset) = TVB_PARAMS;
    }
}

/* Initializaton of the TVB activation function */
/* Call once at the beginning */
void TvbActInit(struct NodeSet *Nset)
{

  struct NodeStruct *Nodeptr;

  TvbInitParams(Nset);
  for(int i=0; i<SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      NODE_OldAct(Nodeptr) = NODE_Act(Nodeptr);
      NODE_SumAct(Nodeptr) = 0.0;
      NODE_SumInput(Nodeptr) = 0.0;
      NODE_SumExInput(Nodeptr) = 0.0;
      NODE_SumInhInput(Nodeptr) = 0.0;
    }

}

void TvbAct(struct NodeSet *Nset)
{

  struct NodeStruct *Nodeptr;

  for(int i=0; i < SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      NODE_Act(Nodeptr) = 0.0;
      NODE_SumAct(Nodeptr) = NODE_Act(Nodeptr);
      NODE_SumInput(Nodeptr) += fabs(NODE_InputVal(Nodeptr,0));
      NODE_InputVal(Nodeptr,0) = 0.0;
    }

}



/* ***********   CLAMP WITH NOISE */

#define N_C_PARAMS 1

#define C_NOISE_INDEX 0

#define C_NOISE(nset)      SET_ParamVal(nset,C_NOISE_INDEX)


/* The set parameter initilalization function*/

void ClampInitParams(struct NodeSet *Nset) 
{

  if(SET_ParamAddress(Nset) == NULL) 
    {
      SET_ParamAddress(Nset) =
	(struct ParamStruct*)calloc(N_C_PARAMS,sizeof(*SET_ParamAddress(Nset)));
      SET_NumParams(Nset) = N_C_PARAMS;
      strcpy(SET_ParamName(Nset,C_NOISE_INDEX),"noise");
      C_NOISE(Nset) = 0.0;
    }
}

/* Initialization of the linear activation function*/
/* Call once at beginning*/

void ClampActInit(struct NodeSet *Nset) 
{

  struct NodeStruct *Nodeptr;
  
  ClampInitParams(Nset);
  for(int i=0; i<SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      NODE_OldAct(Nodeptr) = NODE_Act(Nodeptr);
      NODE_SumAct(Nodeptr) = 0.0;
      NODE_SumInput(Nodeptr) = 0.0;
      NODE_SumExInput(Nodeptr) = 0.0;
      NODE_SumInhInput(Nodeptr) = 0.0;

    }
}

void ClampAct(struct NodeSet *Nset) 
{

  struct NodeStruct *Nodeptr;
  float noise;

  for(int i=0; i < SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      noise = (float)drand48() - 0.5;
      noise =  noise * C_NOISE(Nset);
      NODE_Act(Nodeptr) = NODE_OldAct(Nodeptr) + noise;
      NODE_SumAct(Nodeptr) += NODE_Act(Nodeptr);
      NODE_SumInput(Nodeptr) += fabs(NODE_InputVal(Nodeptr,0));
      NODE_InputVal(Nodeptr,0) = 0.0;
    }
}
