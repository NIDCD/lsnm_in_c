#include <stdio.h>
#include <string.h>
#include <time.h>

#include "win.h"
#include "simdefs.h"
#include "classdef.h"
#include "externs.h"
#include "simproto.h"
#include "macros.h"

// Write the header of the output file

void WriteHeader(FILE *fd)
{
	//printf("writeout.cc - WriteHeader - Begin");
  time_t t;
  int nwsets = 0;
  int i;
  long fileloc;

  time(&t);
  fprintf(fd, "%% %s\n",ctime(&t));
  for(i=0; i<N_Sets; i++) {
    /* TMP
    if(SET_File(Set[i]) != NULL) {
      fileloc = ftell(SET_File(Set[i]));
      if(fileloc != (long)0)
        fseek(SET_File(Set[i]),0,0);
      fprintf(SET_File(Set[i]), "%% %s\n",ctime(&t));
      fprintf(SET_File(Set[i]), "%d %d\n", 1, N_Iter+Tot_Iter);
      fprintf(SET_File(Set[i]),"%s(%d,%d)\n", Set[i]->SetName, Set[i]->XDim, Set[i]->YDim);
      if(fileloc != (long)0)
         fseek(SET_File(Set[i]),fileloc,0);
    }

    else if(Set[i]->WriteOut > 0)
      nwsets++;
      ETMP */
  }
  fprintf(fd, "%d %d\n", nwsets, N_Iter+Tot_Iter);
  for(i=0; i<N_Sets; i++) {
    if(Set[i]->WriteOut > 0) {
      fprintf(fd,"%s(%d,%d)\n", Set[i]->SetName, Set[i]->XDim, Set[i]->YDim);
    }
  }
	//echo writeout.cc - WriteHeader - End;
  return;
}

// Write the footer of the output file

void WriteFooter(FILE *fd)
{
	//echo writeout.cc - WriteFooter - Begin;
  time_t t;
  int i,j,k,m;
  struct NodeSet *Nset;
  struct NodeStruct *Nodeptr;

  for(i=0; i<N_Sets; i++) {
    Nset = Set[i];
    if(Nset->WriteOut >= 0 ) {
     fprintf(fd, "  %d: %s (%d)\t", Nset->SetIndex, SET_Name(Nset),SET_NumNodes(Nset));
     fprintf(fd,"Sum of activations at the end of iteration %d \n",Tot_Iter);
     // If topology in linear
     if(Nset->WriteOut >= 0 && SET_Topology(Nset) == LINEAR) {
      for(j=0; j<SET_NumNodes(Nset); j++) {
        Nodeptr = SET_NodeAddress(Nset,j);
        fprintf(fd, " %5.3f ", NODE_SumAct(Nodeptr));
       }
       fprintf(fd, "  %d: %s (%d)\t", Nset->SetIndex, SET_Name(Nset),SET_NumNodes(Nset));
       fprintf(fd,"Sum of Excitatory Inputs at the end of iteration %d \n",Tot_Iter);
       for(j=0; j<SET_NumNodes(Nset); j++) {
        Nodeptr = SET_NodeAddress(Nset,j);
        fprintf(fd, " %5.3f ", NODE_SumExInput(Nodeptr));
       }
       fprintf(fd, "\n");
       fprintf(fd, "  %d: %s (%d)\t", Nset->SetIndex, SET_Name(Nset),SET_NumNodes(Nset));
       fprintf(fd,"Sum of Inhibitory Inputs at the end of iteration %d \n",Tot_Iter);
       for(j=0; j<SET_NumNodes(Nset); j++) {
        Nodeptr = SET_NodeAddress(Nset,j);
        fprintf(fd, " %5.3f ", NODE_SumInhInput(Nodeptr));
       }
       fprintf(fd, "\n");
      }
     // Else if topology is rectangular
     else if(Nset->WriteOut >= 0 && SET_Topology(Nset) == RECT) {
      fprintf(fd, "\n");
      k = 0;
      for(m=0; m<SET_YDim(Nset); m++) {
        for(j=0; j<SET_XDim(Nset); j++)  {
          Nodeptr = SET_NodeAddress(Nset,k);
          k++;
          fprintf(fd, "%5.2f ", NODE_SumAct(Nodeptr));
        }
        fprintf(fd, "\n");
      }
      k = 0;
      fprintf(fd, "  %d: %s (%d)\t", Nset->SetIndex, SET_Name(Nset),SET_NumNodes(Nset));
      fprintf(fd,"Sum of Excitatory Inputs at the end of iteration %d \n",Tot_Iter);
      for(m=0; m<SET_YDim(Nset); m++) {
        for(j=0; j<SET_XDim(Nset); j++)  {
          Nodeptr = SET_NodeAddress(Nset,k);
          k++;
          fprintf(fd, " %5.2f", NODE_SumExInput(Nodeptr));
        }
        fprintf(fd, "\n");
      }
      k = 0;
      fprintf(fd, "  %d: %s (%d)\t", Nset->SetIndex, SET_Name(Nset),SET_NumNodes(Nset));
      fprintf(fd,"Sum of Inhibitory Inputs at the end of iteration %d \n",Tot_Iter);
      for(m=0; m<SET_YDim(Nset); m++) {
        for(j=0; j<SET_XDim(Nset); j++)  {
          Nodeptr = SET_NodeAddress(Nset,k);
          k++;
          fprintf(fd, " %5.2f", NODE_SumInhInput(Nodeptr));
        }
       fprintf(fd, "\n");
      }
    }
    fprintf(fd, "\n");
   }
  }
  time(&t);
  fprintf(fd, "%% %s\n",ctime(&t));
	//echo writeout.cc - WriteFooter - End;
}

