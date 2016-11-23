#include "UIUCCryoPhysicsList.hh"

#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"
#include "periodicStepping.hh"
#include "neutralSpinRotation.hh"

#include "BlochEq_mcgregor90.hh"

const G4double periodicStepping::kMaxSimulationSeconds = 1;

UIUCCryoPhysicsList::UIUCCryoPhysicsList()
 : dressedSpinPhysicsList()
{
}

UIUCCryoPhysicsList::~UIUCCryoPhysicsList()
{
  if(fBlochEq) delete fBlochEq;
}

void UIUCCryoPhysicsList::ConstructProcess()
{
  AddTransportation();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    G4cout << "UIUCCryoPhysicsList::ConstructProcess " << particleName << G4endl;

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
      fBlochEq = new BlochEq_mcgregor90;
      fNeutralSpinRotation->SetBlochEqObj(fBlochEq);

      fPeriodicStepping = new periodicStepping();
      G4cout << "Adding periodicStepping: "
             << pmanager->AddProcess(fPeriodicStepping, ordDefault,ordInActive,ordDefault) << G4endl;
      fPeriodicStepping->SetTimeInterval(0.002*s);
      fPeriodicStepping->SetPrintInterval(5000);
      fPeriodicStepping->CreateHistograms();

    }

  }
}

