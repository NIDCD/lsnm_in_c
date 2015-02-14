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

   This file (win.h) was last modified on January 18, 2015.


   Author: Malle Tagamets. Last updated by Antonio Ulloa on January 18 2015  
* **************************************************************************/

//  System-specific definitions and prototypes

#include <stdio.h>

/****************************************/
//    Unix-specific Redefinitions

#define      HWND    int
#define BOOL int
#define LPSTR        char*

#define    TRUE    1
#define FALSE  0

#define MessageBox(x,str1,str2,code) str2?fprintf(stderr,"%s\n%s",str1,str2):fprintf(stderr,"%s",str1)

#define _CLASSDEF(x)   ;

#define        MAXPATH 256

#define              PTWindowsObject                 int
#define              InvalidateRect(x, y, z)         ;
#define                UpdateWindow(x)                 ;

BOOL    TimeOut(void);

//   End of Unix-specific redefinitions
/****************************************/

