/* rev.  8/98*/
/* time_axis.cc  reads a .rs file, generate time axis for both
   the synact data and the .out data.  suppose that the .rs file
   we want to use is pethi.rs, and the number of ticks/second is 200,
   and the frequency for writing out the .out data is every 5 ticks.
   at the command line prompt, we type:
   
   time_axis pethi 200 5

  note that we don't tyoe the suffix .rs.  Also, the synact write out
  frequency is stated in pethi.rs, so we do not need to enter how
  often the synact (which comes from spec_pet.m) data is written
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define maxlen 80

int main (int argc, char **argv)
{
  FILE *infile, *outfile1, *outfile2;
  char Infile[maxlen], Outfile1[maxlen], Outfile2[maxlen], temp[maxlen];
  int inchar;
  int tick, del_tick, syn_del_tick, i,k;
  float ratio, sratio, tt = 0, tts = 0;

  strcpy(Infile, argv[1]);
  strcpy(Outfile1, argv[1]);
  strcpy(Outfile2, argv[1]);
  strcat(Infile,".rs");
  strcat(Outfile1,"_t");
  strcat(Outfile2,"_syn_t");

  if( (infile = fopen(Infile, "r")) == NULL)
    {
      printf("can't open %s\n", Infile);
      exit(0);
    }
  if( (outfile1 = fopen(Outfile1, "w")) == NULL)
    {
      printf("can't open %s\n", Outfile1);
      exit(0);
    }
  if( (outfile2 = fopen(Outfile2, "w")) == NULL)
    {
      printf("can't open %s\n", Outfile2);
      exit(0);
    }

  tick = atoi(argv[2]);
  del_tick = atoi(argv[3]);
  ratio = ((float)del_tick)/((float)tick);

  while( (inchar = getc(infile)) != EOF)
    {
      if(inchar == 'W')
	{
	  while( getc(infile) != ' ');
	  fscanf(infile, "%d", &syn_del_tick);
	  fgets(temp, maxlen,infile);
	  sratio = ((float)syn_del_tick)/((float)tick);
	}/*end of if inchar == 'W'*/

      if( (inchar == '%')||(inchar == '#') )
	{
	  fgets(temp, maxlen,infile);
	}/*end of if inchar == '%' or '#'*/

      if(inchar == 'R')
	{
	  while(getc(infile) != ' ');
	  fscanf(infile, "%d", &k);
	  fgets(temp, maxlen,infile);
	  for(i = 0; i < k; i += del_tick)
	    {
	      tt +=  ratio;
	      fprintf(outfile1,"%f ",tt);
	    }

	  for(i = 0; i < k; i += syn_del_tick)
	    {
	      tts +=  sratio;
	      fprintf(outfile2,"%f ",tts);
	    }
	}/*end of if inchar == 'R'*/
    }
  fprintf(outfile1,"\n");
  fprintf(outfile2,"\n");
  fclose(infile);
  fclose(outfile1);
  fclose(outfile2);
}
