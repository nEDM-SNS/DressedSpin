#include "UIUCCryoSteppingAction.hh"
#include "G4Navigator.hh"
#include "G4TransportationManager.hh"

#include "periodicStepping.hh"

UIUCCryoSteppingAction::UIUCCryoSteppingAction()
{
  hInCellLiq = new TH1D("hInCellLiq","Time (s) per interval particle is in liquid",
            10000, 0., periodicStepping::kMaxSimulationSeconds);
  hInCellVapor = new TH1D("hInCellVapor","Time (s) per interval particle is in vapor",
            10000, 0., periodicStepping::kMaxSimulationSeconds);

}

UIUCCryoSteppingAction::~UIUCCryoSteppingAction()
{
}


void UIUCCryoSteppingAction::UserSteppingAction(const G4Step* pstep)
{
  G4StepPoint *prestep = pstep->GetPreStepPoint();
  G4StepPoint *poststep = pstep->GetPostStepPoint();

  G4double t1_s = prestep->GetGlobalTime()/s;
  G4double t2_s = poststep->GetGlobalTime()/s;

  TH1 *hcell;
  G4Material* mat = prestep->GetMaterial();
  if(strcmp(mat->GetName(),"LHe4") == 0) {
    hcell = hInCellLiq;
  } else {
    hcell = hInCellVapor;
  }

  TAxis *axis = hcell->GetXaxis();
  int bin1 = axis->FindBin(t1_s);
  int bin2 = axis->FindBin(t2_s);
  double prev_val;
  if(bin1 == bin2) {
    prev_val = hcell->GetBinContent(bin1);
    hcell->SetBinContent(bin1, prev_val + t2_s - t1_s);
  } else {
    prev_val = hcell->GetBinContent(bin1);
    hcell->SetBinContent(bin1, prev_val + axis->GetBinUpEdge(bin1) - t1_s);
    prev_val = hcell->GetBinContent(bin2);
    hcell->SetBinContent(bin2, prev_val + t2_s - axis->GetBinLowEdge(bin2));
    for(int bin=bin1+1; bin < bin2; bin++) {
      prev_val = hcell->GetBinContent(bin);
      hcell->SetBinContent(bin, prev_val + axis->GetBinWidth(bin));
    }
  }

}

