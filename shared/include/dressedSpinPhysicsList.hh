
#ifndef dressedSpinPhysicsList_h
#define dressedSpinPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "diffusionProcess.hh"
#include "diffusionBoundaryProcess.hh"
#include "periodicStepping.hh"
#include "neutralSpinRotation.hh"
#include "BlochEq.hh"
#include "globals.hh"

class dressedSpinPhysicsList: public G4VUserPhysicsList
{
  public:
    dressedSpinPhysicsList();
    ~dressedSpinPhysicsList();

    diffusionProcess* GetDiffusionProcess() { return fDiffusionProcess; }
    diffusionBoundaryProcess* GetDiffusionBoundaryProcess() { return fDiffusionBoundaryProcess; }
    neutralSpinRotation* GetNeutralSpinRotation() { return fNeutralSpinRotation; }
    periodicStepping* GetPeriodicStepping() { return fPeriodicStepping; }

  protected:
    // Construct particle and physics process
    virtual void ConstructParticle();
    virtual void ConstructProcess();
    void SetCuts();

    diffusionProcess* fDiffusionProcess;
    diffusionBoundaryProcess* fDiffusionBoundaryProcess;
    periodicStepping* fPeriodicStepping;
    neutralSpinRotation* fNeutralSpinRotation;
    BlochEq* fBlochEq; // used in neutralSpinRotation

};

#endif

