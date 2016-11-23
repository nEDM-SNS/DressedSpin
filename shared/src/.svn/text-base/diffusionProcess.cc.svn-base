
#include "diffusionProcess.hh"
#include "G4DynamicParticle.hh"
#include "G4PhysicsLogVector.hh"
#include "G4ParticleChange.hh"
#include "diffusionMaterial.hh"
#include "G4TransportationManager.hh"
#include "G4Navigator.hh"
#include "dressedSpinParameters.hh"
#include "dressedSpin_utils.hh"

// constructor
diffusionProcess::diffusionProcess(const G4String& processName)
                               :G4VDiscreteProcess(processName, fUserDefined),
				verboseLevel(1),
                                HighestValue(20.0),
                                fMeanFreePath(4.396*cm) // T = 0.3 K
{
#ifdef G4VERBOSE
  if (GetVerboseLevel()>1) {
    G4cerr << "diffusionProcess  constructor " << "  Name:" << processName << G4endl;
  }
#endif
  htest = new TH1D("htest","htest",2000, 0., 20.);

  pParticleChange = &aParticleChange;
}

diffusionProcess::~diffusionProcess()
{
}

G4bool diffusionProcess::IsApplicable(const G4ParticleDefinition& aParticleType)
{
   // check if the particle undergoes dressedSpin
   return true; 
}

G4double diffusionProcess::GetMeanLifeTime(const G4Track& aTrack  ,
                                  G4ForceCondition*)
{
   // returns the mean free path in GEANT4 internal units
   G4double meanlife;

   // get particle 
   const G4DynamicParticle* aParticle = aTrack.GetDynamicParticle();
   G4ParticleDefinition* aParticleDef = aParticle->GetDefinition();
   G4double aLife = aParticleDef->GetPDGLifeTime();

   // check if the particle is stable?
   if (aParticleDef->GetPDGStable()) {
     meanlife = DBL_MAX;
    
   } else {
     meanlife = aLife;
   }

#ifdef G4VERBOSE
   if (GetVerboseLevel()>1) {
     G4cout << "mean life time: "<< meanlife/ns << "[ns]" << G4endl;
   }
#endif

   return  meanlife;
}

G4double diffusionProcess::GetMeanFreePath(const G4Track& aTrack,G4double, G4ForceCondition*)
{
  G4Material* Material1 = aTrack.GetMaterial();
  if((strncmp(Material1->GetName(), "LHe4", 4) == 0)
     || (strncmp(Material1->GetName(), "He3Gas", 6) == 0)) {
    fMeanFreePath = ((diffusionMaterial*)Material1)->GetMeanFreePath();
  } else {
    fMeanFreePath = DBL_MAX;
  }

  return fMeanFreePath;
}

void diffusionProcess::BuildPhysicsTable(const G4ParticleDefinition&)
{
  return;
}

G4VParticleChange* diffusionProcess::DiffuseIt(const G4Track& aTrack, const G4Step& aStep)
{
// If the tracked 3He scatters, simply choose a new, random direction for it.


  //   Initialize ParticleChange
  //     all members of G4VParticleChange are set to equal to 
  //     corresponding member in G4Track
  pParticleChange->Initialize(aTrack);

  // get particle 
  const G4DynamicParticle* aParticle = aTrack.GetDynamicParticle();

  // G4ThreeVector OldMomentum(aParticle->GetMomentumDirection());
  NewMomentum = isotropicRand(); // defined in dressedSpin_utils.hh

  aParticleChange.ProposeMomentumDirection(NewMomentum);

  htest->Fill(aTrack.GetStepLength()/mm);

  ClearNumberOfInteractionLengthLeft();

  return pParticleChange;
} 


void diffusionProcess::StartTracking(G4Track*)
{
  currentInteractionLength = -1.0;
  ResetNumberOfInteractionLengthLeft();
 
}

void diffusionProcess::EndTracking()
{
  // Clear NumberOfInteractionLengthLeft
  ClearNumberOfInteractionLengthLeft();

  currentInteractionLength = -1.0;
}


