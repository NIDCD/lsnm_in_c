/*      External variables                              */
/*    Include in all files except main                */
#include "win.h"
#include "simproto.h"

// Variables for initialization functions
extern int      n_line;

extern char   OutputFile[MAXPATH];

extern int     verbose;
extern int     N_Iter;
extern int     Tot_Iter;
extern int     Cur_Iter;
extern int     write_phi;

extern int  WritePetNames;
extern int  WritePet;
extern int  WriteAbsPet;

extern void LinearAct(struct NodeSet *Nset);
extern void SumOut(struct NodeSet *Nset);


/*       Files for more verbose output options           */

extern FILE    *phi_fd;                /* File for writing dynamic weights */
extern FILE    *l_fd;                  /* File for writing static weights
                                         during learning */
extern FILE    *Pet_fs;                /* File for writing Pet Data */

extern char infilename[];

extern char MsgStr[240];

extern struct NodeSet *Set[MAX_SETS];

extern int N_Sets;
extern int CurSet;

