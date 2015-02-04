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

   This file, pareset.cc, parses and initializes/resets set paratemers


   Author: Malle Tagamets, circa 1995  
* *************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

#include "win.h"
#include "simdefs.h"
#include "simproto.h"
#include "classdef.h"
#include "externs.h"
#include "macros.h"


//#define BUGGY
extern FILE *buggy;

/********************************************************************/

enum SetCodes { ENDFILE, ENDPARSE, ACTRULE, ALL=ACTRULE, INPUTRULE,
         LEARNRULE, LEARNPARAM, OUTPUTRULE, NODEACT, BINACT,
	 OBJECT, PARAMETER, PHASE, RECEPTOR, SHIFT, TOPOLOGY,
         WRITEOUT, WRITEWEIGHTS };


//    Gets the structure of the set with name contained in *str

struct NodeSet   *getset(char *str)
{
   int i = 0;

   if(N_Sets == 0)
      return(NULL);
   else while(i < N_Sets && (strcmp(str, SET_Name(Set[i])) != 0)) 
     {
      i++;
    }
   if(i<N_Sets) 
     {
       return(Set[i]);
     }
   else
     return(NULL);
 }

/********************************************************************/
int strcmpi(char *s1, char *s2)
{
  char *s11, *s22, c1,c2;
  int i, k, t = 0;
  
  i = strlen(s1);

  s11 = s1;
  s22 = s2;
  for(k = 0; k < i && t == 0; k++)
    {
      c1 = tolower(*s11);
      c2 = tolower(*s22);
      if(c1 == c2)
	{
	  s11++;
	  s22++;
	}
      else t = 1;
    }
  return t;
}


/********************************************************************/

// Function to read in and convert the node index

int ReadNodeIndex(FILE *fd, struct NodeSet *Nset, int *index)
{
  int i,j,k;

  if(SET_Topology(Nset) == LINEAR) 
    {
      if(getint(fd, &i) != EOF)
	k=i-1;
      else
	return(-1);
    }
  else if(SET_Topology(Nset) == RECT) 
    {
      if((getint(fd,&i) != EOF) && (getint(fd,&j) != EOF))  
	{
	  k = SET_TopNodeIndex(Nset,i,j);
	}
      else
	return(-1);
    }  
  if(k < 0 || k >= SET_NumNodes(Nset))  
    {
      sprintf(MsgStr,
	      "Illegal node index %d in set %s, max is %d (line %d)",
	      k+1, SET_Name(Nset), SET_NumNodes(Nset)+1,n_line);
      Errmsg(MsgStr);
      return(-1);
    }
  *index = k;
  return(0);
}


int GetSetParam(struct NodeSet *Nset,char *paramname)  
{

  int i;

  i=0;
  while(i < SET_NumParams(Nset)) 
    {
      if(strcmpi(SET_ParamName(Nset,i),paramname)==0)
	return(i);
      i++;
    }
  return(-1);
}

int GetLrnParam(struct NodeSet *Nset,char *paramname)  
{

  int i;

  i=0;
  while(i < SET_NLrnParams(Nset)) 
    {
      if(strcmpi(SET_LrnParamName(Nset,i),paramname)==0)
	return(i);
      i++;
    }
  return(-1);
}

int GetSetVar(struct NodeSet *Nset,char *paramname)  
{

  int i;

  i=0;
  while(i < SET_NumParams(Nset)) 
    {
      if(strcmpi(SET_ParamName(Nset,i),paramname)==0)
	return(i);
      i++;
    }
  return(-1);
}


/*******************************************************************/

/*    Parse the input and return the code for the next operation */

SetCodes nextSetcode(FILE *ifd)
{
   int  code;
   char instring[120];

   while((code = getcode(ifd,instring)) != EOF)        
     {
       switch(*instring)      
	 {
	 case '{':
	 case '(':
	 case '[':
	   return(OBJECT);
	 case '}':
	   return(ENDPARSE);
	 case 'a':
	   return(ACTRULE);
	 case 'b':
	   return(BINACT);
	 case 'i':
	   return(INPUTRULE);
	 case 'l':
	   return(LEARNRULE);
	 case 'o':
	   return(OUTPUTRULE);
	 case 'n':
	   return(NODEACT);
	 case 'p':
	   switch(instring[1]) 
	     {
	     case 'a':
	       return(PARAMETER);
	     case 'h':
	       return(PHASE);
	     case 'l':
	       return(LEARNPARAM);
	     default:
	       break;
	     }
	   break;
	 case 'r':
	   return(RECEPTOR);
	 case 's':
	   return(SHIFT);
	 case 't':
	   return(TOPOLOGY);
	 case 'w':
	   switch(instring[1]) 
	     {
	     case 'r':
	       return(WRITEOUT);
	     case 'w':
	       return(WRITEWEIGHTS);
	     default:
	       break;
	     }
	   break;
	 default:
	   break;
	 }
     }
   return(ENDFILE);
 }

