
#include "G4ios.hh"
#include "diffusionBoundaryProcess.hh"
#include "G4GeometryTolerance.hh"

#include "periodicStepping.hh"

#include "dressedSpin_utils.hh"


/////////////////////////
// Class Implementation
/////////////////////////

        /////////////////
        // Constructors
        /////////////////

diffusionBoundaryProcess::diffusionBoundaryProcess(const G4String& processName)
             : G4VDiscreteProcess(processName, fUserDefined)
{
  if ( verboseLevel > 0) {
    G4cout << GetProcessName() << " is created " << G4endl;
  }

  theStatus = Undefined;
  fTypeOfWallBounce = DiffuseReflection;

  kCarTolerance = G4GeometryTolerance::GetInstance()->GetSurfaceTolerance();

  pParticleChange = &aParticleChange;

  alpha_vl = 1.0;
  alpha_lv = 0.0;

  hWallBounceLiquid = new TH1D("hWallBounceLiquid","Bounces off wall from liquid",
            10000, 0., periodicStepping::kMaxSimulationSeconds);
  hWallBounceVapor = new TH1D("hWallBounceVapor","Bounces off wall from vapor",
            10000, 0., periodicStepping::kMaxSimulationSeconds);
  hLiquidVaporBounce = new TH1D("hLiquidVaporBounce","Reflection off surface from liquid side",
            10000, 0., periodicStepping::kMaxSimulationSeconds);
  hEvaporation = new TH1D("hEvaporation","Transmission through surface from liquid side",
            10000, 0., periodicStepping::kMaxSimulationSeconds);
  hVaporLiquidBounce = new TH1D("hVaporLiquidBounce","Reflection off surface from vapor side",
            10000, 0., periodicStepping::kMaxSimulationSeconds);
  hCondensation = new TH1D("hCondensation","Transmission through surface from vapor side",
            10000, 0., periodicStepping::kMaxSimulationSeconds);

}

diffusionBoundaryProcess::~diffusionBoundaryProcess(){}


inline
void diffusionBoundaryProcess::DoIsotropicReflection()
{
  // This may be an unphysical boundary condition.

  G4double pdotn = 0;
  G4int itry;
  do {
    NewMomentum = isotropicRand();
    pdotn = NewMomentum*theFacetNormal;
    // random bounce toward interior
    if(pdotn < 0.0) {
      NewMomentum = -NewMomentum;
      pdotn *= -1.;
    }
    ++itry;
  } while(pdotn < 0.01); // reject bounces nearly parallel to the surface
}




