/* mkattn.cc   rev. 7/14/98
make an attention file, given the attention level an dthe output filename
There are 4 attention files used in *.rs
(1)hiattn_r.s: included in the begining of a simulation, for right brain
(2)hiattn_l.s: included in the begining of a simulation, for left brain
(3)loattn_r.s: included in the end of a simulation, for right brain
(4)loattn_l.s: included in the end of a simulation, for left brain

e.g. we want to make hiattn_r with attention level 0.3, at the prompt, type
mkattn hiattn_r.s 0.3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define maxlen 80

int main (int argc, char **argv)
{
  FILE  *outfile;
  char Outfile[maxlen];

  strcpy(Outfile, argv[1]);
  if( (outfile = fopen(Outfile, "w")) == NULL)
    {
      printf("can't open %s\n", Outfile);
      exit(0);
    }
  if(argv[1][7] == 'r')
    fprintf(outfile,"set(Atts,1)\n{ Node activation { ALL %s } }\n",argv[2]);
  else if(argv[1][7] == 'l')
    fprintf(outfile,"set(GAts,1)\n{ Node activation { ALL %s } }\n",argv[2]);
  else
    printf("output filename %s is not one of the 4 types expected\n",Outfile);
}


