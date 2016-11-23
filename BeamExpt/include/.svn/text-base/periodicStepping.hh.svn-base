#ifndef periodicStepping_hh
#define periodicStepping_hh 1

#include "G4VProcess.hh"

#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleChange.hh"
#include "TH1.h"

class periodicStepping : public G4VProcess 
{
  // Concrete class that does the geometrical transport 

  public:  // with description

     periodicStepping( G4int verbosityLevel= 1);
     ~periodicStepping(); 


     G4double GetTimeInterval();
     void SetTimeInterval(G4double dt);

     static const G4double kMaxSimulationSeconds; // max simulated time in seconds
     static const G4double kPrintInterval; // interval in seconds to display status message

     G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& track,
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
                             const G4Step&  step
                            ) { return 0; }

     G4VParticleChange* AtRestDoIt(
                             const G4Track& track,
                             const G4Step& step
                            );

     G4double AtRestGetPhysicalInteractionLength(
                             const G4Track& track,
                             G4ForceCondition* pForceCond
                            );

     void GetLengthTime(const G4Track& track, G4double& length, G4double& time);

     inline void   SetVerboseLevel( G4int verboseLevel );
     inline G4int  GetVerboseLevel() const;
       // Level of warnings regarding eg energy conservation
       // in field integration.


  private:

     G4TouchableHandle    fCurrentTouchableHandle;

     G4ParticleChange fParticleChange;
       // New ParticleChange

  // Verbosity 
     G4int    fVerboseLevel;
       // Verbosity level for warnings
       // eg about energy non-conservation in magnetic field.

     G4double fTimeInterval;
     G4double fTimeMin;
     G4double fTimeMax;

     void FillHists( const G4Track& track, const G4Step& step);
     TH1 *hSpinX;
     TH1 *hSpinY;
     TH1 *hSpinZ;
     TH1 *hPeriodicDoItCalls;
};

inline G4double periodicStepping::GetTimeInterval()
{
  return fTimeInterval;
}

inline void periodicStepping::SetTimeInterval(G4double dt)
{
  fTimeInterval = dt;
}

inline void periodicStepping::SetVerboseLevel( G4int verboseLev )
{
  fVerboseLevel= verboseLev;
}

inline G4int periodicStepping::GetVerboseLevel( ) const
{
  return fVerboseLevel;
}




#endif  
