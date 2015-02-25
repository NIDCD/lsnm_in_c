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

   This file, parsecxn.cc, parses, initializes/resets connection parameters


   Author: Malle Tagamets, circa 1995  
* *************************************************************************/

/*      Parse    and    initialize/reset  connection    parameters      */

#include <string.h>
#include <stdio.h>
#include <math.h>

#include "win.h"
#include "simdefs.h"
#include "classdef.h"
#include "simproto.h"
#include "externs.h"
#include "macros.h"

// #define BUGGY 1
extern FILE *buggy;

int ReadNodeIndex(FILE *fd, struct NodeSet *nset, int *i);

enum CxnCodes { ALL, EACH, ENDFILE, ENDCXN, ENDWEIGHT, FROM, LEARNON, OBJECT, TYPE};

int CurCxnType = VOLTAGE_IND;
int CurLearn = 0;

/*******************************************************************/

/*   Parse the input and return the code for the next operation */


CxnCodes nextCxncode(FILE *ifd)
{
   int  code;
   char instring[40];


   while((code = getcode(ifd, instring)) != EOF)   
     {

       switch(*instring)      
	 {
	 case '}':
	   return(ENDCXN);
	 case '(':
	 case '[':
	   return(OBJECT);
	 case 'a':
	   return(ALL);
	 case 'e':
	   return(EACH);
	 case 'f':
	   return(FROM);
	 case 'l':
	   return(LEARNON);
	 case 't':
	   return(TYPE);
	 default:
	   break;
	 }
     }
   return(ENDFILE);
 }

/*******************************************************************/

#define SNAMESIZE 64

int parseConnect(FILE *ifd)
{
  CxnCodes       code;
  char     tmpchar[SNAMESIZE];
  struct NodeSet *set1, *set2;
  int fromnode = 0, tonode = 0, i;
  float weight;

  if(getstring(ifd, tmpchar) == EOF)
    return(ENDFILE);
  set1 = getset(tmpchar);
  if(set1 == NULL)  
    {
      Message((char*)"Connect:  Cannot find set ", tmpchar);
      return(ENDCXN);
    }

  CurLearn = 0;            /* Set Learning OFF as default */
  CurCxnType = VOLTAGE_IND;	/* Set to default conenction type */

  if(getstring(ifd, tmpchar) == EOF)
    return(ENDFILE);
  set2 = getset(tmpchar);
  if(set2 == NULL)  
    {
      Message((char*)"Connect:  Cannot find set ", tmpchar);
      return(ENDCXN);
    }


  while((code = nextCxncode(ifd)) != ENDCXN)     
    {
      switch(code)       
	{
	case ENDFILE:
	  break;
	case EACH:   // From each node to its partner in the second set
	  if(getfnum(ifd, &weight) == EOF)
	    return(ENDFILE);
	  for(i=0; i < SET_NumNodes(set1); i++)
	    addweight(set1,i,set2,i,CurCxnType,weight);
	  return(code);	/* Do we need this?? */
	  break;

	case FROM:
	  if(ReadNodeIndex(ifd,set1,&i)) 
	    {
	      sprintf(MsgStr,
		      "Error in parsing connection source set1(%d)",i);
	      Message(MsgStr,(char*)"From");
	      code = ENDFILE;
	      break;
	    }
	  fromnode = i;
	  if(nextobject(ifd) == EOF) 
	    {
	      sprintf(MsgStr, "Unexpected EOF, line %d", n_line);
	      Errmsg(MsgStr);
	      break;
	      return(ENDFILE);
	    }
	  while((code = nextCxncode(ifd)) != ENDCXN)      
	    {
	      switch(code)  
		{
		case ENDFILE:
		  sprintf(MsgStr, "Unexpected EOF, line %d", n_line);
		  Errmsg(MsgStr);
		  break;
		case ALL:   // All nodes
		  if(getfnum(ifd, &weight) == EOF)
		    return(ENDFILE);
		  for(i=0; i < SET_NumNodes(set2); i++)
		    addweight(set1,fromnode,set2,i,CurCxnType,weight);
		  return(code);	/* Do we need this?? */
		  break;
		case OBJECT:
		  if(ReadNodeIndex(ifd,set2,&tonode)) 
		    {
		      sprintf(MsgStr,
		      "Error in parsing connection from set1(%d)",fromnode);
		      Message(MsgStr,(char*)"Onject parse");
		      code = ENDFILE;
		      break;
		    }
		  if(getfnum(ifd, &weight) == EOF) 
		    {
		      sprintf(MsgStr, 
                       "Unexpected EOF in Connection Spec, line %d", n_line);
		      Errmsg(MsgStr);
		      return(ENDFILE);
		    }

		  addweight(set1,fromnode,set2,tonode,CurCxnType,weight);
		  break;
		default:
		  break;
		}
	    }
	  break;

	case TYPE:
	  /* ??? Why was this section commented out?  TMP */
	  if(nextobject(ifd) == EOF) 
	    {
	      sprintf(MsgStr, 
               "Unexpected EOF in Connection Type Spec, line %d", n_line);
	      Errmsg(MsgStr);
	      return(ENDFILE);
	    }
	  /* ??? */
	  if(getstring(ifd,tmpchar) == EOF) 
	    {
	      sprintf(MsgStr, 
              "Unexpected EOF getting type in Connection Type Spec, line %d", 
                 n_line);
	      Errmsg(MsgStr);
	      return(ENDFILE);
	    }
	  switch(*tmpchar)   
	    {
	    case 'i':
	      CurCxnType = VOLTAGE_IND;
	      break;
	    case 'd':
	      CurCxnType = VOLTAGE_DEP;
	      break;
	    case 'r':
	      CurCxnType = REVERSE_CXN;
	      break;
	    case 'c':
	      CurCxnType = CHANGE_CXN;
	      break;
	    default:
	      sprintf(MsgStr, "Unknown Connection type: %s\n",tmpchar);
	      Errmsg(MsgStr);
	      break;
	    }
	  break;

	case LEARNON:
	  if(getint(ifd,&CurLearn) == EOF)
	    return(ENDFILE);
	  break;

	default:
	  break;
	}
    }

  return(code);
}

