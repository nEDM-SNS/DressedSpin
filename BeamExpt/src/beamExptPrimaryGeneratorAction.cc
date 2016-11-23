
#include "beamExptPrimaryGeneratorAction.hh"
#include "beamExptDetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "He3Atom.hh"

#include "globals.hh"
#include "Randomize.hh"
#include "G4TransportationManager.hh"
#include "G4GeometryManager.hh"


beamExptPrimaryGeneratorAction::beamExptPrimaryGeneratorAction()
{
  fMessenger = new beamExptGenMessenger(this);

  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  particleGun->SetParticleDefinition(He3Atom::Definition());

  SetVelocity(100*m/s);
  particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
}

beamExptPrimaryGeneratorAction::~beamExptPrimaryGeneratorAction()
{
  delete particleGun;
  delete fMessenger;
}

void beamExptPrimaryGeneratorAction::SetKineticEnergy(G4double KE)
{
  particleGun->SetParticleEnergy(KE); // 3/2 k T 
}

G4double beamExptPrimaryGeneratorAction::GetKineticEnergy()
{
  return particleGun->GetParticleEnergy();
}

void beamExptPrimaryGeneratorAction::SetVelocity(G4double vel)
{
  G4double mass = He3Atom::Definition()->GetPDGMass();
  G4double KE = 0;
  G4double beta = vel/c_light;
  if(vel/c_light < 0.01) {
    // power series expansion of gamma - 1
    KE = mass*beta*beta/2
         + mass*(pow(beta,4)*3./8. + pow(beta,6)*5./16. + pow(beta,8)*35./128.);
  } else {
    G4double gamma = 1./sqrt(1 - beta*beta);
    KE = (gamma - 1)*mass;
  }

  SetKineticEnergy(KE);
}

G4double beamExptPrimaryGeneratorAction::GetVelocity()
{
  G4double KE = particleGun->GetParticleEnergy();
  G4double mass = He3Atom::Definition()->GetPDGMass();
  return c_light*sqrt(1 - 1./pow(KE/mass + 1, 2));
}

void beamExptPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // direct particle along z-axis
  particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));

  // start particle at origin
  particleGun->SetParticlePosition(G4ThreeVector(0,0,0));

  // set initial polarization
  particleGun->SetParticlePolarization(G4ThreeVector(0., 0., 1.));

  G4cout << "Initial velocity: " << GetVelocity()/(m/s) << " m/s" << G4endl;
  particleGun->GeneratePrimaryVertex(anEvent);
}


//***********************************************************************
// messenger class so we can change parameters with a macro commands


#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4ios.hh"

beamExptGenMessenger::beamExptGenMessenger(beamExptPrimaryGeneratorAction* obj)
  :fGenerator(obj)
{
  dirPrimaryGen = new G4UIdirectory("/Beam/");
  dirPrimaryGen->SetGuidance("Beam commands.");

  velocityCmd = new G4UIcmdWithADouble("/Beam/SetVelocity",this);
  velocityCmd->SetGuidance("Set particel velocity in m/s");
  velocityCmd->SetParameterName("velocity",true,true);

}

beamExptGenMessenger::~beamExptGenMessenger()
{
  delete velocityCmd;
  delete dirPrimaryGen;
}

void beamExptGenMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==velocityCmd )
  { fGenerator->SetVelocity(velocityCmd->GetNewDoubleValue(newValues)*m/s); }
}

G4String beamExptGenMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==velocityCmd )
  { cv = velocityCmd->ConvertToString(fGenerator->GetVelocity()/(m/s)); }
  return cv;
}




