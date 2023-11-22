##############################
##############################
##                          ##
##  Make file for GIGUTILS  ##
##                          ##
##############################
##############################
#
#  Destination pathnames
#
ROOT    =
BINDIR  = $(ROOT)/usr/local/bin
MANDIR  = $(ROOT)/usr/local/man/man1
PRVDIR  = $$HOME/bin
#
#  BUT FOR NOW WE'RE TESTING
#
#BINDIR  = $$HOME/gigutils.bin
#MANDIR  = $$HOME/gigutils.man
#PRVDIR  = $$HOME/gigutils.prv

#
#  Command configuration parameters
#
CFLAGS  = -I h
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
LIBRARY = \
   gigutils
LIBMODS = \
   usargs \
   usdump
UTILS = \
   comf \
   coml \
   cvtbt \
   cvteol \
   cvttb \
   disf \
   genbf \
   shodt \
   zapf
EXTRA = \
   dism \
   dit \
   fba2asc \
   testargs \
   testbits \
   testenvp \
   testsize \
   teststat \
   testtype

#################
# Derived Lists #
#################
LIB     = lib/$(LIBRARY).a
LIBOBJS = $(foreach mod,$(LIBMODS),obj/$(mod).o)
MAN     = $(foreach util,$(UTILS),man/$(util).1)
EXESRCS = $(foreach util,$(UTILS),src/$(util).c)
EXECOMS = $(foreach util,$(UTILS),com/$(util))
EXELSTS = $(foreach util,$(UTILS),$(util).l)
EXETSTS = $(foreach util,$(UTILS),$(util).t)
TSTSRCS = $(foreach util,$(EXTRA),src/$(util).c)
TSTCOMS = $(foreach util,$(EXTRA),com/$(util))
TSTLSTS = $(foreach util,$(EXTRA),$(util).l)
TSTTSTS = $(foreach util,$(EXTRA),$(util).t)

########
# Help #
########
#
# Spit out usage if no arguments are given to make
#
help:
	@echo "From Makefile:"
	@echo ""
	@echo "To make all executables:"
	@echo "   make all"
	@echo "To test what got made:"
	@echo "   make test"
	@echo "To remove test output files:"
	@echo "   make reset"
	@echo "To install official programs and man pages:"
	@echo "   make install"
	@echo "To install test programs:"
	@echo "   make private"
	@echo "To remove all derived files and start over:"
	@echo "   make clean"
	@echo "Notes:"
	@echo "   If prototypes are a problem, CFLAGS=-D_NOPROTOS"
	@echo "      should fix it."
	@echo "   Official programs and man pages are installed in"
	@echo "      BINDIR = $(BINDIR)"
	@echo "      MANDIR = $(MANDIR)"
	@echo "   Running 'make private' copies test programs to"
	@echo "      PRVDIR = $(PRVDIR)"

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
$(LIB): $(LIBOBJS)
	$(AR_CMD) $(LIB) $?
	$(RN_CMD) $(LIB)

define make-obj
obj/$1.o: src/$1.c
	$(CC_CMD) -o obj/$1.o -c src/$1.c
endef

$(foreach mod,$(LIBMODS),$(eval $(call make-obj,$(mod))))

##########################################
# Rules by which to make the executables #
##########################################
all:	$(patsubst src/%.c,com/%,$(EXESRCS)) \
	$(patsubst src/%.c,com/%,$(TSTSRCS))

define make-util
com/$1: src/$1.c $(LIB)
	$(CC_CMD) -o com/$1 src/$1.c $(LIB)
	strip com/$1
	chmod 755 com/$1
endef

$(foreach mod,$(UTILS),$(eval $(call make-util,$(mod))))
$(foreach mod,$(EXTRA),$(eval $(call make-util,$(mod))))

###############################
# Rules by which to run tests #
###############################
TESTLIST = step1.t step2.t step3.t step4.t step5.t step6.t step7.t step8.t
TESTJUNK = LIST0 LIST1 ORIG TEXT0 TEST1 TEXT1 TEST2 TEXT2 SORT0 SORT1

test:	$(TESTLIST) $(EXETSTS) $(TSTTSTS)

#.c.t:
#	-com/$* -\? >$*.l 2>&1
#	-diff test/$*.b $*.l | tee $*.t

define make-test
$1.t:
	-com/$1 -\? >$1.l 2>&1
	-diff test/$1.b $1.l | tee $1.t
endef

$(foreach mod,$(UTILS),$(eval $(call make-test,$(mod))))
$(foreach mod,$(EXTRA),$(eval $(call make-test,$(mod))))

step1.t:
	-ls > LIST0
	-com/genbf ORIG >step1.l 2>&1
	-diff test/step1.b step1.l | tee step1.t

step2.t:
	-com/disf ORIG >step2.l 2>&1
	-diff test/step2.b step2.l | tee step2.t

step3.t:
	-com/cvtbt ORIG TEXT0 >step3.l 2>&1
	-diff test/step3.b step3.l | tee step3.t

step4.t:
	-sed 's/NUL/0xFF/' <TEXT0 >TEXT1
	-com/cvttb TEXT1 TEST1 >step4.l 2>&1
	-diff test/step4.b step4.l | tee step4.t

step5.t:
	-com/comf ORIG TEST1 >step5.l 2>&1
	-diff test/step5.b step5.l | tee step5.t

step6.t:
	-cp ORIG TEST2
	-echo 7 / 7 : ff 00 5a a5 | com/zapf TEST2
	-com/comf ORIG TEST2 >step6.l 2>&1
	-diff test/step6.b step6.l | tee step6.t

step7.t:
	-com/shodt 0x2BAC5DEF >step7.l 2>&1
	-diff test/step7.b step7.l | tee step7.t

step8.t:
	-ls > LIST1
	-perl -e 'while(<>){y/A-Z/a-z/;print;}' LIST0 | sort > SORT0
	-perl -e 'while(<>){y/A-Z/a-z/;print;}' LIST1 | sort > SORT1
	-com/coml SORT0 SORT1 >step8.l 2>&1
	-diff test/step8.b step8.l | tee step8.t

####################################
# Rules by which to install things #
####################################
install:
	$(CP_CMD) $(EXECOMS) $(BINDIR)
	chmod 644 $(MAN)
	$(CP_CMD) $(MAN) $(MANDIR)

private:
	$(CP_CMD) $(TSTCOMS) $(PRVDIR)

##############################
# Rules by which to clean up #
##############################
reset:
	$(RM_CMD) \
          $(EXELSTS) \
          $(TSTLSTS) \
          $(EXETSTS) \
          $(TSTTSTS) \
          $(TESTLIST:.t=.l) \
          $(TESTLIST) \
          $(TESTJUNK)

clean:
	$(RM_CMD) \
          $(LIBOBJS) \
          $(LIB) \
          $(EXECOMS) \
          $(TSTCOMS) \
          $(EXELSTS) \
          $(TSTLSTS) \
          $(EXETSTS) \
          $(TSTTSTS) \
          $(TESTLIST:.t=.l) \
          $(TESTLIST) \
          $(TESTJUNK)
