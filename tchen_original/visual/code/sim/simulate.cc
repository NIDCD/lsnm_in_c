#include <stdio.h>
#include <string.h>
#include <time.h>

#include "win.h"
#include "simdefs.h"
#include "classdef.h"
#include "externs.h"
#include "simproto.h"
#include "macros.h"


//                   SIMULATE
//              Run the simulation

/***************************************************************/


int simulate(HWND TheWind, FILE *out_fd)


{
   int      iteration, j, n_written;
   DisplayInit(TheWind);
   WriteHeader(out_fd);
   for(j=0; j<N_Sets; j++)  {
     if(Set[j]->InitSet && SET_NumNodes(Set[j]) > 0)
       Set[j]->InitSet(Set[j]);
   }
   for(iteration=1; iteration<=N_Iter; iteration++)   {
     // DisplayStatus(TheWind, iteration+Tot_Iter);
     for(j=0; j<N_Sets; j++)   {
       if(Set[j]->OutputRule && SET_NumNodes(Set[j]) > 0)
       Set[j]->OutputRule(Set[j]);
      }
      for(j=0; j<N_Sets; j++)        {
       if(Set[j]->InputRule && SET_NumNodes(Set[j]) > 0)
          Set[j]->InputRule(Set[j]);
      }
      for(j=0; j<N_Sets; j++) {
       if(Set[j]->ActRule && SET_NumNodes(Set[j]) > 0)
          Set[j]->ActRule(Set[j]);
      }
      for(j=0; j<N_Sets; j++)   {
       if(Set[j]->Update && SET_NumNodes(Set[j]) > 0)
          Set[j]->Update(Set[j]);
      }
      for(j=0; j<N_Sets; j++)   {
       if(Set[j]->LearnRule && SET_NumNodes(Set[j]) > 0)
          Set[j]->LearnRule(Set[j]);
      }
      if(WritePet > 0) {
       if((Tot_Iter+iteration)%WritePet == 0)
	      WritePET(Pet_fs);
      }
	  if(WriteAbsPet > 0) {
       if((Tot_Iter+iteration)%WriteAbsPet == 0)
	      Write_APET(Pet_fs);
      }

      n_written = 0;
      for(j=0; j<N_Sets; j++)     {
       if(Set[j]->WriteOut > 0)
          n_written += WriteSet_Matlab(out_fd, Tot_Iter+iteration, Set[j]);
       if(Set[j]->WriteWts > 0)
          WriteWts(out_fd, Tot_Iter+iteration, Set[j]);
      }
/*      if(n_written > 0)
          fprintf(out_fd, "\n");


   fprintf(out_fd, "\n");
*/
   }
   Tot_Iter += N_Iter;
   /*  WriteFooter(out_fd);  */

   return(1);
}
