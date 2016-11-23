//
#include "He3Atom.hh"
#include "G4ParticleTable.hh"

// ######################################################################
// ###                           He3                                  ###
// ######################################################################

He3Atom* He3Atom::theInstance = 0;

He3Atom* He3Atom::Definition()
{
  if (theInstance !=0) return theInstance;
  const G4String name = "He3Atom";
  // search in particle table]
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  G4Ions* anInstance =  reinterpret_cast<G4Ions*>(pTable->FindParticle(name));
  if (anInstance ==0) 
  {
  // create particle
  //
  //    Arguments for constructor are as follows
  //               name             mass          width         charge
  //             2*spin           parity  C-conjugation
  //          2*Isospin       2*Isospin3       G-parity
  //               type    lepton number  baryon number   PDG encoding
  //             stable         lifetime    decay table
  //             shortlived      subType    anti_encoding
  //             excitation 

    G4double mass = 2.80923*GeV; // atomic mass of 3He

    anInstance = new G4Ions(
                 name,   mass,       0.0*MeV,  0.0*eplus,
                    1,              +1,             0,
                    0,               0,             0,
            "nucleus",               0,            +3, 1000020030,
                 true,            -1.0,          NULL,
		false,        "static",             0,
                  0.0
              );
 
    // Magnetic Moment
    G4double mN = eplus*hbar_Planck/2./(proton_mass_c2 /c_squared);
    anInstance->SetPDGMagneticMoment( -2.12762485 * mN);

  }
  //No Anti particle registered
  anInstance->SetAntiPDGEncoding(0);

  theInstance = reinterpret_cast<He3Atom*>(anInstance);
  return theInstance;
}

He3Atom*  He3Atom::He3Definition()
{
  return Definition();
}

He3Atom*  He3Atom::He3()
{
  return Definition();
}


