#ifndef periodicStepping_hh
#define periodicStepping_hh 1

#include "G4VProcess.hh"

#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleChange.hh"
#include "TH1.h"
#include "TTree.h"
#include "TAxis.h"

#define XYZHIST 1
#if XYZHIST
#include "TH3.h"
#endif

class periodicStepping : public G4VProcess 
{
  // Concrete class that does the geometrical transport 

  public:  // with description

     periodicStepping(G4int verbosityLevel= 1);
     ~periodicStepping(); 


     G4double GetTimeInterval() { return fTimeInterval; }
     void SetTimeInterval(G4double dt) { fTimeInterval = dt; }

     static const G4double kMaxSimulationSeconds; // max simulated time in seconds

     void SetPrintInterval(G4int ncalls) { fPrintInterval = ncalls; }

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

     inline void   SetVerboseLevel( G4int lev ) { fVerboseLevel = lev; }
     inline G4int  GetVerboseLevel() const { return fVerboseLevel; }
       // Level of warnings regarding eg energy conservation
       // in field integration.

     // SetTimeInterval(...) should be called before creating histograms in order
     // to have the correct bin widths.
     void CreateHistograms(G4bool makeTree = false);

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

     G4int fPrintInterval;
     void FillHists( const G4Track& track, const G4Step& step);
     TAxis *faxis;
     TH1 *hSpinX;
     TH1 *hSpinY;
     TH1 *hSpinZ;
     TH1 *hPeriodicDoItCalls;

     TH1 *htempx;
     TH1 *htempy;
     TH1 *htempz;
#if XYZHIST
     TH3 *htempxyz;
#endif

     // ROOT tree
     TTree *tree;
     Double_t ft;   // time (in s)
     Float_t fx;   // x position (in mm)
     Float_t fy;   // y position (in mm)
     Float_t fz;   // z position (in mm)
     Float_t fSx;  // x-component of spin
     Float_t fSy;  // y-component of spin
     Float_t fSz;  // z-component of spin
};

#endif  
