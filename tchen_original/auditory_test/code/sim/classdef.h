
/* Class definitions for node sets and structures */

#include <stdio.h>

struct WeightStruct {
  int        LearnOn;
  struct NodeSet *Set;
  struct NodeStruct *DestNode;
  float Value;
  float WtVar;
};

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

