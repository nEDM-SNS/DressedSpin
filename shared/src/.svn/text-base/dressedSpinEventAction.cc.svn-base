#include "dressedSpinEventAction.hh"
#include "dressedSpinPhysicsList.hh"

#include "G4RunManager.hh"

dressedSpinEventAction::dressedSpinEventAction()
{
  hEventStats = new TH1D("hEventStats","Event Statistics",10,0.5,10.5);
  hEventStats->GetXaxis()->SetBinLabel(1,"Events Begun");
  hEventStats->GetXaxis()->SetBinLabel(2,"Events Ended");
}

dressedSpinEventAction::~dressedSpinEventAction()
{
}

void dressedSpinEventAction::BeginOfEventAction(const G4Event* pevent)
{
  hEventStats->Fill(1.);
}

void dressedSpinEventAction::EndOfEventAction(const G4Event* pevent)
{
  hEventStats->Fill(2.);
}