G4VParticleChange*
diffusionBoundaryProcess::PostStepDoIt(const G4Track& aTrack, const G4Step& aStep)
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
//  G4cout << "Material1: " << Material1->GetName()
//         << ", Material2: " << Material2->GetName() << G4endl;
  if((Material1 == Material2) ||  // same G4Material object assigned to these volumes
     (strcmp(Material1->GetName(),Material2->GetName()) == 0)) {  // OR they have the same name
    theStatus = SameMaterial;                              // this is not a boundary
    return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
  } else if((strcmp(Material1->GetName(),"LHe4") == 0) &&
            ((strcmp(Material2->GetName(),"He3Gas") == 0) || 
             (Material2->GetDensity() < 2*universe_mean_density)) ) {  // liquid-(vapor/vacuum) surface
    if(G4UniformRand() < alpha_lv) { // probability for particle to exit liquid
      theStatus = Evaporation;
    } else {
      theStatus = SpikeReflection;
    }
  } else if(((strcmp(Material1->GetName(),"He3Gas") == 0) ||
             (Material1->GetDensity() < 2*universe_mean_density)) &&
            (strcmp(Material2->GetName(),"LHe4") == 0)) {  // (vapor/vacuum)-liquid surface
    if(G4UniformRand() < alpha_vl) { // probability for particle to enter liquid
      theStatus = Condensation;
    } else {
      theStatus = SpikeReflection;
    }
  } else { // default behavior for interface between different materials
//    theStatus = DiffuseReflection; // reflection from rough wall
    theStatus = GetTypeOfWallBounce();
  }


  const G4DynamicParticle* aParticle = aTrack.GetDynamicParticle();
  theAbsMomentum = aParticle->GetTotalMomentum();
  OldMomentum = aParticle->GetMomentumDirection();

  if(theStatus == DiffuseReflection || theStatus == SpecularReflection) {
    if(strcmp(Material1->GetName(),"LHe4") == 0) {
      hWallBounceLiquid->Fill(pPostStepPoint->GetGlobalTime()/s);
    } else {
      hWallBounceVapor->Fill(pPostStepPoint->GetGlobalTime()/s);
    }
  } else if(theStatus == SpikeReflection) {
    if(strcmp(Material1->GetName(),"LHe4") == 0) {
      hLiquidVaporBounce->Fill(pPostStepPoint->GetGlobalTime()/s);
    } else {
      hVaporLiquidBounce->Fill(pPostStepPoint->GetGlobalTime()/s);
    }
  } else if(theStatus == Evaporation) {
    hEvaporation->Fill(pPostStepPoint->GetGlobalTime()/s);
  } else if(theStatus == Condensation) {
    hCondensation->Fill(pPostStepPoint->GetGlobalTime()/s);
  }


  if ( verboseLevel > 0 ) {
    G4cout << " Particle at Boundary! " << G4endl;
    G4cout << " Old Momentum Direction: " << OldMomentum     << G4endl;
  }

  G4ThreeVector theGlobalPoint = pPostStepPoint->GetPosition();

  G4Navigator* theNavigator =
        G4TransportationManager::GetTransportationManager()->
               GetNavigatorForTracking();

  G4ThreeVector theLocalPoint = theNavigator->GetGlobalToLocalTransform().
				      TransformPoint(theGlobalPoint);
  G4ThreeVector theLocalNormal;	// Normal points back into volume

  G4bool valid;
  theLocalNormal = theNavigator->GetLocalExitNormal(&valid);

  if (valid) {
    theLocalNormal = -theLocalNormal;
  } else {
    G4cerr << " diffusionBoundaryProcess/PostStepDoIt(): "
           << " The Navigator reports that it returned an invalid normal" << G4endl;
  }

  theGlobalNormal = theNavigator->GetLocalToGlobalTransform().TransformAxis(theLocalNormal);
  if (OldMomentum * theGlobalNormal > 0.0) {
    theGlobalNormal = -theGlobalNormal;
  }

  // inward-pointing normal to surface
  theFacetNormal = theGlobalNormal;

  if(theStatus == SpecularReflection || theStatus == SpikeReflection) {
    DoSpecularReflection();
  } else if(theStatus == Evaporation) {
    NewMomentum = OldMomentum;
    G4double K = aParticle->GetKineticEnergy();
    aParticleChange.ProposeEnergy(2.4*K); // (K.E.) particle speeds up (m_3 = m_eff/2.4)
    aParticleChange.ProposeMomentumDirection(NewMomentum);
  } else if(theStatus == Condensation) {
    NewMomentum = OldMomentum;
    G4double K = aParticle->GetKineticEnergy();
    aParticleChange.ProposeEnergy(K/2.4); // (K.E.) particle slows (m_eff = 2.4 m_3)
    aParticleChange.ProposeMomentumDirection(NewMomentum);
  } else if(theStatus == DiffuseReflection) {
    DoDiffuseReflection();
  } else {
    G4cout << "diffusionBoundaryProcess: no plan for this interface" << G4endl;
    G4cout << "     Material1 = " << Material1->GetName()
           << ", Material2 = " << Material2->GetName() << G4endl;
  }

  if ( verboseLevel > 0) {
    G4cout << " New Momentum Direction: "
           << NewMomentum << G4endl;
    if ( theStatus == SpikeReflection )
          G4cout << " *** SpikeReflection *** " << G4endl;
    if ( theStatus == DiffuseReflection )
          G4cout << " *** DiffuseReflection *** " << G4endl;
    if ( theStatus == Absorption )
          G4cout << " *** Absorption *** " << G4endl;
    if ( theStatus == NotAtBoundary )
          G4cout << " *** NotAtBoundary *** " << G4endl;
    if ( theStatus == SameMaterial )
          G4cout << " *** SameMaterial *** " << G4endl;
    if ( theStatus == StepTooSmall )
          G4cout << " *** StepTooSmall *** " << G4endl;
  }

//  pParticleChange->ProposeMomentumDirection(NewMomentum);
  aParticleChange.ProposeMomentumDirection(NewMomentum);

  return G4VDiscreteProcess::PostStepDoIt(aTrack, aStep);
}



// GetMeanFreePath
// ---------------
//
G4double diffusionBoundaryProcess::GetMeanFreePath(const G4Track& ,
                                              G4double ,
                                              G4ForceCondition* condition)
{
	*condition = Forced;

	return DBL_MAX;
}

