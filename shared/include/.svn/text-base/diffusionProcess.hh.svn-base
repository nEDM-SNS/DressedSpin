
#ifndef diffusionProcess_h
#define diffusionProcess_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4VDiscreteProcess.hh"
#include "G4ParticleChange.hh"
//  #include "dressedSpinParameters.hh"

#include "TH1.h"

class dressedSpinParameters;

class diffusionProcess : public G4VDiscreteProcess 
{
 // Class Description
  //  This class is a decay process

  public:
    //  Constructors 
    diffusionProcess(const G4String& processName ="Diffusion");

    //  Destructor
    virtual ~diffusionProcess();

    void SetMeanFreePath(G4double lambda) { fMeanFreePath = lambda; }

    void SetNormalFlowFlag(G4bool flag = true) { fNormalFlowFlag = flag; }
    void SetNormalFlowVelocity(G4double v) { fNormalFlowVelocity = v; }
    G4bool GetNormalFlowFlag() { return fNormalFlowFlag; }
    G4double GetNormalFlowVelocity() { return fNormalFlowVelocity; }

    void SetDiffusionParamObj(dressedSpinParameters* obj) { fDiffusionParamObj = obj; }

  private:
    //  copy constructor
      diffusionProcess(const diffusionProcess &right);

    //  Assignment Operation (generated)
      diffusionProcess & operator=(const diffusionProcess &right);

    dressedSpinParameters* fDiffusionParamObj;

    TH1 *htest;

  public: //With Description
     // diffusionProcess Process has
     // PostStepDoIt (mean free path interval)
     virtual G4VParticleChange *PostStepDoIt(
			     const G4Track& aTrack,
                             const G4Step& aStep
                            );


     virtual void BuildPhysicsTable(const G4ParticleDefinition&); 
     // In diffusionProcess, thePhysicsTable may be used in the
     // future to store energy- or temperature-dependent mean free paths

    virtual G4bool IsApplicable(const G4ParticleDefinition&);
    // returns "true" if the decay process can be applied to
    // the particle type. 

  protected: // With Description
    virtual G4VParticleChange* DiffuseIt(
                             const G4Track& aTrack,
                             const G4Step& aStep
                            );
    // The DiffuseIt() methode returns by pointer a particle-change object.


  protected: // With Description
    // GetMeanFreePath returns the appropriate mean free path
    // GetMeanLifeTime returns a large number (stable particle)
    virtual G4double GetMeanFreePath(const G4Track& aTrack,
                              G4double   previousStepSize,
                              G4ForceCondition* condition
                             );

    virtual G4double GetMeanLifeTime(const G4Track& aTrack,
                              G4ForceCondition* condition
                            );

   public: //With Description
     virtual void StartTracking(G4Track*);
     virtual void EndTracking();
      // inform Start/End of tracking for each track to the physics process 

  public:
     void  SetVerboseLevel(G4int value);
     G4int GetVerboseLevel() const;


  protected:
     G4int verboseLevel;
     // controle flag for output message
     //  0: Silent
     //  1: Warning message
     //  2: More

  protected:
    // HighestValue.
    const G4double HighestValue;
 
    // Mean free path
    G4double fMeanFreePath;

    G4ThreeVector NewMomentum;

    G4bool fNormalFlowFlag;
    G4double fNormalFlowVelocity;

};

inline
 void  diffusionProcess::SetVerboseLevel(G4int value){ verboseLevel = value; }

inline
 G4int diffusionProcess::GetVerboseLevel() const { return verboseLevel; }

inline  
  G4VParticleChange* diffusionProcess::PostStepDoIt(
			     const G4Track& aTrack,
			     const G4Step&  aStep
			    )
{
  return DiffuseIt(aTrack, aStep);
}

#if 0
inline  
  G4VParticleChange* diffusionProcess::AlongStepDoIt(
			     const G4Track& aTrack,
			     const G4Step&  aStep
			    )
{
  return 0;
}
#endif


#endif


