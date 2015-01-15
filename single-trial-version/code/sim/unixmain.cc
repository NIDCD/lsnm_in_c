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
/*
  virtual void CMRun(RTMessage Msg)
    = [CM_FIRST + CM_RUN];
  virtual void CMSetIter(RTMessage Msg)
    = [CM_FIRST + CM_ITER];
  virtual void CMVerbose(RTMessage Msg)
    = [CM_FIRST + CM_VERBOSE];
*/
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
   buggy = fopen("debug.txt","w");
   if(siminit(NULL, InFile, Outfs) > 0) {
     InvalidateRect(NULL, NULL, 1);
     NotInit = 0;
     fclose(buggy);
     return(TRUE);
   }
   else {
     fclose(buggy);
     return(FALSE);
   }
}


/****************************************/


/* TMP

void SimClass::CMRun(RTMessage)
{
  if(!InFileFlag)   {
    Message("Need to open a valid input file", "Error!");
    return;
  }
  if(!OutFileFlag)   {
    Message("Need to open an output file", "Error!");
    return;
  }
  if(Outfs == NULL) {
    if((Outfs = fopen(OutFile,"w")) != NULL) {
      OutFileFlag = TRUE;
      strcpy(OutputFile, OutFile);
    }
    else {
      OutFileFlag = FALSE;
      sprintf(MsgStr,"Run: Cannot open output file %s",OutFile);
      Errmsg(MsgStr);
    }
  }
  if(NotInit) {
    if(siminit(HWindow, InFile, Outfs) > 0) {
      InvalidateRect(HWindow, NULL, 1);
      NotInit = 0;
    }
  }
  else
    simulate(HWindow, Outfs);
}

ETMP */

/****************************************/

/* TMP

void SimClass::CMSetIter(RTMessage)
{
  int iter;
  PTInputDialog Iter;

  sprintf(MsgStr, "%d", N_Iter);
  Iter = new TInputDialog(this, "Iterations", "Enter number of iterations:",
                      MsgStr, sizeof(MsgStr));

  if ( GetApplication()->ExecDialog(Iter) == IDOK )
  {
      iter = atoi(MsgStr);
      if ( Iter < 0 )
         Errmsg("Iteration size must be greater than 0");
      else
       N_Iter = iter;
      }
}

ETMP */

/****************************************/

/* TMP

void SimClass::CMVerbose(RTMessage)
{
  if(Verbose == 0)
     Verbose = 1;
  else
     Verbose = 0;
}

ETMP */


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