// Write the PET scan of the output file

void WritePET(FILE *fs)
{
	//echo writeout.cc - WritePET - Begin;
  int i,j;
  float InSum;
  struct NodeSet *Nset;
  struct NodeStruct *Nodeptr;

  if(fs == NULL) {
     Errmsg((char*)"No open PET file\n");
	//echo writeout.cc - WritePET - End 1;
     return;
  }

  // print out total excitatory inputs to each set
  for(i=0; i<N_Sets; i++) {
    Nset = Set[i];
    if(Nset->WriteOut >= 0) {
      InSum = 0.0;
      for(j=0; j<SET_NumNodes(Nset); j++) {
        Nodeptr = SET_NodeAddress(Nset,j);
        InSum += NODE_SumExInput(Nodeptr);
        NODE_SumExInput(Nodeptr) = 0.0;		// Reset
      }
      fprintf(fs,"\t%8.0f", InSum);
    }
  }
    fprintf(fs,"\n");

// print out total inhibitory inputs to each set
  for(i=0; i<N_Sets; i++) {
    Nset = Set[i];
    if(Nset->WriteOut >= 0) {
      InSum = 0.0;
      for(j=0; j<SET_NumNodes(Nset); j++) {
        Nodeptr = SET_NodeAddress(Nset,j);
        InSum += NODE_SumInhInput(Nodeptr);
        NODE_SumInhInput(Nodeptr) = 0.0;		// Reset
      }
      fprintf(fs,"\t%8.0f", InSum);
    }
  }
  fprintf(fs,"\n");
	//echo writeout.cc - WritePET - End 2;
}


// Write the absolute PET scan of the output file

void Write_APET(FILE *fs)
{
	//echo writeout.cc - Write_APET - Begin;
  int i,j;
  float InSum;
  struct NodeSet *Nset;
  struct NodeStruct *Nodeptr;

  if(fs == NULL) {
     Errmsg((char*)"No open PET file\n");
	//echo writeout.cc - Write_APET - End 1;
     return;
  }

    // Print out sum of excitatory and inhibitory inputs to each set
    //    if WritePetFlag = 0
  for(i=0; i<N_Sets; i++) {
      Nset = Set[i];
      if(Nset->WriteOut >= 0) {
        InSum = 0.0;
        for(j=0; j<SET_NumNodes(Nset); j++) {
           Nodeptr = SET_NodeAddress(Nset,j);
           InSum += (NODE_SumExInput(Nodeptr) - NODE_SumInhInput(Nodeptr));
		   NODE_SumExInput(Nodeptr) = 0.0;		// Reset
		   NODE_SumInhInput(Nodeptr) = 0.0;		// Reset
        }
	    fprintf(fs,"%10.0f  ", InSum);
      }
   }
   fprintf(fs,"\n");
	//echo writeout.cc - Write_APET - End 2;
}



/*******************************************************/

//  Function to write the current activations of the set
//        in annotated ASCII formia

