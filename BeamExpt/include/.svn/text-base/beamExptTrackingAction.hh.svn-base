#ifndef beamExptTrackingAction_hh
#define beamExptTrackingAction_hh 1

#include "G4UserTrackingAction.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4Track.hh"

#include "TH1.h"

class beamExptTrackingAction : public G4UserTrackingAction
{
  public:
  beamExptTrackingAction();
  virtual ~beamExptTrackingAction();

  void PreUserTrackingAction(const G4Track* ptrack);
  void PostUserTrackingAction(const G4Track* ptrack);

  private:

  TH1* hDetectedSpin;

};

#endif

