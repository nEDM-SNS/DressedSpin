#include "G4ThreeVector.hh"
#include "Randomize.hh"

inline
G4ThreeVector isotropicRand()
{
// code copied from G4OpBoundaryProcess::G4IsotropicRand
  G4ThreeVector vect;
  G4double len2;
  do {
    vect.setX(G4UniformRand() - 0.5);
    vect.setY(G4UniformRand() - 0.5);
    vect.setZ(G4UniformRand() - 0.5);
    len2 = vect.mag2();
  } while (len2 < 0.01 || len2 > 0.25);
  return vect.unit();
}

