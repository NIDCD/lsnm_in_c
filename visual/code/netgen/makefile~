
BASE = /home/bhguest/brent/visual/bin
# compile on churn, skip the library, let the compiler find it
#setenv LD_LIBRARY_PATH /usr/local/lib if must use g++ on churn
# it is recommended to use CC (SGI's c++) 
CC = CC

netgen1: unixmain.o generate.o 
	CC unixmain.o generate.o -lm -lc  -o $(BASE)/netgen1

netgenk: unixmain.o generatek.o 
	CC unixmain.o generatek.o -lm -lc  -o $(BASE)/netgenk

netgenA: unixmain.o generateA.o 
	CC unixmain.o generateA.o -lm -lc -o $(BASE)/netgenA

netgenC: unixmain.o generateC.o 
	CC unixmain.o generateC.o -lm -lc -o $(BASE)/netgenC

netgenC_L: unixmain.o generateC_L.o
	CC unixmain.o generateC_L.o -lm -lc -o $(BASE)/netgenC_L

unixmain.o:	win.h defs.h structs.h decls.h unixmain.cc
	CC -c 	unixmain.cc

generate.o:		win.h defs.h structs.h prototyp.h generate.cc
	CC -c 		generate.cc

generatek.o:		win.h defs.h structs.h prototyp.h generatek.cc
	CC -c 		generatek.cc

generateA.o:		win.h defs.h structs.h prototyp.h generateA.cc
	CC -c 		generateA.cc

generateC.o:		win.h defs.h structs.h prototyp.h generateC.cc
	CC -c 		generateC.cc

generateC_L.o:		win.h defs.h structs.h prototyp.h generateC_L.cc
	CC -c		generateC_L.cc
