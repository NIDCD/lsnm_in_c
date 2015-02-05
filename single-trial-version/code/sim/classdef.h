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

   This file (classdef.h) defines data structures for LSNM simulations


   Author: Malle Tagamets, last updated by Antonio Ulloa on February 4 2015  
* *************************************************************************/

/* Class definitions for node sets and structures */

#include <stdio.h>

// define a structure for each connecting weight
struct WeightStruct {
  int        LearnOn;
  struct NodeSet *Set;
  struct NodeStruct *DestNode;
  float Value;
  float WtVar;
};

// put all weights together in a single class
_CLASSDEF(TWeightClass)
class TWeightClass
{
public:
  int CurMaxWeight;
  int N_Weights;
  int NodeIndex;
  struct WeightStruct *Weight;
  TWeightClass(int nodeindex);
  ~TWeightClass();
  int NewWeight(struct NodeSet *destset, int destnode, float value);

};

// Define a structure for each node or unit in the model
struct NodeStruct {
  int     Index;
  float   Act;
  float   OldAct;
  float   MaxAct;
  float   SumAct;
  float   SumInput;
  float   SumExInput;
  float   SumInhInput;
  float   SumWeight;
  float   Receptor;
  int     Phase;
  float   Output;
  float   Input;
  float   *InputPtr;
  float   *AltInputPtr;
  TWeightClass *InWt;
  TWeightClass *OutWt;
  TWeightClass *AltWt;
};

struct ParamStruct {
  char        Name[SET_NAME_SIZE];
  float     Value;
};

struct VarStruct {
  char        Name[SET_NAME_SIZE];
  float     *Value;
};

// Define a structure for a module or "set of nodes"
struct NodeSet
{
  char SetName[SET_NAME_SIZE];
  FILE *Sfs;
  FILE *Wtfs;
  int SetIndex;
  int WriteOut;
  int WriteWts;
  int Topology;
  int XDim;
  int YDim;
  int NSetParams;
  int NLrnParams;
  struct ParamStruct *Params;
  struct ParamStruct *LrnParams;
  int NSetVars;
  struct VarStruct *Vars;
  int N_Nodes;
  void (*InitSet)(struct NodeSet *Nset);
  void (*OutputRule)(struct NodeSet *Nset);
  void (*InputRule)(struct NodeSet *Nset);
  void (*ActRule)(struct NodeSet *Nset);
  void (*Update)(struct NodeSet *Nset);
  void (*LearnRule)(struct NodeSet *Nset);
  struct NodeStruct *Node;
};