/*******************************************************************/

#define SNAMESIZE 64

int parseSet(FILE *ifd)
{
  SetCodes        code;
  struct NodeSet     *Nset;
  char sname[SNAMESIZE];
  int  setsize, pval, i,j;
  float x;

  if(getstring(ifd, sname) == EOF)
    return(ENDFILE);

  if(getint(ifd, &setsize) == EOF)
    return(ENDFILE);

  if(setsize > 0)    
    {
      CurSet = N_Sets;
      Nset = initNodeSet(sname, setsize);
    }
  else 
    {
      sprintf(MsgStr, "Illegal Set Size: %d", setsize);
      Errmsg(MsgStr);
      return(ENDFILE);
    }

  while((code = nextSetcode(ifd)) != ENDPARSE)    
    {
      switch(code)  
	{
	  // Activation Rule
	case ACTRULE:
	  if(getstring(ifd,sname) == EOF)
	    return(ENDFILE);
	  switch(*sname)   
	    {
	    case 'c':
	      Nset->ActRule = NULL;  // Clamp activations to set values
	      break;
	    case 'd':            // Differential Sigmoid activation
	      Nset->ActRule = DSigAct;
	      DSigActInit(Nset);
	      break;
	    case 'l':		/* Linear Activation rulw */
	      /* Nset->ActRule = LinearAct;
	      LinActInit(Nset);*/
	      break;
	    case 'n':		// Noisy Clamp
	      Nset->ActRule = ClampAct;
	      ClampActInit(Nset);
	      break;

	    case 's':
	      switch(sname[1]) 
		{
		case 'i':      // Sigmoid activation
		  /* Nset->ActRule = SigAct;
		  SigActInit(Nset);*/
		  break;
		case 'h':      // Shifting activation
		  /* Nset->ActRule = Shift_activation;
		  ShiftActInit(Nset);*/
		  break;
		}
	      break;

	    case 't':         // TVB input matrix to set activation values
	      Nset->ActRule = TvbAct;
	      TvbActInit(Nset);
	      break;
	    }    
	  break;

	case INPUTRULE:
		break;		// We have no input rules now

	case LEARNRULE:
	  if(getstring(ifd,sname) == EOF)
	    return(ENDFILE);
	   switch(*sname)   
	     {
	     case 'o':
	       Nset->LearnRule = NULL;  // OFF:  No learning
	       break;
	     case 'a':          // Afferent Hebbian
	       //Nset->LearnRule = NormAffHebb;
	       //AHebbInit(Nset);
	       break;
	     case 'e':          // Efferent Hebbian
	       //Nset->LearnRule = NormEffHebb;
	       //EHebbInit(Nset);
	       break;

	     default:
	       break;
	     }    
	  break;

	case OUTPUTRULE:
	  if(getstring(ifd,sname) == EOF)
	    return(ENDFILE);
	  switch(*sname)   
	    {
	    case 'c':
	      Nset->OutputRule = NULL;
	      break;
	    case 's':
	      if(sname[1] == 'u')
		Nset->OutputRule = SumOut;
	      break;
	    default:
	      break;
	    }
	  break;

      case NODEACT:       // Initial activation values
        if(nextobject(ifd) == EOF)
          return(ENDFILE);
        while((code = nextSetcode(ifd)) != ENDPARSE)      
	  {
          switch(code)  
	    {
            case ALL:   // All nodes
              if(getfnum(ifd,&x) == EOF)
                return(ENDFILE);
              for(i=0; i < SET_NumNodes(Nset); i++) 
		{
		  Nset->Node[i].Act = x;
		  Nset->Node[i].OldAct = x;
		}
              break;
            case OBJECT:
              if(ReadNodeIndex(ifd,Nset,&i))
                return(ENDFILE);
              if(getfnum(ifd, &x) == EOF)
                return(ENDFILE);
              Nset->Node[i].Act = x;
              Nset->Node[i].OldAct = x;
              break;
            case ENDFILE:
              sprintf(MsgStr, "Unexpected EOF in Activation spec, line %d", n_line);
              Errmsg(MsgStr);
              return(ENDFILE);
            default:
              break;
	    }
        }
	  break;

	case BINACT:    /* Initial activation values, set */
			          /* by input matrix*/
	  if(nextobject(ifd) == EOF)
	    return(ENDFILE);
	  for(i=0;i<SET_NumNodes(Nset); i++)      
	    {
	      if( getfnum(ifd, &x) == EOF)
		return(ENDFILE);
              Nset->Node[i].Act = x;
              Nset->Node[i].OldAct = x;
	    }
	  break;

	case PHASE:       // Initial phase values
	  if(nextobject(ifd) == EOF)
	    return(ENDFILE);
	  while((code = nextSetcode(ifd)) != ENDPARSE)    
	    {
	      switch(code)  
		{
		case ALL:   // All nodes
		  if(getfnum(ifd,&x)== EOF)
		    return(ENDFILE);
		  for(i=0; i<SET_NumNodes(Nset); i++)
		    Nset->Node[i].Phase = (int)x;
		  break;
		case OBJECT:
		  if(ReadNodeIndex(ifd,Nset,&i))
		    return(ENDFILE);
		  if(getfnum(ifd, &x) == EOF)
		    return(ENDFILE);
		  Nset->Node[i].Phase = (int)x;
		  break;
		case ENDFILE:
		  sprintf(MsgStr, "Unexpected EOF, line %d", n_line);
		  Errmsg(MsgStr);
		  return(ENDFILE);
		default:
		  break;
		}
	    }
	  break;

	  // Set parameters values
	case PARAMETER:
	  if(nextobject(ifd) == EOF) 
	    {
	      sprintf(MsgStr,
		      "Unexpected EOF parsing parameter, line %d",
		      sname, n_line);
	      Errmsg(MsgStr);
	      return(ENDFILE);
	    }
	  while((code = nextSetcode(ifd)) != ENDPARSE)    
	    {
	      switch(code)  
		{
		case ALL:   // All parameters
		  if(getfnum(ifd,&x) == EOF)
		    return(ENDFILE);
		  for(i=0; i<SET_NumParams(Nset); i++)
		    SET_ParamVal(Nset,i) = x;
		  break;
		case OBJECT:
		  if(getstring(ifd,sname) == EOF)
		    return(ENDFILE);
		  if((pval = GetSetParam(Nset,sname)) < 0)  
		    {
		      sprintf(MsgStr,
			      "Error in Parameter name %s, line %d",
			      sname, n_line);
		      Errmsg(MsgStr);
		      return(ENDFILE);
		    }
		  if(getfnum(ifd, &x) == EOF)
		    return(ENDFILE);
		  SET_ParamVal(Nset,pval) = x;
		  break;
		case ENDFILE:
		  sprintf(MsgStr,
			  "Unexpected EOF in parsin set %s, line %d",
			  SET_Name(Nset), n_line);
		  Errmsg(MsgStr);
		  return(ENDFILE);
		default:
		  break;
		}
	    }
	  break;

	  // Learning rule parameters values
	case LEARNPARAM:
	  if(nextobject(ifd) == EOF)
	    return(ENDFILE);
	  while((code = nextSetcode(ifd)) != ENDPARSE)    
	    {
	      switch(code)  
		{
		case ALL:   // All parameters
		  if(getfnum(ifd,&x) == EOF)
		    return(ENDFILE);
		  for(i=0; i<SET_NLrnParams(Nset); i++)
		    SET_LrnParamVal(Nset,i) = x;
		  break;
		case OBJECT:
		  if(getstring(ifd,sname) == EOF)
		    return(ENDFILE);
		  if((pval = GetLrnParam(Nset,sname)) < 0)  
		    {
		      sprintf(MsgStr,
			      "Error in learning parameter name %s, line %d",
			      sname, n_line);
		      Errmsg(MsgStr);
		      return(ENDFILE);
		    }
		  if(getfnum(ifd, &x) == EOF)
		    return(ENDFILE);
		  SET_LrnParamVal(Nset,pval) = x;
		  break;
		case ENDFILE:
		  sprintf(MsgStr,
			  "Unexpected EOF in parsin set %s, line %d",
			  SET_Name(Nset), n_line);
		  Errmsg(MsgStr);
		  return(ENDFILE);
		default:
		  break;
		}
	    }
	  break;

	case SHIFT:	/* Explicitly Shift activations */
	  /* Shift_activation(Nset);*/
	  break;

	case TOPOLOGY:
	  if(getstring(ifd,sname) == EOF)
	    return(ENDFILE);
	  switch(*sname) 
	    {
	    case 'l':
	      SET_Topology(Nset) = LINEAR;
	      break;
	    case 'r':
	      if(getint(ifd,&i) == EOF)
		return(ENDFILE);
	      if(getint(ifd,&j) == EOF)
		return(ENDFILE);
	      if(i*j != SET_NumNodes(Nset))  {
		sprintf(MsgStr,
			"Topology of set %s does not match set size %d\nSyntax: Topology: Rect(#x, #y)",
			SET_Name(Nset),SET_NumNodes(Nset));
		Errmsg(MsgStr);
		return(ENDFILE);
	      }
	      SET_Topology(Nset) = RECT;
	      SET_XDim(Nset) = i;
	      SET_YDim(Nset) = j;
	      break;
	    default:
	      break;
            }
	  break;

	case WRITEOUT:    // Set file output to every 'i' iterations; 0 = None
	  if(getint(ifd,&i) == EOF)
	    return(ENDFILE);
	  Nset->WriteOut = i;
	  if(i > 0 && SET_File(Nset) == NULL) 
	    {
	      for(i=0;i<SNAMESIZE;i++)
		sname[i] = 0;
	      strncpy(sname,SET_Name(Nset),8);
	      strcat(sname,".out");
	      SET_File(Nset) = fopen(sname,"w");
	      if(SET_File(Nset) == NULL) 
		{
		  sprintf(MsgStr,
		      "Cannot open output file for set %s\nUsing default file",
		      SET_Name(Nset));
		  Message(MsgStr,(char*)"Parse set: Write");
		}
	    }
	  break;


	case WRITEWEIGHTS:   // Set weight writeout output to every 'i' iterations; 0 = None
	  if(getint(ifd,&i) == EOF)
             return(ENDFILE);
	  Nset->WriteWts = i;
	  if(i > 0) 
	    {
	      for(i=0;i<SNAMESIZE;i++)
		sname[i] = 0;
	      strncpy(sname,SET_Name(Nset),8);
	      strcat(sname,".wt");
	      SET_WtFile(Nset) = fopen(sname,"w");
	      if(SET_WtFile(Nset) == NULL) 
		{
		  sprintf(MsgStr,
                 "Cannot open weight output file for set %s\nUsing default file",
			  SET_Name(Nset));
		  Message(MsgStr,(char*)"Parse set: Write");
		}
	    }
           break;


	case ENDFILE:
	  return(ENDFILE);

        default:
          break;
	}
    }
  return(ENDPARSE);
}



