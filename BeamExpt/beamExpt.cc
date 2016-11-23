
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "beamExptDetectorConstruction.hh"
#include "beamExptPhysicsList.hh"
#include "beamExptPrimaryGeneratorAction.hh"
#include "beamExptEventAction.hh"
#include "beamExptTrackingAction.hh"
#include "Randomize.hh"

#include "TFile.h"
#include "TH1.h"
#include "TROOT.h"

#undef G4VIS_USE

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif



void loop_over_velocities(G4UImanager *UI, char *filename)
{
  TH1* hAccumSpin = new TH1D("hAccumSpin", "weighted sum of spin components",3,0.5,3.5);
  hAccumSpin->GetXaxis()->SetBinLabel(1, "S_{x}");
  hAccumSpin->GetXaxis()->SetBinLabel(2, "S_{y}");
  hAccumSpin->GetXaxis()->SetBinLabel(3, "S_{z}");

  FILE* fdat = fopen(filename, "r");
  char vel_cmd_str[20];
  G4double vel, weight;
  while(1) {
    int retval = fscanf(fdat, "%lf %lf\n", &vel, &weight);
    if(retval == EOF) break;
    printf("vel = %f m/s, weight = %f\n", vel, weight);

    sprintf(vel_cmd_str, "/Beam/SetVelocity %f", vel);
    G4String vel_command = vel_cmd_str;
    UI->ApplyCommand(vel_command);
    UI->ApplyCommand("/run/beamOn 1");

    // get spin components at the detector for this particle
    TH1* hspin = (TH1*)gROOT->FindObject("hDetectedSpin");
    if(hspin) {
      double Sx = hspin->GetBinContent(1);
      double Sy = hspin->GetBinContent(2);
      double Sz = hspin->GetBinContent(3);
      printf("vel = %f, spin = (%f, %f, %f)\n", vel,Sx,Sy,Sz);

      hAccumSpin->Fill(1, weight*Sx);
      hAccumSpin->Fill(2, weight*Sy);
      hAccumSpin->Fill(3, weight*Sz);
    }

  } // end loop over velocities

}


int main(int argc, char** argv)
{
  int iarg_mac = -1;
  int iarg_dat = -1;
  int iarg_root = -1;
  // parse command line arguments for filenames.
  //   macro file should have *.mac
  //   velocity data file should have *.dat
  //   ROOT file should hvae *.root
  for(int iarg = 1; iarg < argc; iarg++) {
    int len = strlen(argv[iarg]);
    if(len >= 4 && (strncmp(argv[iarg] + len - 4, ".mac", 4) == 0)) {
      iarg_mac = iarg;
      G4cout << "Macro file: " << argv[iarg_mac] << G4endl;
    } else if((len >= 4) && (strncmp(argv[iarg] + len - 4, ".dat", 4) == 0)) {
      iarg_dat = iarg;
      G4cout << "Velocity data file: " << argv[iarg_dat] << G4endl;
    } else if((len >= 5) && (strncmp(argv[iarg] + len - 5, ".root", 5) == 0)) {
      iarg_root = iarg;
      G4cout << "ROOT (output) file: " << argv[iarg_root] << G4endl;
    }
  } // for iarg


  TFile* froot;
  if(iarg_root > 0) {
    froot = new TFile(argv[iarg_root], "RECREATE");
  } else {
    froot = new TFile("temp.root", "RECREATE");
  }

  // seed random number generator with the current time
  G4int seed = time(0);
  CLHEP::HepRandom::setTheSeed(seed);

  // Construct the default run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // set mandatory initialization classes
  //
  G4VUserDetectorConstruction* detector = new beamExptDetectorConstruction;
  runManager->SetUserInitialization(detector);
  //
  G4VUserPhysicsList* physics = new beamExptPhysicsList;
  runManager->SetUserInitialization(physics);

#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // set mandatory user action class
  //
  G4VUserPrimaryGeneratorAction* gen_action = new beamExptPrimaryGeneratorAction();
  runManager->SetUserAction(gen_action);

  // set optional user event action, which is called at the beginning of
  // the event (after the particle is created), and at the end of the event
  G4UserEventAction* event_action = new beamExptEventAction;
  runManager->SetUserAction(event_action);

  // set optional user tracking action, which is called at the start/end
  // point of processing one track
  G4UserTrackingAction* track_action = new beamExptTrackingAction;
  runManager->SetUserAction(track_action);


  // Initialize G4 kernel
  //
  runManager->Initialize();


  // Get the pointer to the UI manager and set verbosities
  //
  G4UImanager* UI = G4UImanager::GetUIpointer();

  UI->ApplyCommand("/run/verbose 0");
  UI->ApplyCommand("/event/verbose 0");
  UI->ApplyCommand("/tracking/verbose 0");

  if(iarg_mac < 0) // if no macro file specified
  {
    // if no macro file is specified, then start an interactive session.
    G4UIsession* session = 0;
#ifdef G4UI_USE_TCSH
    session = new G4UIterminal(new G4UItcsh);
#else
    session = new G4UIterminal();
#endif
    session->SessionStart();
    delete session;

  } else {
    // if macro file is specified...
    G4String command = "/control/execute ";
    G4String fileName = argv[iarg_mac];
    UI->ApplyCommand(command+fileName);

    // if velocity distribution data file is specified...
    if(iarg_dat > 0) loop_over_velocities(UI, argv[iarg_dat]);
  }


  // Job termination
  //
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  //


  froot->Write();
  froot->Close();
  delete froot;

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}


