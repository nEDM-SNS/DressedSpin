
#include "periodicStepping.hh"

const G4double periodicStepping::kMaxSimulationSeconds = 1.0;
const G4double periodicStepping::kPrintInterval = 1.0;

periodicStepping::periodicStepping( G4int verboseLevel )
  : G4VProcess( G4String("periodicStepping"), fUserDefined),
    fVerboseLevel( verboseLevel ), fTimeInterval(1e-6*s)
{
  static G4TouchableHandle nullTouchableHandle;  // Points to (G4VTouchable*) 0
  fCurrentTouchableHandle = nullTouchableHandle; 

  fTimeMin = 0.;
  fTimeMax = kMaxSimulationSeconds;
  // Choose histogram parameters such that the bin widths are
  // fTimeInterval/s.
  G4int nbins = int((fTimeMax - fTimeMin)/(fTimeInterval/s)) + 1;
  fTimeMax = fTimeMin + (nbins - 0.5)*fTimeInterval/s;
  fTimeMin -= 0.5*fTimeInterval/s;
  hSpinX = new TH1D("hSpinX","Spin x-component", nbins, fTimeMin, fTimeMax);
  hSpinX->GetXaxis()->SetTitle("Time (s)");
  hSpinY = new TH1D("hSpinY","Spin y-component", nbins, fTimeMin, fTimeMax);
  hSpinY->GetXaxis()->SetTitle("Time (s)");
  hSpinZ = new TH1D("hSpinZ","Spin z-component", nbins, fTimeMin, fTimeMax);
  hSpinZ->GetXaxis()->SetTitle("Time (s)");

  hPeriodicDoItCalls = new TH1D("hPeriodicDoItCalls","hPeriodicDoitCalls",
          nbins,fTimeMin,fTimeMax);
  hPeriodicDoItCalls->GetXaxis()->SetTitle("Time (s)");

}

periodicStepping::~periodicStepping()
{
}

void periodicStepping::GetLengthTime(const G4Track& track, G4double &length, G4double &time)
{
  int nperiod = int(track.GetGlobalTime()/fTimeInterval) + 1;
  G4double nexttime = nperiod*fTimeInterval;
  time = nexttime - track.GetGlobalTime();
  length = time*track.GetVelocity();
}


G4double periodicStepping::
AtRestGetPhysicalInteractionLength( const G4Track& track,
                                            G4ForceCondition* pForceCond )
{ 
  *pForceCond = NotForced ; 

  G4double dl, dt;
  GetLengthTime(track, dl, dt);

  return dt;
}

G4double periodicStepping::
PostStepGetPhysicalInteractionLength( const G4Track& track,
                                   G4double  previousStepSize,
                                   G4ForceCondition* pForceCond )
{ 
  *pForceCond = NotForced ; 

  G4double dl, dt;
  GetLengthTime(track, dl, dt);
  return dl;
}


void periodicStepping::FillHists( const G4Track& track, const G4Step& step)
{
  G4double t_global = track.GetGlobalTime();
  G4ThreeVector spin = track.GetPolarization();
  hSpinX->Fill(t_global/s, spin.x());
  hSpinY->Fill(t_global/s, spin.y());
  hSpinZ->Fill(t_global/s, spin.z());

  hPeriodicDoItCalls->Fill(t_global/s);

  // display message every kPrintInterval seconds
  if(int(t_global/(kPrintInterval*s)) == t_global/(kPrintInterval*s)) {
    G4cout << "time = " << t_global/s << " s, spin = " << spin << G4endl;
    G4cout << "   Position = " << track.GetPosition()/cm << G4endl;
  }

  if(t_global/s > fTimeMax) {
    fParticleChange.ProposeTrackStatus(fStopAndKill);
  }

}

G4VParticleChange* periodicStepping::PostStepDoIt( const G4Track& track,
                                                   const G4Step& step)
{
  fParticleChange.Initialize(track);

  FillHists(track, step);

  return &fParticleChange ;
}

G4VParticleChange* periodicStepping::AtRestDoIt( const G4Track& track,
                                                   const G4Step& step)
{
  fParticleChange.Initialize(track);

  FillHists(track, step);

  return &fParticleChange ;
}


