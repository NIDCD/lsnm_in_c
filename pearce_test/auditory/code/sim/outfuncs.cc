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
//  NODE_SumExInput(Destnode) += fabs(output);
      else
    NODE_SumInhInput(Destnode) += output;
//         NODE_SumInhInput(Destnode) += fabs(output);
      j++;
    }
  }
  return;
}

