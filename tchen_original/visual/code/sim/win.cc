// System-specific functions

#include <string.h>
#include <stdio.h>

#include "win.h"
#include "simdefs.h"
#include "classdef.h"
#include "externs.h"
#include "macros.h"

void DisplayInit(HWND TheWind){return;};

BOOL TimeOut(void) {return(0);}

int DisplayStatus(HWND TheWind, int iteration) {

   fprintf(stdout, "%d\n", Tot_Iter+iteration);
   return(0);
}
