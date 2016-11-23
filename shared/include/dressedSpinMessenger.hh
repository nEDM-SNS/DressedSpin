#ifndef dressedSpinMessenger_h
#define dressedSpinMessenger_h 1

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;

#include "dressedSpinParameters.hh"
#include "G4UImessenger.hh"
#include "globals.hh"

// class description:
//
//  This is a concrete class of G4UImessenger which handles commands to set
//  the dressedSpin simulation parameters.
//

class dressedSpinParameters;

class dressedSpinMessenger: public G4UImessenger
{
  public:
    dressedSpinMessenger(dressedSpinParameters* params);
    ~dressedSpinMessenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    dressedSpinParameters* fKineticParams;

  private: //commands
    G4UIdirectory* kineticsDirectory;
    G4UIcmdWithADoubleAndUnit* temperatureCmd;
    G4UIcmdWithADouble* pressureCmd;
    G4UIcmdWithoutParameter* printCmd;

};

#endif

