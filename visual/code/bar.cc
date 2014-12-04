/*generate a shell script file to change file names to standard form*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxlen 80

int main(int argc, char** argv)
{
  FILE *outfile;
  int i,j,length;
  char fname[maxlen],fname1[maxlen],inchar;

  outfile = fopen("bbout","w");
  strcpy(fname,argv[1]);
  length = strlen(fname);
  i=0;
  j=0;
  while(fname[i] != '_' && i < length)
    {
      fname1[j] = fname[i]; 
      i++;
      j++;
    }
  while(fname[i] != '.') i++;
  while(i< length)
    {
      fname1[j] = fname[i];
      i++;
      j++;
    }
  fname1[j] = '\0';
  if(i != j)
    fprintf(outfile,"#\n#\nmv  %s ../newdir/%s\n",fname,fname1);
  fclose(outfile);
}
