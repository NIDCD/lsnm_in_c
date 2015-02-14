/*============================================================================
 *
 *                    PUBLIC DOMAIN NOTICE
 *
 *   National Institute on Deafness and Other Communication Disorders
 *
 * This software/database is a "United States Government Work" under the 
 * terms of the United States Copyright Act. It was written as part of 
 * the author's official duties as a United States Government employee and 
 * thus cannot be copyrighted. This software/database is freely available 
 * to the public for use. The NIDCD and the U.S. Government have not placed 
 * any restriction on its use or reproduction. 
 *
 * Although all reasonable efforts have been taken to ensure the accuracy 
 * and reliability of the software and data, the NIDCD and the U.S. Government 
 * do not and cannot warrant the performance or results that may be obtained 
 * by using this software or data. The NIDCD and the U.S. Government disclaim 
 * all warranties, express or implied, including warranties of performance, 
 * merchantability or fitness for any particular purpose.
 *
 * Please cite the author in any work or product based on this material.
 * 
 * ==========================================================================
 *
 */

/* **************************************************************************

   Large-Scale Neural Modeling software (LSNM)

   Section on Brain Imaging and Modeling
   Voice, Speech and Language Branch
   National Institute on Deafness and Other Communication Disorders
   National Institutes of Health

   This file (simdecls.h) was last modified on January 18, 2015.


   Author: Malle Tagamets. Last updated by Antonio Ulloa on January 18 2015  
* **************************************************************************/

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



