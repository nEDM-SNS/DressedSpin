
#ifndef beamExptBoundaryProcess_h
#define beamExptBoundaryProcess_h 1

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

enum beamExptBoundaryProcessStatus {  Undefined, NotAtBoundary, StepTooSmall,
                                  SameMaterial, atAnalyzer};

class beamExptBoundaryProcess : public G4VDiscreteProcess 
{

private:

        //////////////
        // Operators
        //////////////

        // beamExptBoundaryProcess& operator=(const beamExptBoundaryProcess &right);

        // beamExptBoundaryProcess(const beamExptBoundaryProcess &right);

public: // Without description

        ////////////////////////////////
        // Constructors and Destructor
        ////////////////////////////////

        beamExptBoundaryProcess(const G4String& processName = "DiffusionBoundary");

	~beamExptBoundaryProcess();

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

	G4VParticleChange* PostStepDoIt(const G4Track& aTrack,
				       const G4Step&  aStep);
        // This is the method implementing boundary processes.

        beamExptBoundaryProcessStatus GetStatus() const;
        // Returns the current status.

private:

	G4double theAbsMomentum;


	G4Material* Material1;
	G4Material* Material2;

	beamExptBoundaryProcessStatus theStatus;

        G4double kCarTolerance;

};

////////////////////
// Inline methods
////////////////////

inline
G4bool beamExptBoundaryProcess::IsApplicable(const G4ParticleDefinition& 
					               aParticleType)
{
   return true;
}


inline
beamExptBoundaryProcessStatus beamExptBoundaryProcess::GetStatus() const
{
   return theStatus;
}



#endif /* beamExptBoundaryProcess_h */
