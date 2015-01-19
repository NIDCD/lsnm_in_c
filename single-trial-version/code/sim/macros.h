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

   This file (macros.h) was last modified on January 18, 2015.


   Author: Malle Tagamets. Last updated by Antonio Ulloa on January 18 2015  
* **************************************************************************/

/****************************************************************/
/*            Macros for access functions                     */
/****************************************************************/

#include <ctype.h>
#include <math.h>
#include <stdlib.h>

// Define the sigmoid function with gain K

#define SIGMOID(x,K) (1.0 / (1.0 + exp((-K)*x)))

/*  Access functions for set and node attributes    */

#define SET_NumNodes(setp)            (setp->N_Nodes)
#define SET_File(setp)                  (setp->Sfs)
#define SET_WtFile(setp)              (setp->Wtfs)

//#define SET_Write(setp)           (setp->WriteOut)

#define SET_NodeAddress(setp,i)         (&(setp->Node[i]))
#define SET_XDim(setp)                        (setp->XDim)
#define SET_YDim(setp)                      (setp->YDim)
#define SET_Topology(setp)          (setp->Topology)
#define SET_TopNode(setp,i,j)   (&(setp->Node[(i-1)*SET_XDim(setp)+j-1]))
#define SET_TopNodeIndex(setp,i,j)     (((i-1)*SET_XDim(setp))+j-1)
#define SET_TopNodeX(setp,i)          ((int)(i/SET_XDim(setp))+1)
#define SET_TopNodeY(setp,i)           ((int)(i%SET_XDim(setp))+1)
#define SET_Name(setp)                 (setp->SetName)

// Set parameter access functions
#define SET_NumParams(setp)             (setp->NSetParams)
#define SET_ParamAddress(setp)                (setp->Params)
#define SET_ParamName(setp,i)             (setp->Params[i].Name)
#define SET_ParamVal(setp,i)              (setp->Params[i].Value)


// Learning parameters access functions
#define SET_NLrnParams(setp)              (setp->NLrnParams)
#define SET_LrnParamAddress(setp)     (setp->LrnParams)
#define SET_LrnParamName(setp,i)       (setp->LrnParams[i].Name)
#define SET_LrnParamVal(setp,i)                (setp->LrnParams[i].Value)

// Set variable access functions
#define SET_NumVars(setp)             (setp->NSetVars)
#define SET_VarAddress(setp)            (setp->Vars)
#define SET_VarName(setp,i)         (setp->Vars[i].Name)
#define SET_VarValAddress(setp,i)   (setp->Vars[i].Value)
#define SET_VarVal(setp,i,j)               (setp->Vars[i].Value[j])

#define NODE_Index(nodeptr)             (nodeptr->Index)
#define NODE_Act(nodeptr)               (nodeptr->Act)
#define NODE_OldAct(nodeptr)              (nodeptr->OldAct)
#define NODE_MaxAct(nodeptr)           (nodeptr->MaxAct)
#define NODE_SumAct(nodeptr)           (nodeptr->SumAct)
#define NODE_SumInput(nodeptr)         (nodeptr->SumInput)
#define NODE_SumExInput(nodeptr)     (nodeptr->SumExInput)
#define NODE_SumInhInput(nodeptr)  (nodeptr->SumInhInput)
#define NODE_SumWeight(nodeptr)           (nodeptr->SumWeight)
#define NODE_Receptor(nodeptr)              (nodeptr->Receptor)
#define NODE_Phase(nodeptr)          (nodeptr->Phase)

#define NODE_InputLoc(nodeptr)          (nodeptr->InputPtr)
#define NODE_InputVal(nodeptr,i)     (nodeptr->InputPtr[i])
#define NODE_AltInputLoc(nodeptr) (nodeptr->AltInputPtr)
#define NODE_AltInputVal(nodeptr,i)       (nodeptr->AltInputPtr[i])
#define NODE_Output(nodeptr)           (nodeptr->Output)

#define NODE_NumWts(nodeptr)   (nodeptr->OutWt->N_Weights)
#define NODE_NumAltWts(nodeptr)      (nodeptr->AltWt->N_Weights)

#define NODE_WeightLoc(nodeptr)              (nodeptr->OutWt)     // Pointer to weight structure
#define NODE_AltWeightLoc(nodeptr)   (nodeptr->AltWt)   // Pointer to second weight structure

// Macros for accessing  weight structures

#define WT_Learn(weightptr,j) (weightptr->Weight[j].LearnOn == 1)

#define WT_NumWts(weightptr) (weightptr->N_Weights)

#define WT_DestSetPtr(weightptr,j)        (weightptr->Weight[j].Set)

#define WT_DestNodePtr(weightptr,j)   (weightptr->Weight[j].DestNode)
#define WT_DestNodeInput(weightptr,j)    NODE_InputLoc(weightptr->Weight[j].DestNode)
#define WT_DestNodeAltInput(weightptr,j)    NODE_AltInputLoc(weightptr->Weight[j].DestNode)

#define WT_Value(weightptr,j)    (weightptr->Weight[j].Value)
#define WT_WtVar(weightptr,j)       (weightptr->Weight[j].WtVar)
