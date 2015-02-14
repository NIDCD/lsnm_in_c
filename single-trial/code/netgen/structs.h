#include "defs.h"
// Structure definitions for network generator

struct NetGenStruct {
  char      Type;
  char  OutWrite;
  char    InSet[SET_NAME_SIZE];
  char     OutSet[SET_NAME_SIZE];
  int     istartx, istarty, ostartx, ostarty;
  int        ix, iy, ox, oy, fx, fy;
  int    idx, idy, odx, ody;
  float      pctzero;
  int   seed;
  float *scale, *base;
};

/* 
TWL comments:
   *startx: row index
   *starty: column index

   *x: number of rows
   *y: number of columns

note that this is counter intuitive because we tend to think x as traversing
columns, and y in the direction of traversing the rows

*/
