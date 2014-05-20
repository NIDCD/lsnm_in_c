
#if on alw using c++ code
CC = g++
LIB0 =  -lstdc++ -lm

#if on alw using c code, which are netgen and sim codes
#CC = gcc
#LIB0 = -lgcc -lc -lm

# compile on churn, skip the library, let the compiler find it
#setenv LD_LIBRARY_PATH /usr/local/lib if must use g++ on churn
# it is recommended to use CC (SGI's c++) 
#CC = CC
LIB0 = -lm -lc
BASE = /home/bhguest/sgihome/tchen/auditory/bin/

.KEEP_STATE:

time_axis: time_axis.cc 
	$(CC) time_axis.cc  -o  $(BASE)time_axis $(LIB0)

crosswt_au_i: crosswt_au_i.cc 
	$(CC) crosswt_au_i.cc  -o $(BASE)crosswt_au_i $(LIB0)

crossws_au: crossws_au.cc 
	$(CC) crossws_au.cc  -o $(BASE)crossws_au $(LIB0)

genw_au: genw_au.cc 
	$(CC) genw_au.cc  -o $(BASE)genw_au $(LIB0)

altgenw_au: altgenw_au.cc
	$(CC) altgenw_au.cc -o $(BASE)altgenw_au $(LIBO)

altgenw_L_au: altgenw_L_au.cc
	$(CC) altgenw_L_au.cc -o $(BASE)altgenw_L_au $(LIBO)

change: change.cc 
	$(CC) change.cc  -o $(BASE)change $(LIB0)

mkinput: mkinput.cc 
	$(CC) mkinput.cc -o $(BASE)mkinput $(LIB0)  

mkattn_au: mkattn_au.cc
	$(CC) mkattn_au.cc -o $(BASE)mkattn_au $(LIB0)

mkcatout_au: mkcatout_au.cc
	$(CC) mkcatout_au.cc -o $(BASE)mkcatout_au $(LIBO)
  
itoa.o:	itoa.cc
	$(CC) -c itoa.cc  

mkbatchw_au: mkbatchw_au.cc  itoa.o 
	$(CC) mkbatchw_au.cc itoa.o -o $(BASE)mkbatchw_au $(LIB0)  

mkbatchb_au: mkbatchb_au.cc itoa.o
	$(CC) mkbatchb_au.cc itoa.o -o $(BASE)mkbatchb_au $(LIBO)

mkbatchrlc_au: mkbatchrlc_au.cc itoa.o
	$(CC) mkbatchrlc_au.cc itoa.o -o $(BASE)mkbatchrlc_au $(LIBO)

mkbatchr_au: mkbatchr_au.cc itoa.o
	$(CC) mkbatchr_au.cc itoa.o -o $(BASE)mkbatchr_au $(LIBO)

