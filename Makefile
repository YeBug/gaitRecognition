#
# Makefile
#
# This file is owed by Reynald Pereira under Kingston University
# No portion of this document may be reproducted, copied
# or revised without written permission of the authors
#
# @author Reynald Pereira <KS10928@kingston.ac.uk>
#

ODIR =			./objects/
IDIR =			./include/
SDIR = 			./src/
LDIR = 			./lib/
BDIR =			./bin/
DOCDIR =		./doc/
DATADIR = 		./data/

CC = 			g++
RM =			rm -f
OPENCVFLAGS =		`pkg-config --cflags opencv`
OPENCVLIBS = 		`pkg-config --cflags --libs opencv`
CPPFLAGS =		-ggdb $(OPENCVFLAGS) -Wall -Wextra -I$(IDIR)
CCFLAGS =		-pedantic -ansi -O3 -g
LIBS =			-L$(LDIR) -lm -lglut
AR =			ar
ARFLAGS =		lrcv
.PHONY : all clean distclean tarball testOpenCv testTexture

all : testOpenCv 

# Non file target, make it easier to compile a prog
testOpenCv: $(BDIR)testOpenCv

testTexture : $(BDIR)testTexture


# Target to create the real execs, own creation
$(BDIR)testOpenCv: $(ODIR)algorithmeEnum.o  $(ODIR)corner.o  $(ODIR)cornerFinder.o  $(ODIR)cornerPrecizer.o  $(ODIR)hornSchunck.o $(ODIR)imageAlgorithme.o $(ODIR)imageEnum.o $(ODIR)lukasKanade.o  $(ODIR)main.o $(ODIR)opticalFlowCalculater.o $(ODIR)pyrLukasKanade.o $(ODIR)tracker.o $(ODIR)lic.o $(ODIR)sift.o $(ODIR)surf.o $(ODIR)regSinThread.o $(ODIR)matrix.o $(ODIR)gaitPrint.o
	$(CC)  $(CCFLAGS) $(CPPFLAGS) $^ -o $@ $(OPENCVLIBS) $(LIBS) -lm




# Target to create all objects files
$(ODIR)%.o: $(SDIR)%.cpp
	$(CC)  $(CCFLAGS) $(CPPFLAGS) -c $< -o $@ $(OPENCVLIBS) $(LIBS)


# Non file target, just to to basis function on all repository

clean :
		-@$(RM) ./*~ $(SDIR)*~ $(IDIR)*~
		-@$(RM) $(ODIR)*.o

distclean : clean
		-@$(RM) $(BDIR)*

tarball : distclean
		directory =`pwd`; cd ..; tar cvfz gaitRecognition.tgz `basename $$directory`