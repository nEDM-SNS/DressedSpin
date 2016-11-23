#include "beamExptTrackingAction.hh"

beamExptTrackingAction::beamExptTrackingAction()
{
  hDetectedSpin = new TH1D("hDetectedSpin","Spin components at detector",
            3, 0.5, 3.5);
  hDetectedSpin->GetXaxis()->SetBinLabel(1,"S_{x}");
  hDetectedSpin->GetXaxis()->SetBinLabel(2,"S_{y}");
  hDetectedSpin->GetXaxis()->SetBinLabel(3,"S_{z}");
}

beamExptTrackingAction::~beamExptTrackingAction()
{
}

void beamExptTrackingAction::PreUserTrackingAction(const G4Track* ptrack)
{
  G4cout << "Start point: t = " << ptrack->GetGlobalTime()/ms << " ms, "
         << ptrack->GetPosition() << G4endl;
  G4cout << "Start polarization: " << ptrack->GetPolarization() << G4endl;
}

void beamExptTrackingAction::PostUserTrackingAction(const G4Track* ptrack)
{
  G4cout << "End point: t = " << ptrack->GetGlobalTime()/ms << " ms, "
         << ptrack->GetPosition() << G4endl;
  G4cout << "End polarization: " << ptrack->GetPolarization() << G4endl;
  G4ThreeVector spin = ptrack->GetPolarization();
  // save spin components for this event (overwrites prev values)
  hDetectedSpin->SetBinContent(1, spin.x());
  hDetectedSpin->SetBinContent(2, spin.y());
  hDetectedSpin->SetBinContent(3, spin.z());

}

