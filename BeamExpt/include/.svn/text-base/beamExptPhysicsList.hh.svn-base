
#ifndef beamExptPhysicsList_h
#define beamExptPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "beamExptBoundaryProcess.hh"
#include "neutralSpinRotation.hh"
#include "periodicStepping.hh"
#include "globals.hh"

class beamExptPhysicsList: public G4VUserPhysicsList
{
  public:
    beamExptPhysicsList();
    ~beamExptPhysicsList();

    beamExptBoundaryProcess* GetBeamExptBoundaryProcess() { return fBeamExptBoundaryProcess; }
    neutralSpinRotation* GetNeutralSpinRotation() { return fNeutralSpinRotation; }
    periodicStepping* GetPeriodicStepping() { return fPeriodicStepping; }

  protected:
    // Construct particle and physics process
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

    beamExptBoundaryProcess* fBeamExptBoundaryProcess;
    neutralSpinRotation* fNeutralSpinRotation;
    periodicStepping* fPeriodicStepping;

};

#endif


