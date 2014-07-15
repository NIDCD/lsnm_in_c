#include <string.h>

#include "win.h"
#include "simdefs.h"
#include "simproto.h"
#include "classdef.h"
#include "externs.h"
#include "macros.h"

// ******************  AFFERENT HEBB RULE

// Total number of learning parameters

#define N_AHEBB_PARAMS 4

// Define indexes of learning paraneters

#define PRE_THRESH_INDEX  0
#define POST_THRESH_INDEX      1
#define L_DELTA_INDEX          2
#define WT_SCALE_INDEX         3

// Define access macros for learning parameters

#define PRE_THRESH(nset)        SET_LrnParamVal(nset,PRE_THRESH_INDEX)
#define POST_THRESH(nset) SET_LrnParamVal(nset,POST_THRESH_INDEX)
#define L_DELTA(nset)            SET_LrnParamVal(nset,L_DELTA_INDEX)
#define WT_SCALE(nset)               SET_LrnParamVal(nset,WT_SCALE_INDEX)


// The learning parameter initilalization function

void AHebbInitParams(struct NodeSet *Nset) {

   if(SET_LrnParamAddress(Nset) == NULL) {
     SET_LrnParamAddress(Nset) =
       (struct ParamStruct*)calloc(N_AHEBB_PARAMS,sizeof(*SET_LrnParamAddress(Nset)));
     SET_NLrnParams(Nset) = N_AHEBB_PARAMS;
     strcpy(SET_LrnParamName(Nset,PRE_THRESH_INDEX),"L_PreThresh");
     strcpy(SET_LrnParamName(Nset,POST_THRESH_INDEX),"L_PostThresh");
     strcpy(SET_LrnParamName(Nset,POST_THRESH_INDEX),"L_Delta");
     strcpy(SET_LrnParamName(Nset,WT_SCALE_INDEX),"Wt_Scale");
     PRE_THRESH(Nset) = 0.0;
     POST_THRESH(Nset) = 0.0;
     L_DELTA(Nset) = 0.001;
     WT_SCALE(Nset) = 1.0;
   }
}

// Initilaization of the sigmoid activation function
// Call once at beginning

void AHebbInit(struct NodeSet *Nset) {

   struct NodeStruct *Nodeptr;

   AHebbInitParams(Nset);
}


// Normalized afferent Hebbian learning rule

void NormAffHebb(struct NodeSet *Nset) {

  struct NodeStruct *Sourcenode, *Destnode;
  TWeightClass *Weightptr;
  float        dpre, dpost, x;
  int i, j;

  for(i=0; i < SET_NumNodes(Nset); i++) {
    Sourcenode = SET_NodeAddress(Nset,i);
    Weightptr = NODE_WeightLoc(Sourcenode);
    j = 0;
    while(j < NODE_NumWts(Sourcenode)) {
      if(WT_Learn(Weightptr,j)) {
        Destnode = WT_DestNodePtr(Weightptr,j);
        dpre = NODE_Act(Sourcenode) - PRE_THRESH(Nset);
        dpost = NODE_Act(Destnode) - POST_THRESH(Nset);
        if(dpre > 0.0 || dpost > 0.0) {
          x =  WT_Value(Weightptr,j) + L_DELTA(Nset) * dpre*dpost;
          NODE_SumWeight(Destnode) += x;
          WT_Value(Weightptr,j) = x;
        }
      }
      j++;
    }
  }

  // Normalize weights

  for(i=0; i < SET_NumNodes(Nset); i++) {
    Sourcenode = SET_NodeAddress(Nset,i);
    Weightptr = NODE_WeightLoc(SET_NodeAddress(Nset,i));
    j = 0;
    while(j < NODE_NumWts(Sourcenode)) {
      if(WT_Learn(Weightptr,j)) {
       Destnode = WT_DestNodePtr(Weightptr,j);
        NODE_SumWeight(Destnode) = fabs(NODE_SumWeight(Destnode));
        if(NODE_SumWeight(Destnode) > 0.0) {
          WT_Value(Weightptr,j) /= NODE_SumWeight(Destnode);
          WT_Value(Weightptr,j) *= WT_SCALE(Nset);
        }
      }
      j++;
    }
  }
  // Rezero the summed input weights at destination nodes
  for(i=0; i < SET_NumNodes(Nset); i++) {
    Sourcenode = SET_NodeAddress(Nset,i);
    Weightptr = NODE_WeightLoc(SET_NodeAddress(Nset,i));
    j = 0;
    while(j < NODE_NumWts(Sourcenode)) {
      NODE_SumWeight(WT_DestNodePtr(Weightptr,j)) = 0.0;
      j++;
    }
  }
  return;
}





