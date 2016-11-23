
#include "dressedSpinRunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "dressedSpinPrimaryGeneratorAction.hh"
#include "dressedSpinEventAction.hh"
// #include "dressedSpinTrackingAction.hh"
// #include "dressedSpinSteppingAction.hh"
#include "diffusionMaterial.hh"
#include "dressedSpinParameters.hh"
#include "fieldMap.hh"
#include "Randomize.hh"

#include "UIUCTableTopPhysicsList.hh"
#include "detector_UIUCTableTop.hh"

#include "TFile.h"
#include "TH1.h"

#define SHOWVIEWER 0


#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

int main(int argc, char** argv)
{
  int iarg_mac = -1;
  int iarg_root = -1;
  // parse command line arguments for filenames.
  //   macro file should have *.mac
  //   ROOT file should hvae *.root
  for(int iarg = 1; iarg < argc; iarg++) {
    int len = strlen(argv[iarg]);
    if(len >= 4 && (strncmp(argv[iarg] + len - 4, ".mac", 4) == 0)) {
      iarg_mac = iarg;
      G4cout << "Macro file: " << argv[iarg_mac] << G4endl;
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




  G4int seed = time(0);
  CLHEP::HepRandom::setTheSeed(seed);

  // Construct the default run manager
  //
  dressedSpinRunManager* runManager = new dressedSpinRunManager;

  // this sets the maximum wall clock time for the simulation
  runManager->SetEventLoopTimeLimit(4.0*3600.0*s);

  // set mandatory initialization classes
  //
  G4cout << "Creating detector_UIUCTableTop object" << G4endl;
  detector_UIUCTableTop* detector = new detector_UIUCTableTop;
  runManager->SetUserInitialization(detector);
  //
  UIUCTableTopPhysicsList* physics = new UIUCTableTopPhysicsList;
  runManager->SetUserInitialization(physics);

#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // set mandatory user action class
  //
  dressedSpinPrimaryGeneratorAction* gen_action = new dressedSpinPrimaryGeneratorAction();
  runManager->SetUserAction(gen_action);

  // set optional user event action, which is called at the beginning of
  // the event (after the particle is created), and at the end of the event
  G4UserEventAction* event_action = new dressedSpinEventAction;
  runManager->SetUserAction(event_action);

  // set optional user tracking action, which is called at the start/end
  // point of processing one track
//  G4UserTrackingAction* track_action = new dressedSpinTrackingAction;
//  runManager->SetUserAction(track_action);

  // set optional user stepping action (executed after each step)
//  G4UserSteppingAction* step_action = new dressedSpinSteppingAction;
//  runManager->SetUserAction(step_action);


  // Initialize G4 kernel
  //
  runManager->Initialize();


  dressedSpinParameters* params = new dressedSpinParameters();
  gen_action->SetDressedSpinParametersObj(params);
  params->SetDetectorConstruction(detector);
  params->SetPrimaryGeneratorAction(gen_action);
  params->SetPhysicsList(physics);
  params->SetTemperature(300.*kelvin); // change in macro with command /kinetics/temperature

  physics->GetDiffusionProcess()->SetDiffusionParamObj(params);

  // create object that is optionally called to fill in B-field map histograms
  fieldMap* fieldMapObj = new fieldMap;
  fieldMapObj->SetPrimaryGeneratorObj(gen_action);
  fieldMapObj->SetDetectorObj(detector);
  fieldMapObj->SetPhysicsListObj(physics);

  // Get the pointer to the UI manager and set verbosities
  //
  G4UImanager* UI = G4UImanager::GetUIpointer();

#if SHOWVIEWER
  UI->ApplyCommand("/run/verbose 2");
  UI->ApplyCommand("/event/verbose 2");
  UI->ApplyCommand("/tracking/verbose 2");
#else
  UI->ApplyCommand("/run/verbose 0");
  UI->ApplyCommand("/event/verbose 0");
  UI->ApplyCommand("/tracking/verbose 0");
#endif

  if(iarg_mac < 0) // if no macro file specified
  {
    G4UIsession* session = 0;
#ifdef G4UI_USE_TCSH
    session = new G4UIterminal(new G4UItcsh);
#else
    session = new G4UIterminal();
#endif
#if SHOWVIEWER
    UI->ApplyCommand("/control/execute macros/vis.mac");
#endif
    session->SessionStart();
    delete session;
  } else {
    // macro file is specified...
    G4String command = "/control/execute ";
    G4String fileName = argv[iarg_mac];
    UI->ApplyCommand(command+fileName);
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
  delete params;
  delete fieldMapObj;


#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}