// Set initalization

struct NodeSet *initNodeSet(char *name, int nnodes)

{
  struct NodeSet *set;
  struct NodeStruct *Nodeptr;

  if((set = getset(name))) 
    {
      CurSet = set->SetIndex;
      return(set);
    }

  if((set = (NodeSet *)calloc(1, sizeof(NodeSet))) == NULL) 
    {
      sprintf(MsgStr, "Error: Not enough memory for Set %s ", name);
      Errmsg(MsgStr);
      return(NULL);
    }

  if((set->Node = (NodeStruct *)calloc((unsigned)nnodes, sizeof(NodeStruct))) == NULL) 
    {
      sprintf(MsgStr, "Error: Not enough memory for Set %s ", name);
      Errmsg(MsgStr);
      free(set);
      return(NULL);
    }

  strncpy(SET_Name(set), name, SET_NAME_SIZE);
  SET_File(set) = NULL;
  SET_NumNodes(set) = nnodes;
  SET_XDim(set) = nnodes;
  SET_YDim(set) = 1;
  SET_Topology(set) = LINEAR;
  SET_NumParams(set) = 0;
  SET_NumVars(set) = 0;
  SET_ParamAddress(set) = NULL;
  SET_VarAddress(set) = NULL;
  set->WriteOut = 1;          // Default: Write out every iteration
  set->SetIndex = N_Sets;
  set->InitSet = NULL;          // Default functions:  Do Nothing
  set->OutputRule = NULL;
  set->InputRule = NULL;
  set->ActRule = NULL;
  set->Update = NULL;
  set->LearnRule = NULL;
  for(int i=0; i < SET_NumNodes(set); i++) 
    {
      Nodeptr = SET_NodeAddress(set,i);
      NODE_Index(Nodeptr) = i;
      NODE_Act(Nodeptr) = 0.0;
      NODE_SumAct(Nodeptr) = 0.0;
      NODE_MaxAct(Nodeptr) = 0.0;
      NODE_SumExInput(Nodeptr) = 0.0;
      NODE_SumInhInput(Nodeptr) = 0.0;
      NODE_SumWeight(Nodeptr) = 0.0;
      NODE_Phase(Nodeptr) = 0;
      NODE_Output(Nodeptr) = 0.0;
      set->Node[i].Input = 0.0;
      NODE_InputLoc(Nodeptr) = &(set->Node[i].Input);
      NODE_WeightLoc(Nodeptr) = new TWeightClass(i);
      NODE_AltWeightLoc(Nodeptr) = new TWeightClass(i);
      set->Node[i].InWt = new TWeightClass(i);
    }
  Set[N_Sets++] = set;
  return(set);
}

void DeleteNodeSet(struct NodeSet *Nset)

{
  struct NodeStruct *Nodeptr;

  if(SET_File(Nset) != NULL)
    fclose(SET_File(Nset));

  for(int i=0; i<SET_NumNodes(Nset); i++)  
    {
      Nodeptr = SET_NodeAddress(Nset,i);
      delete(NODE_WeightLoc(Nodeptr));
      delete(NODE_AltWeightLoc(Nodeptr));
      delete(Nset->Node[i].InWt);
    }

  free(Nset->Node);
  free(Nset);
  return;
}

