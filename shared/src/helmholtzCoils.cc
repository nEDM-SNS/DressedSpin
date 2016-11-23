#include "helmholtzCoils.hh"
#include <math.h>

helmholtzCoils::helmholtzCoils()
{
  fa = 1*m;
  fI0 = 1*ampere;
}

helmholtzCoils::helmholtzCoils(G4double radius, G4double current)
{
  fa = radius;
  fI0 = current;
}

helmholtzCoils::~helmholtzCoils()
{
}

void helmholtzCoils::SetFieldAtOrigin(G4double Bz)
{
// just set fI0 to a value that gives the desired field
  fI0 = Bz*(5*sqrt(5)*fa/8)/mu0;
}

G4double helmholtzCoils::GetFieldAtOrigin()
{
  G4double Br, Bz;
  Bfield(0,0,Br,Bz);
  return Bz;
}

void helmholtzCoils::Bfield(G4double r, G4double z, G4double &Br, G4double &Bz)
{
  G4double a2 = fa*fa;
  G4double a3 = fa*a2;
  G4double a4 = fa*a3;
  G4double a8 = pow(fa,8);
  G4double a9 = fa*a8;

  G4double r2 = r*r;
  G4double r4 = r2*r2;

  G4double z2 = z*z;
  G4double z4 = z2*z2;

  Br = mu0*fI0*1536*r2*z*(-125*a4 + 400*a3*r - 2688*fa*r*z2 + 7088*r2*z2 + a2*(-1310*r2 + 1120*z2))/(78125*sqrt(5)*a8);

  Bz = mu0*fI0*8*(15625*a8 - 157248*r4*z4 - 2250*a4*(3*r4 - 24*r2*z2 + 8*z4) + 36960*a2*(3*r4*z2 - 4*r2*z4))/(78125*sqrt(5)*a9);

// field at origin is Br=0, Bz=mu0*fI0*8/(5*sqrt(5)*fa)

}


