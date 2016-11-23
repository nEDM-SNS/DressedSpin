#ifndef nEDMCellTrackingAction_hh
#define nEDMCellTrackingAction_hh 1

#include "G4UserTrackingAction.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4Track.hh"

class nEDMCellTrackingAction : public G4UserTrackingAction
{
  public:
  nEDMCellTrackingAction();
  virtual ~nEDMCellTrackingAction();

  void PreUserTrackingAction(const G4Track* ptrack);
  void PostUserTrackingAction(const G4Track* ptrack);

  private:

};

#endif

