
#ifndef diffusionBoundaryProcess_h
#define diffusionBoundaryProcess_h 1

/////////////
// Includes
/////////////

#include "globals.hh"
#include "templates.hh"
#include "geomdefs.hh"
#include "G4Step.hh"
#include "G4VDiscreteProcess.hh"
#include "G4DynamicParticle.hh"
#include "G4Material.hh"
#include "G4TransportationManager.hh"

#include "TH1.h"

// Class Description:
// Discrete Process -- reflection/refraction at optical interfaces.
// Class inherits publicly from G4VDiscreteProcess.                  
// Class Description - End:             

/////////////////////
// Class Definition
/////////////////////

enum diffusionBoundaryProcessStatus {  Undefined, SpikeReflection, SpecularReflection,
                                  DiffuseReflection, Absorption, NotAtBoundary,
                                  SameMaterial, StepTooSmall, Evaporation, Condensation };

class diffusionBoundaryProcess : public G4VDiscreteProcess 
{

private:

        //////////////
        // Operators
        //////////////

        // diffusionBoundaryProcess& operator=(const diffusionBoundaryProcess &right);

        // diffusionBoundaryProcess(const diffusionBoundaryProcess &right);

public: // Without description

        ////////////////////////////////
        // Constructors and Destructor
        ////////////////////////////////

        diffusionBoundaryProcess(const G4String& processName = "DiffusionBoundary");

	~diffusionBoundaryProcess();

        void SetEvaporationProb(G4double prob) { alpha_lv = prob; }
        // in collision with liquid-vapor or liquid-vacuum surface, the probability
        // that the particle will traverse the surface (leave the liquid).

        void SetCondensationProb(G4double prob) { alpha_vl = prob; }
        // in collision with vapor-liquid or vacuum-liquid surface, the probability
        // that the particle will traverse the surface (enter the liquid).

        void SetTypeOfWallBounce(diffusionBoundaryProcessStatus status);
        diffusionBoundaryProcessStatus GetTypeOfWallBounce() const;

	////////////
	// Methods
        ////////////

public: // With description

        G4bool IsApplicable(const G4ParticleDefinition& aParticleType);
        // Returns true -> 'is applicable' only for an optical photon.

	G4double GetMeanFreePath(const G4Track& ,
				 G4double ,
				 G4ForceCondition* condition);
        // Returns infinity; i. e. the process does not limit the step,
        // but sets the 'Forced' condition for the DoIt to be invoked at
        // every step. However, only at a boundary will any action be
        // taken. 

        G4double GetEvaporationProb() { return alpha_lv; }
        G4double GetCondensationProb() { return alpha_vl; }

	G4VParticleChange* PostStepDoIt(const G4Track& aTrack,
				       const G4Step&  aStep);
        // This is the method implementing boundary processes.

        diffusionBoundaryProcessStatus GetStatus() const;
        // Returns the current status.

private:

	void G4Swap(G4double* a, G4double* b) const;
	void G4Swap(G4Material* a, G4Material* b) const;
	void G4VectorSwap(G4ThreeVector* vec1, G4ThreeVector* vec2) const;

	void DoSpecularReflection();
	void DoDiffuseReflection();
	void DoIsotropicReflection();

private:

	G4double theAbsMomentum;

	G4ThreeVector OldMomentum;
	G4ThreeVector OldPolarization;

	G4ThreeVector NewMomentum;
	G4ThreeVector NewPolarization;
        G4RotationMatrix fRotation;

	G4ThreeVector theGlobalNormal;
	G4ThreeVector theFacetNormal;

	G4Material* Material1;
	G4Material* Material2;

	diffusionBoundaryProcessStatus theStatus;
	diffusionBoundaryProcessStatus fTypeOfWallBounce;

        G4double kCarTolerance;

        G4double alpha_lv; // probability of liquid-vapor boundary traversal
        G4double alpha_vl; // probability of vapor-liquid boundary traversal

        TH1 *hWallBounceLiquid;
        TH1 *hWallBounceVapor;
        TH1 *hLiquidVaporBounce;
        TH1 *hEvaporation;
        TH1 *hVaporLiquidBounce;
        TH1 *hCondensation;

};

////////////////////
// Inline methods
////////////////////

inline
void diffusionBoundaryProcess::SetTypeOfWallBounce(diffusionBoundaryProcessStatus status)
{
  if(status == DiffuseReflection || status == SpecularReflection) {
    fTypeOfWallBounce = status;
  } else {
    G4cout << "diffusionBoundaryProcess error: attempt to set invalid type of wall bounce"
           << G4endl;
  }
}

inline
diffusionBoundaryProcessStatus diffusionBoundaryProcess::GetTypeOfWallBounce() const
{
   return fTypeOfWallBounce;
}

inline
void diffusionBoundaryProcess::G4Swap(G4double* a, G4double* b) const
{
	// swaps the contents of the objects pointed 
	// to by 'a' and 'b'!

  G4double temp;

  temp = *a;
  *a = *b;
  *b = temp;
}

inline
void diffusionBoundaryProcess::G4Swap(G4Material* a, G4Material* b) const
{
	// ONLY swaps the pointers; i.e. what used to be pointed
	// to by 'a' is now pointed to by 'b' and vice versa!

   G4Material* temp = a;

   a = b;
   b = temp;
}

inline
void diffusionBoundaryProcess::G4VectorSwap(G4ThreeVector* vec1,
				       G4ThreeVector* vec2) const
{
        // swaps the contents of the objects pointed
        // to by 'vec1' and 'vec2'!

  G4ThreeVector temp;

  temp = *vec1;
  *vec1 = *vec2;
  *vec2 = temp;
}

inline
G4bool diffusionBoundaryProcess::IsApplicable(const G4ParticleDefinition& 
					               aParticleType)
{
   return true;
}


inline
diffusionBoundaryProcessStatus diffusionBoundaryProcess::GetStatus() const
{
   return theStatus;
}


inline
void diffusionBoundaryProcess::DoSpecularReflection()
{
  theFacetNormal = theGlobalNormal;
  G4double PdotN = OldMomentum * theFacetNormal;
  NewMomentum = OldMomentum - (2.*PdotN)*theFacetNormal;
  NewMomentum = NewMomentum.unit();
}

inline
void diffusionBoundaryProcess::DoDiffuseReflection()
{
  // scattering kernel: R(v' --> v) = 1/(2*pi) |v.n|, where v = v'.
  // P(theta) = sin(2*theta)/2,  0 < theta < pi/2
  G4double PthetaX2 = 2*G4UniformRand() - 1; // 2*P(theta)
  G4double theta = pi/4 + 0.5*std::asin(PthetaX2);
  G4double phi = 2*pi*G4UniformRand();

  // choose new momentum as if z-axis is aligned with theFacetNormal
  G4double sth = std::sin(theta);
  G4double cth = std::cos(theta);
  NewMomentum.setX(sth*std::cos(phi));
  NewMomentum.setY(sth*std::sin(phi));
  NewMomentum.setZ(cth);
  // rotate NewMomentum to align z-axis with theFacetNormal
  NewMomentum.rotateUz(theFacetNormal);

}

#endif /* diffusionBoundaryProcess_h */
