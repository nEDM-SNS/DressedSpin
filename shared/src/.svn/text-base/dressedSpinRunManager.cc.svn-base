#include "G4Timer.hh"

#include "dressedSpinRunManager.hh"
#include "G4RunManagerKernel.hh"

#include "G4UImanager.hh"
#include "G4ios.hh"

dressedSpinRunManager::dressedSpinRunManager()
{
  // G4Timer object "timer" is created in the base class constructor
  timer2 = new G4Timer();
  fTimeLimit = -1;
}

dressedSpinRunManager::~dressedSpinRunManager()
{
  delete timer2;
}

void dressedSpinRunManager::DoEventLoop(G4int n_event,const char* macroFile,G4int n_select)
{
  if(verboseLevel>0)
  { timer->Start(); }

  G4String msg;
  if(macroFile!=0)
  {
    if(n_select<0) n_select = n_event;
    msg = "/control/execute ";
    msg += macroFile;
  }
  else
  { n_select = -1; }

// Event loop
  G4int i_event;
  G4double total_elapsed_time = 0;
  for( i_event=0; i_event<n_event; i_event++ )
  {
    if(fTimeLimit > 0) timer2->Start();
    currentEvent = GenerateEvent(i_event);
    eventManager->ProcessOneEvent(currentEvent);
    AnalyzeEvent(currentEvent);
    if(i_event<n_select) G4UImanager::GetUIpointer()->ApplyCommand(msg);
    StackPreviousEvent(currentEvent);
    currentEvent = 0;
    if(fTimeLimit > 0) {
      timer2->Stop();
      total_elapsed_time += timer2->GetRealElapsed();
      if(total_elapsed_time >= fTimeLimit) {
        G4cout << " Run beamOn elapsed time limit reached" << G4endl;
        break;
      }
    }
    if(runAborted) break;
  }

  if(verboseLevel>0)
  {
    timer->Stop();
    G4cout << "Run terminated." << G4endl;
    G4cout << "Run Summary" << G4endl;
    if(runAborted)
    { G4cout << "  Run Aborted after " << i_event << " events processed." << G4endl; }
    else
    { G4cout << "  Number of events processed : " << i_event << G4endl; }
    G4cout << "  "  << *timer << G4endl;
  }
}



