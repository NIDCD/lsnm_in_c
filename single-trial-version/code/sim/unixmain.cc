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

   This file (unixmain.cc) was last modified on January 18, 2015.


   Author: Malle Tagamets. Last updated by Antonio Ulloa on January 18 2015  
* **************************************************************************/


#include <stdio.h>
#include <string.h>
#include <time.h>


#include "win.h"
#include "simdefs.h"
#include "simproto.h"
#include "simdecls.h"
#include "classdef.h"

#define BUGGY
FILE *buggy;

// Prototypes for the simulator function */

int         siminit(HWND GraphWnd, char *infile, FILE *ofd);  /* Reads the input file */
int         simulate(HWND GraphWnd, FILE *outfs);
void       ClearAll();


/****************************************/

   /* Simulation Window class defintions */

/****************************************/



//_CLASSDEF(SimClass)
class SimClass
{
public:
  int Verbose;
  int NotInit;
  BOOL OutFileFlag, InFileFlag;
  FILE *Outfs;
  char InFile[MAXPATH];
  char OutFile[MAXPATH];
  SimClass(PTWindowsObject AParent, char *File);
  ~SimClass();
  BOOL ParseFile(char *File);
};


/****************************************/

SimClass::SimClass(PTWindowsObject AParent, char *File)
{

//  AssignMenu("COMMANDS");
  InFileFlag = FALSE;
  OutFileFlag = FALSE;
  NotInit = 0;
  Outfs = NULL;
  if(strlen(File))
    ParseFile(File);
  else
    Errmsg((char*)"Usage: sim <in_file_name>\n");
}


/****************************************/

SimClass::~SimClass() {

  if(Outfs != NULL) {
    WriteFooter(Outfs);
    fclose(Outfs);
    }

  ClearAll();

}


/****************************************/

BOOL SimClass::ParseFile(char *File)
{
   strncpy(InFile, File, MAXPATH-2);
   strncpy(OutFile, File, MAXPATH-2);
   strcat(InFile, ".s");
   strcat(OutFile, ".out");
   n_line = 0;
   NotInit = 1;
   if(Outfs != NULL)
     fclose(Outfs);
   if((Outfs = fopen(OutFile,"w")) == NULL)
     return(FALSE);
   // buggy = fopen("debug.txt","w");
   if(siminit(NULL, InFile, Outfs) > 0) {
     InvalidateRect(NULL, NULL, 1);
     NotInit = 0;
     //  fclose(buggy);
     return(TRUE);
   }
   else {
     //  fclose(buggy);
     return(FALSE);
   }
}


/****************************************/
/*-----------------------------------------------------*/
/*                       Main                           */
/*-----------------------------------------------------*/
/****************************************/



int main(int argc, char **argv)
{
  SimClass      *MainThing;
  char               FileName[MAXPATH];

  if(argc > 1)
    strncpy(FileName,argv[1],MAXPATH);
  else
    strcpy(FileName,"");

  MainThing = new SimClass(NULL, FileName);
}







