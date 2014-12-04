#include <stdlib.h>
#include <string.h>

#include "win.h"
#include "simdefs.h"
#include "simproto.h"
#include "classdef.h"
#include "externs.h"
#include "macros.h"


void Update(struct NodeSet *Nset)
{

  for(int i=0; i < Nset->N_Nodes; i++) {
     INPUT(i) = 0.0;
     OUTPUT(i) = 0.0;
  }
  return;
}

