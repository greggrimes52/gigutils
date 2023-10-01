#############################
#############################
##                         ##
##  Make file for GIGUTIL  ##
##                         ##
#############################
#############################
#
#  Destination pathnames
#
#ROOT   =
BINDIR  = $(ROOT)/usr/local/bin
MANDIR  = $(ROOT)/usr/local/man/man1
PRVDIR  = $$HOME/bin
#
#  BUT FOR NOW WE'RE TESTING
#
BINDIR  = $$HOME/gigutil.bin
MANDIR  = $$HOME/gigutil.man
PRVDIR  = $$HOME/gigutil.prv

#
#  Command configuration parameters
#
#CFLAGS =
CC      = cc
CCOPTS  =
CC_CMD  = $(CC) $(CCOPTS) $(CFLAGS)
AR      = ar
AROPTS  = r
AR_CMD  = $(AR) $(AROPTS)
RN      = ranlib
RNOPTS  =
RN_CMD  = $(RN) $(RNOPTS)
CP      = cp
CPOPTS  = -p
CP_CMD  = $(CP) $(CPOPTS)
RM      = rm
RMOPTS  = -f
RM_CMD  = $(RM) $(RMOPTS)

#
#  We need /bin/sh because the tests use 2>&1
#
SHELL   = /bin/sh

###############################
# Lists of everything to make #
###############################
MAN     = \
   comf.1 \
   coml.1 \
   cvtbt.1 \
   cvteol.1 \
   cvttb.1 \
   disf.1 \
   genbf.1 \
   shodt.1 \
   zapf.1
LIB     = \
   gigutil.a
LIBSRCS = \
   usargs.c \
   usdump.c
EXESRCS = \
   comf.c \
   coml.c \
   cvtbt.c \
   cvteol.c \
   cvttb.c \
   disf.c \
   genbf.c \
   shodt.c \
   zapf.c
TSTSRCS = \
   dism.c \
   dit.c \
   fba2asc.c \
   testargs.c \
   testbits.c \
   testenvp.c \
   testsize.c \
   teststat.c \
   testtype.c

########
# Help #
########
#
# Spit out usage if no arguments are given to make
#
help:
	@echo "To make all executables:"
	@echo "   make all"
	@echo "To test what got made:"
	@echo "   make test"
	@echo "To install official programs and man pages:"
	@echo "   make install"
	@echo "To install test programs:"
	@echo "   make private"
	@echo "To remove all derived files:"
	@echo "   make clean"
	@echo "Notes:"
	@echo "   If prototypes are a problem, CFLAGS=-D_NOPROTOS"
	@echo "      should fix it."
	@echo "   Official programs and man pages are installed in"
	@echo "      BINDIR = (ROOT)/usr/local/bin"
	@echo "      MANDIR = (ROOT)/usr/local/man/man1"
	@echo "   Running 'make private' copies test programs to"
	@echo "      PRVDIR = ~/bin"

#####################################################
# Additional suffixes to support in inference rules #
#####################################################
.SUFFIXES: .t

###################################
# Rules by which to do everything #
###################################
itso: all test install private clean

######################################
# Rules by which to make the library #
######################################
$(LIB): $(LIBSRCS:.c=.o)
	$(AR_CMD) $(LIB) $?
	$(RN_CMD) $(LIB)

.c.o:
	$(CC_CMD) -c $<

##########################################
# Rules by which to make the executables #
##########################################
all:	$(EXESRCS:.c=) $(TSTSRCS:.c=)

comf: comf.c $(LIB)
	$(CC_CMD) -o comf comf.c $(LIB)
	strip comf
	chmod 755 comf

coml: coml.c $(LIB)
	$(CC_CMD) -o coml coml.c $(LIB)
	strip coml
	chmod 755 coml

cvtbt: cvtbt.c $(LIB)
	$(CC_CMD) -o cvtbt cvtbt.c $(LIB)
	strip cvtbt
	chmod 755 cvtbt

cvteol: cvteol.c $(LIB)
	$(CC_CMD) -o cvteol cvteol.c $(LIB)
	strip cvteol
	chmod 755 cvteol

cvttb: cvttb.c $(LIB)
	$(CC_CMD) -o cvttb cvttb.c $(LIB)
	strip cvttb
	chmod 755 cvttb

disf: disf.c $(LIB)
	$(CC_CMD) -o disf disf.c $(LIB)
	strip disf
	chmod 755 disf

genbf: genbf.c $(LIB)
	$(CC_CMD) -o genbf genbf.c $(LIB)
	strip genbf
	chmod 755 genbf