// **************   EFFERENT HEBB RULE

// Total number of learning parameters

#define N_EHEBB_PARAMS 4

// Define indexes of learning paraneters

#define PRE_THRESH_INDEX  0
#define POST_THRESH_INDEX      1
#define L_DELTA_INDEX          2
#define WT_SCALE_INDEX         3

// Define access macros for learning parameters

#define PRE_THRESH(nset)        SET_LrnParamVal(nset,PRE_THRESH_INDEX)
#define POST_THRESH(nset) SET_LrnParamVal(nset,POST_THRESH_INDEX)
#define L_DELTA(nset)            SET_LrnParamVal(nset,L_DELTA_INDEX)
#define WT_SCALE(nset)               SET_LrnParamVal(nset,WT_SCALE_INDEX)


// The learning parameter initilalization function

void EHebbInitParams(struct NodeSet *Nset) {

   if(SET_LrnParamAddress(Nset) == NULL) {
     SET_LrnParamAddress(Nset) =
       (struct ParamStruct*)calloc(N_EHEBB_PARAMS,sizeof(*SET_LrnParamAddress(Nset)));
     SET_NLrnParams(Nset) = N_EHEBB_PARAMS;
     strcpy(SET_LrnParamName(Nset,PRE_THRESH_INDEX),"L_PreThresh");
     strcpy(SET_LrnParamName(Nset,POST_THRESH_INDEX),"L_PostThresh");
     strcpy(SET_LrnParamName(Nset,POST_THRESH_INDEX),"L_Delta");
     strcpy(SET_LrnParamName(Nset,WT_SCALE_INDEX),"Wt_Scale");
     PRE_THRESH(Nset) = 0.0;
     POST_THRESH(Nset) = 0.0;
     L_DELTA(Nset) = 0.001;
     WT_SCALE(Nset) = 1.0;
   }
}

// Initilaization of the Learning Rule
// Call once at beginning

void EHebbInit(struct NodeSet *Nset) {

   struct NodeStruct *Nodeptr;

   EHebbInitParams(Nset);
}


// Normalized Efferent Hebbian learning rule

void NormEffHebb(struct NodeSet *Nset) {

  struct NodeStruct *Sourcenode, *Destnode;
  TWeightClass *Weightptr;
  float        dpre, dpost, x;
  int i, j;

  for(i=0; i < SET_NumNodes(Nset); i++) {
    Sourcenode = SET_NodeAddress(Nset,i);
    Weightptr = NODE_WeightLoc(Sourcenode);
    j = 0;
    while(j < NODE_NumWts(Sourcenode)) {
      if(WT_Learn(Weightptr,j)) {
        Destnode = WT_DestNodePtr(Weightptr,j);
        dpre = NODE_Act(Sourcenode) - PRE_THRESH(Nset);
        dpost = NODE_Act(Destnode) - POST_THRESH(Nset);
        if(dpre > 0.0 || dpost > 0.0) {
          x =  WT_Value(Weightptr,j) + L_DELTA(Nset) * dpre*dpost;
          NODE_SumWeight(Sourcenode) += x;
          WT_Value(Weightptr,j) = x;
        }
      }
      j++;
    }
  }

  // Normalize weights

  for(i=0; i < SET_NumNodes(Nset); i++) {
    Sourcenode = SET_NodeAddress(Nset,i);
    Weightptr = NODE_WeightLoc(SET_NodeAddress(Nset,i));
    j = 0;
    while(j < NODE_NumWts(Sourcenode)) {
      if(WT_Learn(Weightptr,j)) {
        NODE_SumWeight(Sourcenode) = fabs(NODE_SumWeight(Sourcenode));
        if(NODE_SumWeight(Sourcenode) > 0.0) {
          WT_Value(Weightptr,j) /= NODE_SumWeight(Sourcenode);
          WT_Value(Weightptr,j) *= WT_SCALE(Nset);
        }
      }
      j++;
    }
    NODE_SumWeight(Sourcenode) = 0.0;
  }

  return;
}

