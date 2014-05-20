/* rev.  6/3/98,  TWL*/
/* namechange.cc  
   For each region, changes the right brain labels to left brain labels 
   according to:
   attv -> attv
   atts -> gats

   lgns -> lgns

   ev1h -> eg1h
   iv1h -> ig1h
   ev1v -> eg1v
   iv1v -> ig1v

   ev4h -> eg4h
   iv4h -> ig4h
   ev4v -> eg4v
   iv4v -> ig4v
   ev4c -> eg4c
   iv4c -> ig4c

   exss -> exgt
   inss -> ingt

   exfs -> egfs
   infs -> igfs
   efd1 -> egd1
   ifd1 -> igd1
   efd2 -> egd2
   ifd2 -> igd2
   exfr -> egfr
   infr -> igfr
note that if we start the index at 0, excitatory regions are at index 2i+1 of the array, where i starts at 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxlen 12
#define num 23

int namechange(char *name)
{

   char *oldname[num] = {"attv","atts","lgns","ev1h","iv1h","ev1v","iv1v","ev4h","iv4h","ev4v","iv4v","ev4c","iv4c","exss","inss","exfs","infs","efd1","ifd1","efd2","ifd2","exfr","infr"};

  char *newname[num] = {"attv","gats","lgns","eg1h","ig1h","eg1v","ig1v","eg4h","ig4h","eg4v","ig4v","eg4c","ig4c","exgt","ingt","egfs","igfs","egd1","igd1","egd2","igd2","egfr","igfr"};
 
  int i, getout = 0;

  for(i = 0; i< num && getout == 0; i++)
    {
      if( strstr(name,oldname[i]) != NULL)
	{
	  getout = i;
	  strcpy(name, newname[i]);
	}
    }/* end of i loop */
  return getout;
}
