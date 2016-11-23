# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:40 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := sim_UIUCCryo


G4TARGET := $(name)

G4EXLIB := true


.PHONY: all
all: lib bin


CPPFLAGS := $(user_flags) `$(ROOTSYS)/bin/root-config --cflags` -I../shared/include
ROOTLIBS := `$(ROOTSYS)/bin/root-config --libs`
EXTRALIBS += $(ROOTLIBS) -L$(G4WORKDIR)/tmp/Linux-g++ -ldressedSpin

#  vpath % ../shared/src

include $(G4INSTALL)/config/binmake.gmk

