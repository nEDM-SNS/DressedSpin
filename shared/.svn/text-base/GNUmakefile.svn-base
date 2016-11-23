# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:40 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := dressedSpin

G4EXLIB := true

.PHONY: all
all: lib


CPPFLAGS := $(user_flags) `$(ROOTSYS)/bin/root-config --cflags`
ROOTLIBS := `$(ROOTSYS)/bin/root-config --libs`
EXTRALIBS += $(ROOTLIBS)

include $(G4INSTALL)/config/binmake.gmk