/* Connection Class function definitions  */


TWeightClass::TWeightClass(int nodeindex)

{
  CurMaxWeight = 0;
  N_Weights = 0;
  NodeIndex = nodeindex;
  Weight = NULL;
}

TWeightClass::~TWeightClass()

{
   free(Weight);
}


BOOL TWeightClass::NewWeight(struct NodeSet *destset, int destnode, float value)
{

  // Stuff for memory management
  if(CurMaxWeight == 0) {
    if((Weight = (WeightStruct *)calloc((unsigned)WTARRAY_INC, sizeof(*Weight))) == NULL) 
      {
	sprintf(MsgStr,
         "Error: Not enough memory to add weights in Set <destset>");
	Errmsg(MsgStr);
	return FALSE;
      }
    CurMaxWeight = WTARRAY_INC;
  }
  CurMaxWeight--;
  if(CurMaxWeight == 0) 
    {
      if((Weight = (WeightStruct *)realloc(Weight, sizeof(*Weight)*(WTARRAY_INC+N_Weights))) == NULL) 
	{
	  sprintf(MsgStr,
          "Error: Not enough memory to add weights in Set <destset> ");
	  Errmsg(MsgStr);
	  return FALSE;
	}
      CurMaxWeight = WTARRAY_INC;
    }

  //Now add the weight
  Weight[N_Weights].Set = destset;
  Weight[N_Weights].Value = value;
  Weight[N_Weights].DestNode = SET_NodeAddress(destset,destnode);
  Weight[N_Weights].LearnOn = CurLearn;
  N_Weights++;
  return TRUE;
}

BOOL ChangeWeight(struct NodeSet *set1, int fromnode,
             struct NodeSet *set2, int tonode, float value)
{	
  int	i;
  WeightStruct *wts;

  i = 0;
  wts = &(set1->Node[fromnode].OutWt->Weight[i]);
  while(i < set1->Node[fromnode].OutWt->N_Weights) 
    {
      if(wts[i].Set == set2) 
	{
	  if(wts[i].DestNode == SET_NodeAddress(set2,tonode)) 
	    {
	      wts[i].Value = value;
	      return(TRUE);
	    }
	}
      i++;
    }
  return(FALSE);
}


void addweight(struct NodeSet *set1, int fromnode,
             struct NodeSet *set2, int tonode,
               int type, float weight) 
{

   if(fromnode < 0 || fromnode >= SET_NumNodes(set1))  
     {
       sprintf(MsgStr, "Error: Node %d in set %s is out of range",
                 fromnode, SET_Name(set1));
       Errmsg(MsgStr);
       return;
     }
   if(tonode < 0 || tonode >= SET_NumNodes(set2))  
     {
       sprintf(MsgStr, "Error: Node %d in set %s is out of range",
                      tonode, SET_Name(set2));
       Errmsg(MsgStr);
       return;
     }
   if(type == VOLTAGE_IND) 
     set1->Node[fromnode].OutWt->NewWeight(set2, tonode,weight);
   else if(type == CHANGE_CXN) 
     {
       if(ChangeWeight(set1, fromnode,set2,tonode,weight) == FALSE) 
	 {
	   sprintf(MsgStr, "Cannot change weight from %s:%d to %s:%d",
			 SET_Name(set1),fromnode,SET_Name(set2),tonode);
	   Errmsg(MsgStr);
	 }
     }
   else if(type == VOLTAGE_DEP)
     set1->Node[fromnode].AltWt->NewWeight(set2, tonode, weight);
   else if(type == REVERSE_CXN)
     set2->Node[tonode].OutWt->NewWeight(set1, fromnode, weight);
   else 
     {
       sprintf(MsgStr, "Unknown connection type: %d", type);
       Errmsg(MsgStr);
     }
   return;
 }
