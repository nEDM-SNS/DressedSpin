#ifndef neutralSpinRotation_hh
#define neutralSpinRotation_hh 1

#include "G4VProcess.hh"

#include "G4Navigator.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleChange.hh"

#include "BlochEq.hh"

class neutralSpinRotation : public G4VProcess 
{
  // Concrete class that does the geometrical transport 

  public:  // with description

     neutralSpinRotation( G4int verbosityLevel= 1);
     ~neutralSpinRotation(); 

     void DoRotation(const G4Track& track, const G4Step& step);

     G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& ,
                             G4double   previousStepSize,
                             G4ForceCondition* pForceCond
                            );

     G4VParticleChange* PostStepDoIt(
                             const G4Track& track,
                             const G4Step& stepData
                            );

     G4double      AlongStepGetPhysicalInteractionLength(
                             const G4Track& track,
                                   G4double  previousStepSize,
                                   G4double  currentMinimumStep, 
                                   G4double& currentSafety,
                                   G4GPILSelection* selection
                            ) { return -1.0; }

     G4VParticleChange* AlongStepDoIt(
                             const G4Track& track,
                             const G4Step&  stepData
                            ) { return 0; }

     G4VParticleChange* AtRestDoIt(
                             const G4Track& ,
                             const G4Step&
                            );

     G4double AtRestGetPhysicalInteractionLength(
                             const G4Track& ,
                             G4ForceCondition* pForceCond
                            );


     inline void   SetVerboseLevel( G4int verboseLevel );
     inline G4int  GetVerboseLevel() const;
       // Level of warnings regarding eg energy conservation
       // in field integration.


     BlochEq* GetBlochEqObj() { return fBlochEq; }

  private:

     G4TouchableHandle    fCurrentTouchableHandle;

     G4ParticleChange fParticleChange;
       // New ParticleChange

     BlochEq* fBlochEq;

  // Verbosity 
     G4int    fVerboseLevel;
       // Verbosity level for warnings
       // eg about energy non-conservation in magnetic field.
};


inline void neutralSpinRotation::SetVerboseLevel( G4int verboseLev )
{
  fVerboseLevel= verboseLev;
}

inline G4int neutralSpinRotation::GetVerboseLevel( ) const
{
  return fVerboseLevel;
}




#endif  
