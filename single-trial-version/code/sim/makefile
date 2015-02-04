# ============================================================================
#
#                            PUBLIC DOMAIN NOTICE
#
#       National Institute on Deafness and Other Communication Disorders
#
# This software/database is a "United States Government Work" under the 
# terms of the United States Copyright Act. It was written as part of 
# the author's official duties as a United States Government employee and 
# thus cannot be copyrighted. This software/database is freely available 
# to the public for use. The NIDCD and the U.S. Government have not placed 
# any restriction on its use or reproduction. 
#
# Although all reasonable efforts have been taken to ensure the accuracy 
# and reliability of the software and data, the NIDCD and the U.S. Government 
# do not and cannot warrant the performance or results that may be obtained 
# by using this software or data. The NIDCD and the U.S. Government disclaim 
# all warranties, express or implied, including warranties of performance, 
# merchantability or fitness for any particular purpose.
#
# Please cite the author in any work or product based on this material.
# 
# ==========================================================================



# ***************************************************************************
#
#   Large-Scale Neural Modeling software (LSNM)
#
#   Section on Brain Imaging and Modeling
#   Voice, Speech and Language Branch
#   National Institute on Deafness and Other Communication Disorders
#   National Institutes of Health
#
#   This file (makefile) was created by Malle Tagamets around 1995
#
#   Last updated by Antonio Ulloa on February 4 2015  
# **************************************************************************/
#
# makefile
#
# Buils a binary for LSNM simulation executable by compiling C source code
# files. 

BASE = ../../bin
CC = g++

sim: actfuncs.o init.o messages.o outfuncs.o parsecxn.o parseset.o \
 	parse.o siminit.o simulate.o unixmain.o writeout.o win.o
	$(CC) *.o -lm -lc -o $(BASE)/sim

parse.o:	win.h simdefs.h simproto.h parse.cc
	$(CC) -c 	parse.cc
actfuncs.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h actfuncs.cc
	$(CC) -c 	actfuncs.cc
init.o:		win.h simdefs.h macros.h classdef.h externs.h simproto.h init.cc
	$(CC) -c 		init.cc
messages.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h messages.cc
	$(CC) -c 	messages.cc
outfuncs.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h outfuncs.cc
	$(CC) -c 	outfuncs.cc
parsecxn.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h parsecxn.cc
	$(CC) -c 	parsecxn.cc
parseset.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h parseset.cc
	$(CC) -c 	parseset.cc
siminit.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h siminit.cc
	$(CC) -c 	siminit.cc
simulate.o:	win.h simdefs.h macros.h classdef.h externs.h simproto.h simulate.cc
	$(CC) -c 	simulate.cc
unixmain.o:	win.h simdefs.h macros.h classdef.h simdecls.h simproto.h unixmain.cc
	$(CC) -c 	unixmain.cc
writeout.o:	win.h simdefs.h macros.h classdef.h simdecls.h simproto.h writeout.cc
	$(CC) -c 	writeout.cc
win.o:	win.h simdefs.h macros.h classdef.h simdecls.h simproto.h win.cc
	$(CC) -c 	win.cc
