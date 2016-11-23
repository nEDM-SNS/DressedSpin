#ifndef UIUCCryoSteppingAction_hh
#define UIUCCryoSteppingAction_hh 1

#include "G4UserSteppingAction.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4Step.hh"

#include "TH1.h"

class UIUCCryoSteppingAction : public G4UserSteppingAction
{
  public:
  UIUCCryoSteppingAction();
  virtual ~UIUCCryoSteppingAction();

  void UserSteppingAction(const G4Step* pstep);

  private:

  TH1 *hInCellLiq;
  TH1 *hInCellVapor;

};

#endif

