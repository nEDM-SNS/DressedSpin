
#include "neutralSpinRotation.hh"
#include "BlochEq_beamExpt.hh"

neutralSpinRotation::neutralSpinRotation( G4int verboseLevel )
  : G4VProcess( G4String("NeutralSpinRotation"), fUserDefined),
    fVerboseLevel( verboseLevel )
{

  static G4TouchableHandle nullTouchableHandle;  // Points to (G4VTouchable*) 0
  fCurrentTouchableHandle = nullTouchableHandle; 

  G4cout << "Creating BlochEq_beamExpt object" << G4endl;
  fBlochEq = new BlochEq_beamExpt;
}

neutralSpinRotation::~neutralSpinRotation()
{
  delete fBlochEq;
}


//////////////////////////////////////////////////////////////////////////
//
//  This ensures that the AtRest or PostStep action is always called,
//  so that it can do the spin rotation over a given step.
// 
G4double neutralSpinRotation::
AtRestGetPhysicalInteractionLength( const G4Track&,
                                            G4ForceCondition* pForceCond )
{ 
  *pForceCond = Forced ; 
  return DBL_MAX ;  // was kInfinity ; but convention now is DBL_MAX
}

G4double neutralSpinRotation::
PostStepGetPhysicalInteractionLength( const G4Track& track,
                                   G4double  previousStepSize,
                                   G4ForceCondition* pForceCond )
{ 
  *pForceCond = Forced ; 
  return DBL_MAX ;  // was kInfinity ; but convention now is DBL_MAX
}


/////////////////////////////////////////////////////////////////////////////
//

G4VParticleChange* neutralSpinRotation::PostStepDoIt( const G4Track& track,
                                                   const G4Step& step)
{
// Rotate spin...
  DoRotation(track, step);

  return &fParticleChange ;
}

G4VParticleChange* neutralSpinRotation::AtRestDoIt( const G4Track& track,
                                                   const G4Step& step)
{
// Rotate spin...
  DoRotation(track, step);

  return &fParticleChange ;
}


void neutralSpinRotation::DoRotation( const G4Track& track, const G4Step& step)
{

  fParticleChange.Initialize(track);

  G4ThreeVector spin = track.GetPolarization();

  G4ThreeVector dl = step.GetDeltaPosition();
  G4double dt = step.GetDeltaTime();

  G4double t1 = step.GetPreStepPoint()->GetGlobalTime();
  G4ThreeVector p1 = step.GetPreStepPoint()->GetPosition();

// G4cout << "SPIN(" << spin << ", " << t1/ns << ", " << p1/cm << ", " << dt/ns << ", " << dl/cm << ")" << G4endl;

  fBlochEq->EvolveSpin(spin, step);

  fParticleChange.ProposePolarization(spin);

}


