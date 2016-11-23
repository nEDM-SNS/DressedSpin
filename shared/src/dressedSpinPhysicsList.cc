
#include "dressedSpinPhysicsList.hh"
#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"

#include "He3Atom.hh"

#include "G4UserSpecialCuts.hh"
#include "periodicStepping.hh"
#include "neutralSpinRotation.hh"


#if 0
const G4double periodicStepping::kMaxSimulationSeconds = 1;
#endif

dressedSpinPhysicsList::dressedSpinPhysicsList()
 : G4VUserPhysicsList(), fBlochEq(0)
{
}

dressedSpinPhysicsList::~dressedSpinPhysicsList()
{
}

void dressedSpinPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  G4Geantino::GeantinoDefinition();
  He3Atom::He3Definition();
}

void dressedSpinPhysicsList::ConstructProcess()
{
}

void dressedSpinPhysicsList::SetCuts()
{
  // oppress error messages even in case e/gamma/proton do not exist            
  G4int temp = GetVerboseLevel();
  SetVerboseLevel(0);                                                           
  //  " G4VUserPhysicsList::SetCutsWithDefault" method sets 
  //   the default cut value for all particle types 
  SetCutsWithDefault();   

  // Retrieve verbose level
  SetVerboseLevel(temp);  
}

