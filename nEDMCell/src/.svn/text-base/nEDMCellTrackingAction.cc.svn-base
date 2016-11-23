#include "nEDMCellTrackingAction.hh"

nEDMCellTrackingAction::nEDMCellTrackingAction()
{
}

nEDMCellTrackingAction::~nEDMCellTrackingAction()
{
}

void nEDMCellTrackingAction::PreUserTrackingAction(const G4Track* ptrack)
{
//  G4cout << "Start point: t = " << ptrack->GetGlobalTime()/ms << " ms, "
//         << ptrack->GetPosition() << G4endl;
}

void nEDMCellTrackingAction::PostUserTrackingAction(const G4Track* ptrack)
{
  G4cout << "End point: t = " << ptrack->GetGlobalTime()/s << " s, "
         << ptrack->GetPosition()/cm << " cm" << G4endl;
  G4cout << "Track length = " << ptrack->GetTrackLength()/cm << " cm" << G4endl;
  G4cout << "avg. velocity = " << ptrack->GetTrackLength()/ptrack->GetGlobalTime()/(cm/s)
         << " cm/s" << G4endl;
}

