#include "simdefs.h"


// Variables for initialization functions
int   n_line = 0;
int   old_line = 0;
char  codestr[LINESIZE];

char  OutputFile[MAXPATH];

void  (*learn)() = 0;

int   WritePetNames = 1;
int   WritePet = 0;	/* How often to write PET  */
int   WriteAbsPet = -1;	/* How often to write Absolute PET  */


/*       Declare and initialize global variables         */


int   verbose = 0;
int   N_Iter = 500;
int   Tot_Iter = 0;
int   Cur_Iter = 0;
int   write_phi = 0;
FILE  *out_fd;
FILE  *log_fd = 0;
FILE  *Pet_fs = 0;

float  K = 0.0;
float  delta = 1.0;
float  delta_phi = 1.0;
float  sigma = 1.0;
float  topwt = 2.0;            /* Amount to weight center node by in
                              topological learning */

int    In_side = 0;
int    Out_side = 0;

int    randseed = 0;

FILE   *phi_fd = 0;
FILE   *l_fd = 0;

float  learn_rate = 0.0;
int    learn_times = 0;


char   infilename[120];        /* Input file without the .s */

char    MsgStr[240];


/********************************************************************/

int     N_Sets = 0;
int     CurSet = 0;


struct  NodeSet *Set[MAX_SETS];



