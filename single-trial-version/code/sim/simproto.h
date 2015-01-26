   /* Simulation class defintions */

#include <stdio.h>

//        Prototypes for message functions

void    Errmsg(char *str);
void  	Message(char *str1, char *str2);
void    DisplayInit(HWND TheWind);       // Initialize run-time display
int     DisplayStatus(HWND TheWind, int iteration);    // Show run-time status

// Prototypes for file output functions

void    WriteHeader(FILE *fd);
void    WriteFooter(FILE *fd);
void    WritePET(FILE *fd);
void    Write_APET(FILE *fd);
int     WriteSet(FILE *fd, int iter, struct NodeSet *Nset);
int     WriteSet_Matlab(FILE *fd, int iter, struct NodeSet *Nset);
int     WriteWts(FILE *fd, int iter, struct NodeSet *Nset);


/* Prototypes for parsing and initilization functions */


int     siminit(HWND GraphWnd, char *infile, FILE *ofd);  /* Reads the input file */
void    ClearAll();

int	    getcode(FILE *fd, char *str);
int	    parse_string(FILE *fd, char *str);
int	    parse_number(FILE *fd, char *str);
int	    getint(FILE *fd, int *x);
int	    getfnum(FILE *fd, float *x);
int	    getstring(FILE *fd, char *x);
int	    nextobject(FILE *fd);

int     parseSet(FILE *infd);
int     parseConnect(FILE *infd);

// Prototype for the simulator function */

int     simulate(HWND GraphWnd, FILE *outfs);

// Set operations

struct	NodeSet *initNodeSet(char *name, int nnodes);
struct	NodeSet   *getset(char *str);   //Returns Address of set
int     FindSet(char setname);          //Returns Index of set named <setname>
void	DeleteNodeSet(struct NodeSet *Nset);
int	    GetSetParam(struct NodeSet *Nset,char *paramname);


// Connection operations

void    addweight(struct NodeSet *set1, int fromnode,
                  struct  NodeSet *set2, int tonode, int type, float weight);


/* Prototypes for activation functions */

void TononiInitVars(struct NodeSet *Nset);
void TononiActInit(struct NodeSet *Nset);
void TononiAct(struct NodeSet *Nset);

void SpornsAct(struct NodeSet *Nset);
void SpornsActInit(struct NodeSet *Nset);

void MalleAct(struct NodeSet *Nset);
void MalleActInit(struct NodeSet *Nset);

void LinActInit(struct NodeSet *Nset);
void LinearAct(struct NodeSet *Nset);

void SigActInit(struct NodeSet *Nset);
void SigAct(struct NodeSet *Nset);

void DSigActInit(struct NodeSet *Nset);
void DSigAct(struct NodeSet *Nset);


void InitReceptor(struct NodeSet *Nset);
void ReceptorAct(struct NodeSet *Nset);

void ShiftActInit(struct NodeSet *Nset);
void Shift_activation(struct NodeSet *Nset);	// Shifts activations in space regularly

void TvbActInit(struct NodeSet *Nset);
void TvbAct(struct NodeSet *Nset);

void ClampActInit(struct NodeSet *Nset);
void ClampAct(struct NodeSet *Nset);

/* Prototypes for node output functions */

void SumOut(struct NodeSet *Nset);

void TononiInput(struct NodeSet *Nset);
void TononiOutInit(struct NodeSet *Nset);
void TononiOut(struct NodeSet *Nset);
void TononiDep(struct NodeSet *Nset);
void TononiUpdate(struct NodeSet *Nset);

void SpornsOut(struct NodeSet *Nset);

void MalleOut(struct NodeSet *Nset);

/* Prototypes for learning functions */

void TononiLearn(struct NodeSet *Nset);

// Normalized Afferent Hebbian learning rule

void AHebbInit(struct NodeSet *Nset);
void NormAffHebb(struct NodeSet *Nset);

// Normalized Efferent Hebbian learning rule

void EHebbInit(struct NodeSet *Nset);
void NormEffHebb(struct NodeSet *Nset);




