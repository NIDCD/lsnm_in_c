// Definitions for input parsing

#define MAXPATH 256

#define A_NUMBER  1
#define A_STRING 2
#define START_OBJECT 3
#define END_OBJECT 4

#define LITTLENUM       0.00001

#define  LINESIZE        200

#define SET_NAME_SIZE 32
#define MAX_SETS 50


#define LINEAR    0               // Set topology types
#define RECT       1

#define VOLTAGE_IND	0     // Definitions of connection types
#define VOLTAGE_DEP	1
#define REVERSE_CXN	2        // Reverse the destination and source sets
#define CHANGE_CXN	3        // Change the value of an existing connection

#define WTARRAY_INC  50      /* Amount to increment weight array by */

#define CM_INFILEOPEN  201
#define CM_OUTFILEOPEN 202                     
#define CM_IOFILE      203

#define CM_RUN              301
#define CM_VERBOSE     302
#define CM_ITER            303
#define CM_GRAPH       304
#define CM_EXITSIM     305

