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
CPPFLAGS =		-Wall -Wextra -I$(IDIR)
CCFLAGS =		-pedantic -ansi -03
LIBS =			-L$(LDIR)
AR =			ar
ARFLAGS =		lrcv

.PHONY : all clean distclean tarball

all :

# Non file target, make it easier to compile a prog


# Target to create the real execs, own creation


# Target to create all objects files


# Non file target, just to to basis function on all repository

clean :
		-@$(RM) ./*~ $(SDIR)*~ $(IDIR)*~
		-@$(RM) $(ODIR)*.o

distclean : clean
		-@$(RM) $(BDIR)*

tarball : distclean
		directory =`pwd`; cd ..; tar cvfz gaitRecognition.tgz `basename $$directory`