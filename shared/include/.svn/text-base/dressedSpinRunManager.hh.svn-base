#ifndef dressedSpinRunManager_hh
#define dressedSpinRunManager_hh 1

#include "G4RunManager.hh"
#include "G4Timer.hh"
#include "G4RunManagerKernel.hh"
#include "globals.hh"

class dressedSpinRunManager : public G4RunManager
{
  public:
  dressedSpinRunManager();
  virtual ~dressedSpinRunManager();

  // DoEventLoop is nearly the same as in the base class, the difference
  // being the event loop is stopped if the run time is exceeded.
  void DoEventLoop(G4int n_event,const char* macroFile=0,G4int n_select=-1);

  void SetEventLoopTimeLimit(G4double tlimit) { fTimeLimit = tlimit/s; }
  G4double GetEventLoopTimeLimit() { return fTimeLimit*s; }

  private:
  G4double fTimeLimit;
  G4Timer* timer2;

};

#endif

