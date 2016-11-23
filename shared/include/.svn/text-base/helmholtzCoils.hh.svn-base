#ifndef helmholtzCoils_h
#define helmholtzCoils_h 1

// This class computes the magnetic field in the center of a helmholtz coil.
// The configuration is two circular wire loops normal to the z-axis,
// one loop at z = +a/2 and the other at z = -a/2, where a is the radius
// of the coils.

#include "globals.hh"

class helmholtzCoils
{
  public:

  helmholtzCoils();
  helmholtzCoils(G4double radius, G4double current);
  virtual ~helmholtzCoils();

  void Bfield(G4double r, G4double z, G4double &Br, G4double &Bz);


  void SetRadius(G4double val) { fa = val; }
  void SetCurrent(G4double val) { fI0 = val; }
  G4double GetRadius() { return fa; }
  G4double GetCurrent() { return fI0; }

  void SetFieldAtOrigin(G4double Bz); // this is an alternative to setting fI0 (and mu0)
  G4double GetFieldAtOrigin(); // computes and returns field at origin

  private:

  G4double fa;  // radius of loop
  G4double fI0; // permeability of free space (mu0) * current through loop (I0)

};

#endif

