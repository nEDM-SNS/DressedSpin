#include "UIUCTableTopPhysicsList.hh"

#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"
#include "periodicStepping.hh"
#include "neutralSpinRotation.hh"

#include "BlochEq_UIUCTableTop.hh"

const G4double periodicStepping::kMaxSimulationSeconds = 1;

UIUCTableTopPhysicsList::UIUCTableTopPhysicsList()
 : dressedSpinPhysicsList()
{
}

UIUCTableTopPhysicsList::~UIUCTableTopPhysicsList()
{
  if(fBlochEq) delete fBlochEq;
}

void UIUCTableTopPhysicsList::ConstructProcess()
{
  AddTransportation();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    G4cout << "UIUCTableTopPhysicsList::ConstructProcess " << particleName << G4endl;

    if(strncmp("He3Atom",particleName,7) == 0) {
      fDiffusionProcess = new diffusionProcess();
      G4cout << "Adding DiffusionProcess: "
             <<  pmanager->AddDiscreteProcess(fDiffusionProcess) << G4endl;

      fDiffusionBoundaryProcess = new diffusionBoundaryProcess();
      G4cout << "Adding DiffusionBoundaryProcess: "
             << pmanager->AddDiscreteProcess(fDiffusionBoundaryProcess) << G4endl;

      fNeutralSpinRotation = new neutralSpinRotation();
      G4cout << "Adding neutralSpinRotation: "
             << pmanager->AddProcess(fNeutralSpinRotation, ordDefault,ordInActive,ordDefault) << G4endl;

      // This is the Bloch equation solver for the particular
      // magnetic field configuration.
      if(fBlochEq) delete fBlochEq;
      fBlochEq = new BlochEq_UIUCTableTop;
      fNeutralSpinRotation->SetBlochEqObj(fBlochEq);

      fPeriodicStepping = new periodicStepping();
      G4cout << "Adding periodicStepping: "
             << pmanager->AddProcess(fPeriodicStepping, ordDefault,ordInActive,ordDefault) << G4endl;
      fPeriodicStepping->SetTimeInterval(0.00001*s);
      fPeriodicStepping->SetPrintInterval(1000);
      fPeriodicStepping->CreateHistograms();

    }

  }
}

