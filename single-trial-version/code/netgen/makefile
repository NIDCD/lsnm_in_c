
BASE = ../../bin
# compile on churn, skip the library, let the compiler find it
#setenv LD_LIBRARY_PATH /usr/local/lib if must use g++ on churn
# it is recommended to use CC (SGI's c++) 
CC = g++

netgen1: unixmain.o generate.o 
	$(CC) unixmain.o generate.o -lm -lc  -o $(BASE)/netgen1

unixmain.o:	win.h defs.h structs.h decls.h unixmain.cc
	$(CC) -c 	unixmain.cc

generate.o:		win.h defs.h structs.h prototyp.h generate.cc
	$(CC) -c 		generate.cc

