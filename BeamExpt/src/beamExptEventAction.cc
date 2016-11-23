#include "beamExptEventAction.hh"
#include "beamExptPhysicsList.hh"

#include "G4RunManager.hh"

beamExptEventAction::beamExptEventAction()
{
  hEventStats = new TH1D("hEventStats","Event Statistics",10,0.5,10.5);
  hEventStats->GetXaxis()->SetBinLabel(1,"Events Begun");
  hEventStats->GetXaxis()->SetBinLabel(2,"Events Ended");
}

beamExptEventAction::~beamExptEventAction()
{
}

void beamExptEventAction::BeginOfEventAction(const G4Event* pevent)
{
  hEventStats->Fill(1.);
}

void beamExptEventAction::EndOfEventAction(const G4Event* pevent)
{
  hEventStats->Fill(2.);
}