int WriteSet(FILE *fd, int iter, struct NodeSet *Nset)
	//echo writeout.cc - WriteSet - Begin;
{
  struct NodeStruct *Nodeptr;
  int i, j, k, written;
  FILE *outfs;

  if(SET_File(Nset) != NULL) {
    written = 0;
    outfs = SET_File(Nset);
  }
  else {
    written = 1;
    outfs = fd;
  }

  if(Nset->WriteOut == 0 || iter%(Nset->WriteOut) == 0)      {
    fprintf(outfs,"%d ",iter);
    fprintf(outfs, "  %d %s (%d)\t", Nset->SetIndex, SET_Name(Nset),SET_NumNodes(Nset));
    if(SET_Topology(Nset) == LINEAR) {
       for(j=0; j<SET_NumNodes(Nset); j++) {
         Nodeptr = SET_NodeAddress(Nset,j);
      fprintf(outfs, "%5.3f ", NODE_Act(Nodeptr));
       }
  fprintf(outfs, "\n");
    }
    else if(SET_Topology(Nset) == RECT) {
      k = 0;
      fprintf(outfs, "\n");
      for(i=1; i<=SET_YDim(Nset); i++) {
      for(j=1; j<=SET_XDim(Nset); j++)  {
       k = SET_TopNodeIndex(Nset,j,i);
         Nodeptr = SET_NodeAddress(Nset,k);
         fprintf(outfs, "%5.2f ", NODE_Act(Nodeptr));
          }
       fprintf(outfs, "\n");
      }
    }
  }
	//echo writeout.cc - WriteSet - End;
  return(written);
}

/**********************************************************/

// Write activations in matlab format: rows are all nodes in the set,
// columns are time steps in the simulation

int WriteSet_Matlab(FILE *fd, int iter, struct NodeSet *Nset)
{
	//echo writeout.cc - WriteSet_Matlab - Begin;
  struct NodeStruct *Nodeptr;
  int i, j, k, written;
  FILE *outfs;
  TWeightClass *wtptr;

  if(SET_File(Nset) != NULL) {
    written = 0;
    outfs = SET_File(Nset);
  }
  else {
    written = 1;
    outfs = fd;
  }

  if(Nset->WriteOut > 0 && iter%(Nset->WriteOut) == 0)     {
       for(j=0; j<SET_NumNodes(Nset); j++) {
           Nodeptr = SET_NodeAddress(Nset,j);
           fprintf(outfs, "%5.3f ", NODE_Act(Nodeptr));
       }
       fprintf(outfs, "\n");
  }
	//echo writeout.cc - WriteSet_Matlab - End;
  return(written);
}

//       Function to write the current weights of the set

int WriteWts(FILE *fd, int iter, struct NodeSet *Nset)
{
	//echo writeout.cc - WriteWts - Begin;
  struct NodeStruct *Nodeptr;
  struct NodeSet *Destset;
  TWeightClass *Weightptr;
  int i, j, dnode, written, writeweight = 0;
  FILE *outfs;

  if(SET_WtFile(Nset) != NULL) {
    written = 0;
    outfs = SET_WtFile(Nset);
  }
  else {
    written = 1;
    outfs = fd;
  }

  if(Nset->WriteWts == 0 || iter%(Nset->WriteWts) == 0)    {
    fprintf(outfs,"%d:\n",iter);
    Destset = NULL;
    for(i=0; i<SET_NumNodes(Nset); i++) {
      Nodeptr = SET_NodeAddress(Nset,i);
      Weightptr = NODE_WeightLoc(Nodeptr);
      j = 0;
      while(j < NODE_NumWts(Nodeptr))  {
	if(WT_Learn(Weightptr,j)) {
	   writeweight = 1;
           if(WT_DestSetPtr(Weightptr,j) != Destset) {
              writeweight = 0;
              if(Destset != NULL)
                 fprintf(outfs,"\n}\n\n");
              Destset = WT_DestSetPtr(Weightptr,j);
              fprintf(outfs,"Connect(%s,%s) {\n",SET_Name(Nset),SET_Name(Destset));
              fprintf(outfs,"\n From: (%d, %d)  { ", SET_TopNodeX(Nset,i)+1, SET_TopNodeY(Nset,i)+1);
           }
           if(j == 0 && writeweight > 0)
              fprintf(outfs,"\n From: (%d, %d)  { ",SET_TopNodeX(Nset,i)+1, SET_TopNodeY(Nset,i)+1);
	   dnode = NODE_Index(WT_DestNodePtr(Weightptr,j));
           fprintf(outfs, "( [%d, %d] %6.4f) ", 
			   SET_TopNodeX(Destset,dnode)+1, SET_TopNodeY(Destset,dnode)+1,
                           WT_Value(Weightptr,j));
	}  /* END if(WT_Learn...)  */
        j++;

      }  /* END WHILE */

      if(writeweight > 0)
         fprintf(outfs,"}\n");

    }    /* END FOR */
      if(writeweight > 0)
         fprintf(outfs,"\n}\n");
  }      /* END IF */
	//echo writeout.cc - WriteWts - End;
  return(written);
}

