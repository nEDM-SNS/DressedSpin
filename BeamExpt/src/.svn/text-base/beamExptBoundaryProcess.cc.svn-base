
#include "G4ios.hh"
#include "beamExptBoundaryProcess.hh"
#include "G4GeometryTolerance.hh"

#include "periodicStepping.hh"

/////////////////////////
// Class Implementation
/////////////////////////

        /////////////////
        // Constructors
        /////////////////

beamExptBoundaryProcess::beamExptBoundaryProcess(const G4String& processName)
             : G4VDiscreteProcess(processName, fUserDefined)
{
  if ( verboseLevel > 0) {
    G4cout << GetProcessName() << " is created " << G4endl;
  }

  theStatus = Undefined;
                                                                                
  kCarTolerance = G4GeometryTolerance::GetInstance()->GetSurfaceTolerance();

  pParticleChange = &aParticleChange;

}

beamExptBoundaryProcess::~beamExptBoundaryProcess(){}

G4VParticleChange*
beamExptBoundaryProcess::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
{
  theStatus = Undefined;

  pParticleChange->Initialize(aTrack);

  G4StepPoint* pPreStepPoint  = aStep.GetPreStepPoint();
  G4StepPoint* pPostStepPoint = aStep.GetPostStepPoint();

  if (pPostStepPoint->GetStepStatus() != fGeomBoundary){
    theStatus = NotAtBoundary;
    return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
  }

  if (aTrack.GetStepLength()<=kCarTolerance/2){
    theStatus = StepTooSmall;
    return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
  }

  Material1 = pPreStepPoint  -> GetMaterial();
  Material2 = pPostStepPoint -> GetMaterial();

  // check if the boundary is between identical materials
  // (in which case we do nothing)
  if((Material1 == Material2) ||  // same G4Material object assigned to these volumes
     (strcmp(Material1->GetName(),Material2->GetName()) == 0)) {  // OR they have the same name
    theStatus = SameMaterial;                              // this is not a boundary
    return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);

  // check if the boundary is between vacuum (beam pipe) and "Analyzer"
  // (in which case we stop the event and save the spin components)
  } else if((Material1->GetDensity() < 2*universe_mean_density) &&
            (strcmp(Material2->GetName(),"Ana") == 0)) {
    theStatus = atAnalyzer;
    pParticleChange->ProposeTrackStatus(fStopAndKill);
    return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);

  // default behavior (do nothing)
  } else {
    return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
  }

}



// GetMeanFreePath
// ---------------
//
G4double beamExptBoundaryProcess::GetMeanFreePath(const G4Track& ,
                                              G4double ,
                                              G4ForceCondition* condition)
{
	*condition = Forced;

	return DBL_MAX;
}

