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

extern FILE *buggy;
    
/**************************************************************
       Activation Rule  SigAct
    
       Non-differential style sigmoid
    
       Sigmoid rule in which new activation is just sigmoid of
       the (input - threshold).
***************************************************************/
    
#define N_SIG_PARAMS 2
    
#define SIG_K_INDEX                        0
#define SIG_THRESH_INDEX               1
    
#define SIG_K(nset)            SET_ParamVal(nset,SIG_K_INDEX)
#define SIG_THRESH(nset)  SET_ParamVal(nset,SIG_THRESH_INDEX)
    
    
/* The set parameter initilalization function*/
    
void SigInitParams(struct NodeSet *Nset) 
{
    
  if(SET_ParamAddress(Nset) == NULL) 
    {
      SET_ParamAddress(Nset) =
	(struct ParamStruct*)calloc(N_SIG_PARAMS,sizeof(*SET_ParamAddress(Nset)));
      SET_NumParams(Nset) = N_SIG_PARAMS;
      strcpy(SET_ParamName(Nset,SIG_K_INDEX),"k");
      strcpy(SET_ParamName(Nset,SIG_THRESH_INDEX),"thresh");
      SIG_K(Nset) = 10.0;
      SIG_THRESH(Nset) = 0.5;
    }
}
    
/* Initilaization of the sigmoid activation function*/
/* Call once at beginning*/
    
void SigActInit(struct NodeSet *Nset) 
{
    
  struct NodeStruct *Nodeptr;
    
  SigInitParams(Nset);
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
    
void SigAct(struct NodeSet *Nset) 
{
    
  struct NodeStruct *Nodeptr;
    
  for(int i=0; i < SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      NODE_Act(Nodeptr) = SIGMOID((NODE_InputVal(Nodeptr,0) - SIG_THRESH(Nset)),SIG_K(Nset));
      NODE_SumAct(Nodeptr) += NODE_Act(Nodeptr);
      NODE_SumInput(Nodeptr) += fabs(NODE_InputVal(Nodeptr,0));
      NODE_InputVal(Nodeptr,0) = 0.0;
    }
}
    
    
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
    
    
/* ***********   LINEAR ACTIVATION RULE*/
 
#define N_LIN_PARAMS 4
    
#define DELTA_INDEX   0
#define THRESH_INDEX   1
#define DECAY_INDEX    2
#define LIN_NOISE_INDEX 3
    
#define DELTA(nset)    SET_ParamVal(nset,DELTA_INDEX)
#define THRESH(nset)      SET_ParamVal(nset,THRESH_INDEX)
#define DECAY(nset)      SET_ParamVal(nset,DECAY_INDEX)
#define LIN_NOISE(nset)      SET_ParamVal(nset,LIN_NOISE_INDEX)
    
    
/* The set parameter initilalization function  */
    
void LinInitParams(struct NodeSet *Nset) 
{
  if(SET_ParamAddress(Nset) == NULL) 
    {
      SET_ParamAddress(Nset) =
	(struct ParamStruct*)calloc(N_LIN_PARAMS,sizeof(*SET_ParamAddress(Nset)));
      SET_NumParams(Nset) = N_LIN_PARAMS;
      strcpy(SET_ParamName(Nset,DELTA_INDEX),"delta");
      strcpy(SET_ParamName(Nset,THRESH_INDEX),"thresh");
      strcpy(SET_ParamName(Nset,DECAY_INDEX),"decay");
      strcpy(SET_ParamName(Nset,LIN_NOISE_INDEX),"noise");
      DELTA(Nset) = 0.05;
      THRESH(Nset) = 0.2;
      DECAY(Nset) = 0.2;
      LIN_NOISE(Nset) = 0.0;
    }
}
    
/* Initialization of the linear activation function*/
/* Call once at beginning*/
    
void LinActInit(struct NodeSet *Nset) 
{
    
  struct NodeStruct *Nodeptr;
    
  LinInitParams(Nset);
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
    
      
void LinearAct(struct NodeSet *Nset) 
{
  struct NodeStruct *Nodeptr;
  float noise;
    
  for(int i=0; i < SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      noise = (float)drand48() - 0.5;
      noise =  noise * LIN_NOISE(Nset);
      NODE_Act(Nodeptr) -= DECAY(Nset)*NODE_Act(Nodeptr);
      NODE_Act(Nodeptr) += DELTA(Nset)*(NODE_InputVal(Nodeptr,0)-THRESH(Nset)+noise);
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
      NODE_Act(Nodeptr) += 0.0;
      NODE_SumAct(Nodeptr) += NODE_Act(Nodeptr);
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


/* *********** SHIFT Activation Rule: 
               Just shifts the clamped activation by DX every DELTA iterations */
/*             Useful for learning invariance os position of an object   */

#define N_SHIFT_PARAMS 2

#define S_DELTA_INDEX   0
#define S_DX_INDEX   1

#define S_DELTA(nset)   SET_ParamVal(nset,S_DELTA_INDEX)
#define S_DX(nset)      SET_ParamVal(nset,S_DX_INDEX)


/* The set parameter initilalization function*/

void ShiftInitParams(struct NodeSet *Nset) 
{

  if(SET_ParamAddress(Nset) == NULL) 
    {
      SET_ParamAddress(Nset) =
	(struct ParamStruct*)calloc(N_SHIFT_PARAMS,sizeof(*SET_ParamAddress(Nset)));
      SET_NumParams(Nset) = N_SHIFT_PARAMS;
      strcpy(SET_ParamName(Nset,S_DELTA_INDEX),"Delta");
      strcpy(SET_ParamName(Nset,S_DX_INDEX),"Dx");
      S_DELTA(Nset) = 100.0;
      S_DX(Nset) = 1.0;
    }
}

/* Initialization of the Shift activation function*/
/* Call once at beginning*/

void ShiftActInit(struct NodeSet *Nset) 
{

  struct NodeStruct *Nodeptr;

  ShiftInitParams(Nset);
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


void Shift_activation(struct NodeSet *Nset)

{
  struct NodeStruct *Nodeptr;
  int	i, j;

  
  if(Cur_Iter%(int)S_DELTA(Nset))
    return;
  /* First collect current activations into each node's input holder */
  for(i=0; i < SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      j = (int)(i+S_DX(Nset))%SET_NumNodes(Nset);
      NODE_InputVal(Nodeptr,0) = NODE_Act(SET_NodeAddress(Nset,j));
    }
  /* Then set activations to the inputs and reset inputs */
  for(i=0; i < SET_NumNodes(Nset); i++) 
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      NODE_Act(Nodeptr) = NODE_InputVal(Nodeptr,0);
      NODE_InputVal(Nodeptr,0) = 0.0;
    }
  return;
}


