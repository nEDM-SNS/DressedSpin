
#include "beamExptPhysicsList.hh"
#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"

#include "He3Atom.hh"

#include "G4UserSpecialCuts.hh"
#include "neutralSpinRotation.hh"
#include "periodicStepping.hh"

beamExptPhysicsList::beamExptPhysicsList()
 : G4VUserPhysicsList()
{
}

beamExptPhysicsList::~beamExptPhysicsList()
{;}

void beamExptPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  G4Geantino::GeantinoDefinition();
  He3Atom::He3Definition();
}

void beamExptPhysicsList::ConstructProcess()
{
  AddTransportation();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if(strncmp("He3Atom",particleName,7) == 0) {
      fBeamExptBoundaryProcess = new beamExptBoundaryProcess();
      G4cout << "Adding BeamExptBoundaryProcess: "
             << pmanager->AddDiscreteProcess(fBeamExptBoundaryProcess) << G4endl;
      fNeutralSpinRotation = new neutralSpinRotation();
      G4cout << "Adding neutralSpinRotation: "
             << pmanager->AddProcess(fNeutralSpinRotation, ordDefault,ordInActive,ordDefault) << G4endl;
      fPeriodicStepping = new periodicStepping();
      G4cout << "Adding periodicStepping: "
             << pmanager->AddProcess(fPeriodicStepping, ordDefault,ordInActive,ordDefault) << G4endl;

      G4cout << "beamExptPhysicsList::ConstructProcess " << particleName << G4endl;
    }

  }
}

void beamExptPhysicsList::SetCuts()
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

