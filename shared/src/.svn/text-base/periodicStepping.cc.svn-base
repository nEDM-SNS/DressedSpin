
#include "periodicStepping.hh"

// define these in your custom physics list class instead of here
// const G4double periodicStepping::kMaxSimulationSeconds = 100;

periodicStepping::periodicStepping( G4int verboseLevel )
  : G4VProcess( G4String("periodicStepping"), fUserDefined),
    fVerboseLevel( verboseLevel ), fTimeInterval(1e-3*s),
    faxis(0), tree(0)
{
  static G4TouchableHandle nullTouchableHandle;  // Points to (G4VTouchable*) 0
  fCurrentTouchableHandle = nullTouchableHandle; 

  ft = -1;
}

void periodicStepping::CreateHistograms(G4bool makeTree)
{
  // Choose histogram parameters such that the bin widths are
  // fTimeInterval/s.
  G4int nbins = int(kMaxSimulationSeconds/(fTimeInterval/s));

  hPeriodicDoItCalls = new TH1D("hPeriodicDoItCalls","hPeriodicDoitCalls",
          nbins,0,kMaxSimulationSeconds);
  hPeriodicDoItCalls->GetXaxis()->SetTitle("Time (s)");
  faxis = hPeriodicDoItCalls->GetXaxis();

  if(makeTree == true) {
    tree = new TTree("Spins","Spin vectors");
    tree->Branch("t",&ft,"t/D");     // time
    tree->Branch("x",&fx,"x/F");     // x position
    tree->Branch("y",&fy,"y/F");     // y position
    tree->Branch("z",&fz,"z/F");     // z position
    tree->Branch("Sx",&fSx,"Sx/F");  // x-component of spin
    tree->Branch("Sy",&fSy,"Sy/F");  // y-component of spin
    tree->Branch("Sz",&fSz,"Sz/F");  // z-component of spin
  } else {
    hSpinX = new TH1D("hSpinX","Spin x-component", nbins, 0, kMaxSimulationSeconds);
    hSpinX->GetXaxis()->SetTitle("Time (s)");
    hSpinY = new TH1D("hSpinY","Spin y-component", nbins, 0, kMaxSimulationSeconds);
    hSpinY->GetXaxis()->SetTitle("Time (s)");
    hSpinZ = new TH1D("hSpinZ","Spin z-component", nbins, 0, kMaxSimulationSeconds);
    hSpinZ->GetXaxis()->SetTitle("Time (s)");

    double xmin = -40.;
    double xmax = 40.;
    double ymin = -40.;
    double ymax = 40.;
    double zmin = -40.;
    double zmax = 40.;
    int nbinsx = int(xmax - xmin + 0.5);
    int nbinsy = int(ymax - ymin + 0.5);
    int nbinsz = int(zmax - zmin + 0.5);
    htempx = new TH1D("htempx","x-position of particle",nbinsx,xmin,xmax);
    htempy = new TH1D("htempy","y-position of particle",nbinsy,ymin,ymax);
    htempz = new TH1D("htempz","z-position of particle",nbinsz,zmin,zmax);

#if XYZHIST
    htempxyz = new TH3F("htempxyz","xyz-position of particle",nbinsx,xmin,xmax,
                         nbinsy,ymin,ymax, nbinsz,zmin,zmax);
#endif
  }

}

periodicStepping::~periodicStepping()
{
}

void periodicStepping::GetLengthTime(const G4Track& track, G4double &length, G4double &time)
{
  // find the time to the next histogram bin that hasn't been filled
  G4double t_global = track.GetGlobalTime();
  int bin = hPeriodicDoItCalls->FindBin(t_global/s);
  double ncalls_bin = hPeriodicDoItCalls->GetBinContent(bin);
  double ncalls_nextbin = hPeriodicDoItCalls->GetBinContent(bin+1);
  if(ncalls_bin > ncalls_nextbin) ++bin;

  G4double nexttime = hPeriodicDoItCalls->GetXaxis()->GetBinCenter(bin)*s;
  time = nexttime - track.GetGlobalTime();
  // calculate equivalent length
  length = time*track.GetVelocity();

#if 0
  G4cout << "position: " << track.GetPosition()/cm << G4endl;
  G4cout << "t_global = " << t_global/s
         << " s, time = " << time/s
         << " s, length = " << length/cm << " cm" << G4endl;
#endif
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
  G4ThreeVector p = track.GetPosition();

  if(faxis) {
    hPeriodicDoItCalls->Fill(t_global/s);

    if(tree) {
      ft = t_global/s;
      fx = Float_t(p.x()/mm);
      fy = Float_t(p.y()/mm);
      fz = Float_t(p.z()/mm);
      fSx = Float_t(spin.x());
      fSy = Float_t(spin.y());
      fSz = Float_t(spin.z());
      tree->Fill();
    } else {
      hSpinX->Fill(t_global/s, spin.x());
      hSpinY->Fill(t_global/s, spin.y());
      hSpinZ->Fill(t_global/s, spin.z());
      htempx->Fill(p.x()/mm);
      htempy->Fill(p.y()/mm);
      htempz->Fill(p.z()/mm);
#if XYZHIST
      htempxyz->Fill(p.x()/mm,p.y()/mm,p.z()/mm);
#endif
    }

    // display message every fPrintInterval calls
    int bin = faxis->FindBin(t_global/s);
    if(bin%fPrintInterval == 0) {
      G4cout << "time = " << t_global/s << " s, spin = " << spin << G4endl;
      G4cout << "   Position = " << p/cm << G4endl;
    }
  } else {
    G4cout << "Error in periodicStepping: CreateHistograms not called before FillHists"
           << G4endl;
    fParticleChange.ProposeTrackStatus(fStopAndKill);
  }

  if(t_global/s > kMaxSimulationSeconds) {
    G4cout << "periodicStepping: particle time reached kMaxSimulationSeconds. Ending track."
           << G4endl;
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


