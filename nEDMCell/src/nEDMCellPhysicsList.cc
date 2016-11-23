#include "nEDMCellPhysicsList.hh"

#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"
#include "periodicStepping.hh"
#include "neutralSpinRotation.hh"

#include "BlochEq_nEDMField.hh"

// define maximum simulation time here:
const G4double periodicStepping::kMaxSimulationSeconds = 1000;

nEDMCellPhysicsList::nEDMCellPhysicsList()
 : dressedSpinPhysicsList()
{
}

nEDMCellPhysicsList::~nEDMCellPhysicsList()
{
  if(fBlochEq) delete fBlochEq;
}

void nEDMCellPhysicsList::ConstructProcess()
{
  AddTransportation();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    G4cout << "nEDMCellPhysicsList::ConstructProcess " << particleName << G4endl;

    if(strncmp("He3Atom",particleName,7) == 0) {
      fDiffusionProcess = new diffusionProcess();
      G4cout << "Adding DiffusionProcess: "
             <<  pmanager->AddDiscreteProcess(fDiffusionProcess) << G4endl;

      fDiffusionBoundaryProcess = new diffusionBoundaryProcess();
      G4cout << "Adding DiffusionBoundaryProcess: "
             << pmanager->AddDiscreteProcess(fDiffusionBoundaryProcess) << G4endl;
#if 0
      G4cout << "--->setting specular wall bounces" << G4endl;
      fDiffusionBoundaryProcess->SetTypeOfWallBounce(SpecularReflection);
#endif

      fNeutralSpinRotation = new neutralSpinRotation();
      G4cout << "Adding neutralSpinRotation: "
             << pmanager->AddProcess(fNeutralSpinRotation, ordDefault,ordInActive,ordDefault) << G4endl;

      // This is the Bloch equation solver for the particular
      // magnetic field configuration.
      if(fBlochEq) {
        G4cout << "nEDMCellPhysicsList: BlochEq object already exists?" << G4endl;
        delete fBlochEq;
      }
      fBlochEq = new BlochEq_nEDMField;
#if 0
      G4cout << "Using rotating frame in BlochEq object." << G4endl;
      ((BlochEq_nEDMField*)fBlochEq)->SetRotatingFrameFlag(true);
#endif
      fNeutralSpinRotation->SetBlochEqObj(fBlochEq);

      fPeriodicStepping = new periodicStepping();
      G4cout << "Adding periodicStepping: "
             << pmanager->AddProcess(fPeriodicStepping, ordDefault,ordInActive,ordDefault) << G4endl;
      fPeriodicStepping->SetTimeInterval(0.001*s);
      fPeriodicStepping->SetPrintInterval(10000); // print every 0.001*10000 seconds
      fPeriodicStepping->CreateHistograms(true); // arg=true means save data as ROOT TTree.
                                                 // change to arg=false to save as a histogram
                                                 // instead, which avoids having to later
                                                 // analyze the tree into spin vs. time.

    }

  }
}

