/*    
	(C) Copyright 2000 T.W. Long
	All rights reserved

*/

/* change.cc rev.  3/99*/
/*

Change the string in a file from "from" to "to".
e.g. "from" could be: /homr/theresa, "to" could be "/home/theresa"
In the input file change.in, "from" takes up one line, and "to" takes
up one line. Don't forget to press "return" at end of "to" because
the function fgets stops at "\n" or "EOF".  If we don't press 
return at the last line of input, we will lose one caharacter
when fgets replaces the last symbol (which is normally '\n')
with the NUll('\0'), and we lose one symbol.

fgets  would allow for a pattern containing
space, but fscanf would not..

At the system prompt type
>change fname
where fname is the file we want to go in to make change


To do multiply files, we can use a shell script. e.g.
we want to do this for all the codes in the current directory
we can use the follwing script

for file in $(ls  *.cc); do
change $file
done
exit 0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxline 1000
#define maxlen  80
int from_length, to_length;

void changename(char* fname,char *from,char* to);
char* pattern(char *line, char *pat, int pat_length);

int main (int argc, char ** argv)
{
  FILE *infile;
  char from[maxlen];
  char to[maxlen];

  if( (infile = fopen("change.in", "r")) == NULL)
    {
      printf("can't open change.in\n");
      exit(0);
    }

  fgets(from,maxlen,infile);
  fgets(to,maxlen,infile);
  from_length = strlen(from);
  to_length = strlen(to);


  /* do not want to double dip by counting '\0'*/
  from_length--;  
  to_length--;

  changename(argv[1],from,to);

  fclose(infile);
}

/*----------------------------------------------*/
void changename(char* fname,char *from,char* to)
{
  FILE *outfile, *readfile;
  int i, inchar, t = 1;
  char line[maxline], line2[maxline],*cs, *cs2, *pt, *pt2;
  char* Outfile = "tempfile";
  outfile = fopen(Outfile,"w");
  if( (readfile = fopen(fname, "r")) == NULL)
    {
      printf("can't open %s\n",fname);
      exit(0);
    }
  while( t)
    {
      if( (inchar = getc(readfile) )!= EOF)
	{
	  ungetc(inchar, readfile);
	  fgets(line,maxline,readfile);
	  strcpy(line2,line);
	  pt = line;
	  pt2 = line2;
	  /* keep on looking in case there are repeat patterns*/
	  while( (cs = pattern(pt,from, from_length)) != NULL)
	    {
	      pt = cs;
	      cs2 = pattern(pt2,from,from_length); 
	      for(i=0; i< to_length; i++)
		{
		  *cs2 = to[i];
		  cs2++;
		}
	      pt += from_length;
	      pt2 = cs2;
	      strcpy(cs2,pt);
	    }/* end of while there is a match */

	  fprintf(outfile,"%s",line2);

	}/*end of if !EOF*/
      else
	t = 0;
    }/*end of while*/

  fclose(readfile);
  fclose(outfile);
  remove(fname);
  rename(Outfile,fname);
}


/*---------------pattern-------------*/
/*search for "pat" in "line".  If there is a match, return
pointer to the first occurrence of pat in line*/
char* pattern(char *line, char *pat, int pat_length)
{
  int i, track = 0;
  char *cs, *cs1;
  cs = line;
  cs1 = pat;

  if(strlen(line) < pat_length)
    {
      cs = NULL;
      return cs;
    }

  while((*cs != '\0') && (track < pat_length))
    {
      if(*cs != *cs1)
	{
	  cs++;
	}
	  
      else
	{
	  track++;
	  cs++;
	  cs1++;
	  for(i = 1; (i<pat_length) && (cs != '\0')&&(track != 0); i++)
	    {
	      if(*cs == *cs1)
		{
		  track++;
		  cs++;
		  cs1++;
		}
	      else 
		{
		  track == 0;
		  cs1 = pat;
		}
	    }/* end of for, to see if pat_length chars match*/

	  if(track < pat_length)
	    {
	      track = 0;
	      cs1 = pat;
	    }
	}/* end of outer else*/
    }/*end of while*/

  if(track < pat_length)
    {
      cs = NULL;
      return cs;
    }
  else
    {
      cs -= pat_length;
      /*      printf("%s",cs);*/
      return cs;
    }
}
