// copied from G4He3 class.
// somehow the mass isn't correct in G4He3 (?)

#ifndef He3Atom_h
#define He3Atom_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4ParticleDefinition.hh"
#include "G4Ions.hh"

// ######################################################################
// ###                            He3                                 ###
// ######################################################################

class He3Atom : public G4Ions
{
 private:
   static He3Atom* theInstance;
   He3Atom(){}
   ~He3Atom(){}

 public:
   static He3Atom* Definition();
   static He3Atom* He3Definition();
   static He3Atom* He3();
};

#endif