shodt: shodt.c $(LIB)
	$(CC_CMD) -o shodt shodt.c $(LIB)
	strip shodt
	chmod 755 shodt

zapf: zapf.c $(LIB)
	$(CC_CMD) -o zapf zapf.c $(LIB)
	strip zapf
	chmod 755 zapf

dism: dism.c $(LIB)
	$(CC_CMD) -o dism dism.c $(LIB)
	strip dism
	chmod 755 dism

dit: dit.c $(LIB)
	$(CC_CMD) -o dit dit.c $(LIB)
	strip dit
	chmod 755 dit

fba2asc: fba2asc.c $(LIB)
	$(CC_CMD) -o fba2asc fba2asc.c $(LIB)
	strip fba2asc
	chmod 755 fba2asc

testargs: testargs.c $(LIB)
	$(CC_CMD) -o testargs testargs.c $(LIB)
	strip testargs
	chmod 755 testargs

testbits: testbits.c $(LIB)
	$(CC_CMD) -o testbits testbits.c $(LIB)
	strip testbits
	chmod 755 testbits

testenvp: testenvp.c $(LIB)
	$(CC_CMD) -o testenvp testenvp.c $(LIB)
	strip testenvp
	chmod 755 testenvp

testsize: testsize.c $(LIB)
	$(CC_CMD) -o testsize testsize.c $(LIB)
	strip testsize
	chmod 755 testsize

teststat: teststat.c $(LIB)
	$(CC_CMD) -o teststat teststat.c $(LIB)
	strip teststat
	chmod 755 teststat

testtype: testtype.c $(LIB)
	$(CC_CMD) -o testtype testtype.c $(LIB)
	strip testtype
	chmod 755 testtype

###############################
# Rules by which to run tests #
###############################
TESTLIST = step1.t step2.t step3.t step4.t step5.t step6.t step7.t step8.t
TESTJUNK = LIST0 LIST1 ORIG TEXT0 TEST1 TEXT1 TEST2 TEXT2 SORT0 SORT1

test:	$(TESTLIST) $(EXESRCS:.c=.t) $(TSTSRCS:.c=.t)

.c.t:
	-./$* -\? >$*.l 2>&1
	-diff $*.b $*.l | tee $*.t

step1.t:
	-ls > LIST0
	-./genbf ORIG >step1.l 2>&1
	-diff step1.b step1.l | tee step1.t

step2.t:
	-./disf ORIG >step2.l 2>&1
	-diff step2.b step2.l | tee step2.t

step3.t:
	-./cvtbt ORIG TEXT0 >step3.l 2>&1
	-diff step3.b step3.l | tee step3.t

step4.t:
	-sed 's/NUL/0xFF/' <TEXT0 >TEXT1
	-./cvttb TEXT1 TEST1 >step4.l 2>&1
	-diff step4.b step4.l | tee step4.t

step5.t:
	-./comf ORIG TEST1 >step5.l 2>&1
	-diff step5.b step5.l | tee step5.t

step6.t:
	-cp ORIG TEST2
	-echo 7 / 7 : ff 00 5a a5 | ./zapf TEST2
	-./comf ORIG TEST2 >step6.l 2>&1
	-diff step6.b step6.l | tee step6.t

step7.t:
	-./shodt 0x2BAC5DEF >step7.l 2>&1
	-diff step7.b step7.l | tee step7.t

step8.t:
	-ls > LIST1
	-perl -e 'while(<>){y/A-Z/a-z/;print;}' LIST0 | sort > SORT0
	-perl -e 'while(<>){y/A-Z/a-z/;print;}' LIST1 | sort > SORT1
	-./coml SORT0 SORT1 >step8.l 2>&1
	-diff step8.b step8.l | tee step8.t

####################################
# Rules by which to install things #
####################################
install:
	$(CP_CMD) $(EXESRCS:.c=) $(BINDIR)
	chmod 644 $(MAN)
	$(CP_CMD) $(MAN) $(MANDIR)

private:
	$(CP_CMD) $(TSTSRCS:.c=) $(PRVDIR)

##############################
# Rules by which to clean up #
##############################
clean:
	$(RM_CMD) \
          $(LIBSRCS:.c=.o) \
          $(LIB) \
          $(EXESRCS:.c=) \
          $(EXESRCS:.c=.o) \
          $(EXESRCS:.c=.l) \
          $(EXESRCS:.c=.t) \
          $(TSTSRCS:.c=) \
          $(TSTSRCS:.c=.o) \
          $(TSTSRCS:.c=.l) \
          $(TSTSRCS:.c=.t) \
          $(TESTLIST:.t=.l) \
          $(TESTLIST) \
          $(TESTJUNK)
