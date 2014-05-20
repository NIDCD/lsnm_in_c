BASE = ../../bin
CC = g++
LIBO = -lc -lm

au_sim1: actfuncs.o init.o messages.o outfuncs.o parsecxn.o parseset.o\
 	parse.o siminit.o simlearn.o  simulate.o unixmain.o writeout.o win.o
	$(CC) *.o -g -o $(BASE)/au_sim1

parse.o:	win.h simdefs.h simproto.h parse.cc
	$(CC) -c -g	parse.cc
actfuncs.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h actfuncs.cc
	$(CC) -c -g	actfuncs.cc
init.o:		win.h simdefs.h macros.h classdef.h externs.h simproto.h init.cc
	$(CC) -c -g	init.cc
malleact.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h malleact.cc
	$(CC) -c -g	malleact.cc
mallev2.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h mallev2.cc
	$(CC) -c -g	mallev2.cc
messages.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h messages.cc
	$(CC) -c -g	messages.cc
outfuncs.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h outfuncs.cc
	$(CC) -c -g	outfuncs.cc
paintdat.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h paintdat.cc
	$(CC) -c -g	paintdat.cc
parsecxn.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h parsecxn.cc
	$(CC) -c -g	parsecxn.cc
parseset.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h parseset.cc
	$(CC) -c -g	parseset.cc
receptor.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h receptor.cc
	$(CC) -c -g	receptor.cc
siminit.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h siminit.cc
	$(CC) -c -g	siminit.cc
simlearn.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h simlearn.cc
	$(CC) -c -g	simlearn.cc
simulate.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h simulate.cc
	$(CC) -c -g	simulate.cc
unixmain.o:	win.h simdefs.h macros.h classdef.h simdecls.h simproto.h unixmain.cc
	$(CC) -c -g	unixmain.cc
writeout.o:	win.h simdefs.h macros.h classdef.h simdecls.h simproto.h writeout.cc
	$(CC) -c -g	writeout.cc
win.o:		win.h simdefs.h macros.h classdef.h simdecls.h simproto.h win.cc
	$(CC) -c -g	win.cc
sporns91.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h sporns91.cc
	$(CC) -c -g	sporns91.cc
tononi.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h tononi.cc
	$(CC) -c -g	tononi.cc
