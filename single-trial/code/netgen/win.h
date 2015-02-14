//  System-specific definitions and prototypes

#include <stdio.h>

/****************************************/
//	Unix-specific Redefinitions

#define	HWND	int
#define BOOL	int
#define LPSTR	char*

#define	TRUE	1
#define FALSE	0

void srandom(int x);
long random();

#define MessageBox(x,str1,str2,code) fprintf(stderr,"%s\n%s\n",str1,str2)

#define _CLASSDEF(x)	;

#define	MAXPATH	256

#define		PTWindowsObject			int
#define		InvalidateRect(x, y, z) 	;
#define		UpdateWindow(x)			;

#define	strcmpi(str1, str2)	strcasecmp(str1,str2)

BOOL    TimeOut(void);

//	End of Unix-specific redefinitions
/****************************************/

