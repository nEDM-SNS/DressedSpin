.PHONY: clean

all: libSpinsTree.so process_spin_files

SOFLAGS = -shared

# If on mac os X
OSTYPE = $(shell echo $$OSTYPE)
ifneq (,$(findstring darwin, $(OSTYPE)))
SOFLAGS = -dynamiclib
LDFLAGS = -bind_at_load
endif

vpath % .:../nEDMCell/src:../nEDMCell/include:./src

ROOT_CFLAGS = `$(ROOTSYS)/bin/root-config --cflags`
ROOT_LIBS = `$(ROOTSYS)/bin/root-config --libs` -lThread -lGui -lMinuit

INC_CFLAGS = -I./src -I../nEDMCell/include -DROOTMacros
CXXFLAGS = -I. $(INC_CFLAGS) $(ROOT_CFLAGS)

# 
# to generate streamer functions for lib objects
Dictionary.cpp: SpinsTree.h fieldmapFile.hh LinkDef.h
	rootcint -f Dictionary.cpp -c $(INC_CFLAGS) SpinsTree.h fieldmapFile.hh LinkDef.h

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

#
libSpinsTree.so: SpinsTree.o fieldmapFile.o Dictionary.o
	$(CXX) $(ROOT_LIBS) $(SOFLAGS) SpinsTree.o fieldmapFile.o \
Dictionary.o -o libSpinsTree.so
#

process_spin_files : process_spin_files.o libSpinsTree.so
	$(CXX) $(ROOT_LIBS) $(LDFLAGS) -o process_spin_files process_spin_files.o \
libSpinsTree.so

clean: 
	rm -f *.d *.o Dictionary.* libSpinsTree.so process_spin_files

blank:
	touch blank

include blank $(wildcard *.d)
