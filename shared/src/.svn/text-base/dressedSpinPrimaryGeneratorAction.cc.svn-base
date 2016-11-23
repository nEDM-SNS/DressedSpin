
#include "dressedSpinPrimaryGeneratorAction.hh"
#include "dressedSpinDetectorConstruction.hh"

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

#include "dressedSpinParameters.hh"
#include "dressedSpin_utils.hh"


dressedSpinPrimaryGeneratorAction::dressedSpinPrimaryGeneratorAction(G4ParticleDefinition* particle_def)
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  if(particle_def) {
    particleGun->SetParticleDefinition(particle_def);
    particleMass = particle_def->GetPDGMass();
  } else {
    particleGun->SetParticleDefinition(He3Atom::Definition());
    particleMass = He3Atom::Definition()->GetPDGMass();
  }

  SetKineticEnergy(3.8e-11*MeV); // 3/2 k T,  T = 0.3 K. 
  particleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
  particleGun->SetParticlePolarization(G4ThreeVector(0, 0, 1));

  aNavigator = new G4Navigator();
  aTouchableHandle = new G4TouchableHistory();

}

void dressedSpinPrimaryGeneratorAction::SetInitialPolarization(G4ThreeVector& vec)
{
  particleGun->SetParticlePolarization(vec);
}

G4ThreeVector dressedSpinPrimaryGeneratorAction::GetInitialPolarization()
{
  return particleGun->GetParticlePolarization();
}

void dressedSpinPrimaryGeneratorAction::SetKineticEnergy(G4double KE)
{
  particleGun->SetParticleEnergy(KE); // 3/2 k T 
  G4double m = particleMass;
  particleVelocity = c_light*std::sqrt(KE*(KE+2.*m))/(KE+m);
}

G4double dressedSpinPrimaryGeneratorAction::GetKineticEnergy()
{
  return particleGun->GetParticleEnergy();
}

dressedSpinPrimaryGeneratorAction::~dressedSpinPrimaryGeneratorAction()
{
  delete particleGun;
}

void dressedSpinPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Call dressedSpinParameters::changedPT() to make sure all parameters
  // are set appropriately for the temperature.  In particular, the
  // particalGun KE is reset to the value consistent with a free 3He particle;
  // otherwise, if the particle starts in LHe4, the KE would be erroneously
  // scaled by another factor of m_3/m_eff each time a particle subsequent to
  // the first is created (unless e.g. the macro command "/kinetics/SetTemperature 0.4"
  // is called before each subsequent "/run/beamOn 1").
  if(kinetic_params) {
    kinetic_params->changedPT();
  } else {
    G4cout << "error in dressedSpinPrimaryGeneratoreAction::GeneratePrimaries" << G4endl;
    G4cout << "    kinetic_params object pointer not set." << G4endl;
    return;
  }


  NewMomentum = isotropicRand();

  particleGun->SetParticleMomentumDirection(NewMomentum);

  ChooseInitialPosition();
  if( (particleGun->GetParticleDefinition()->GetParticleName() == "He3Atom")
      && (fStartingMaterial->GetName() == "LHe4") ) {
    G4double KE = GetKineticEnergy();
    SetKineticEnergy(KE/2.4); // scale KE by m_3/m_eff if in LHe4
    G4cout << "GeneratePrimaries: scaling initial KE by m_3/m_eff" << G4endl;
  }

  particleGun->GeneratePrimaryVertex(anEvent);
}


void dressedSpinPrimaryGeneratorAction::ChooseInitialPosition()
{
  dressedSpinDetectorConstruction* det = (dressedSpinDetectorConstruction*)
           (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  G4double xmin = det->GetCellXmin();
  G4double xmax = det->GetCellXmax();
  G4double ymin = det->GetCellYmin();
  G4double ymax = det->GetCellYmax();
  G4double zmin = det->GetCellZmin();
  G4double zmax = det->GetCellZmax();

  aNavigator->SetWorldVolume(
      G4TransportationManager::GetTransportationManager()->
      GetNavigatorForTracking()->GetWorldVolume());

  G4GeometryManager* geomManager = G4GeometryManager::GetInstance();
  if(!geomManager->IsGeometryClosed()) {
    geomManager->OpenGeometry();
    geomManager->CloseGeometry(true);
  }

  G4double safety = 0; // distance to nearest boundary
  G4ThreeVector p0;
  G4VPhysicalVolume* vol;
  do {
    // choose (global) coordinates that may be within cell
    G4double x = xmin + (xmax - xmin)*G4UniformRand();
    G4double y = ymin + (ymax - ymin)*G4UniformRand();
    G4double z = zmin + (zmax - zmin)*G4UniformRand();
    p0 = G4ThreeVector(x, y, z);

    vol = aNavigator->LocateGlobalPointAndSetup(p0,0,false);
    G4cout << "p0 = " << p0/cm << ", vol: " << vol->GetName() << G4endl;

  } while( strcmp("cell",vol->GetName()) != 0 );

  fStartingMaterial = vol->GetLogicalVolume()->GetMaterial();
  particleGun->SetParticlePosition(p0);
}


bool dressedSpinPrimaryGeneratorAction::PointIsInCell(const G4ThreeVector& p)
{
  aNavigator->SetWorldVolume(
      G4TransportationManager::GetTransportationManager()->
      GetNavigatorForTracking()->GetWorldVolume());

  G4GeometryManager* geomManager = G4GeometryManager::GetInstance();
  if(!geomManager->IsGeometryClosed()) {
    geomManager->OpenGeometry();
    geomManager->CloseGeometry(true);
  }

  G4VPhysicalVolume* vol = aNavigator->LocateGlobalPointAndSetup(p,0,false);
  fStartingMaterial = vol->GetLogicalVolume()->GetMaterial();

  if( strncmp("cell",vol->GetName(),4) == 0 ) return true;
  else return false;

}


