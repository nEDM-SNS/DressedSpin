#ifndef beamExptEventAction_hh
#define beamExptEventAction_hh 1

#include "G4UserEventAction.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4Event.hh"

#include "TH1.h"

class beamExptEventAction : public G4UserEventAction
{
  public:
  beamExptEventAction();
  virtual ~beamExptEventAction();

  void BeginOfEventAction(const G4Event* anEvent);
  void EndOfEventAction(const G4Event* anEvent);

  private:
  TH1 *hEventStats;

};

#endif

