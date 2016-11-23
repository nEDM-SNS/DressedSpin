#ifndef BlochEq_mcgregor90_h
#define BlochEq_mcgregor90_h 1

#include "BlochEq.hh"
#include "helmholtzCoils.hh"

class BlochEq_mcgregor90_messenger;

class BlochEq_mcgregor90 : public BlochEq
{
  public:

  BlochEq_mcgregor90();
  virtual ~BlochEq_mcgregor90();

  G4ThreeVector Bfield(const G4double t, const G4ThreeVector& p);

  void SetGradient(G4ThreeVector vec) { gradHz = vec; }
  G4ThreeVector GetGradient() { return gradHz; }

  void SetGradFreq(G4double val) { fGradFreq = val; }
  G4double GetGradFreq() { return fGradFreq; }

  void ShowParams();

  protected:

  G4ThreeVector gradHz; // gradient of H_z in nT/cm
  G4double fGradFreq; // frequency of field gradient

  BlochEq_mcgregor90_messenger* fMessenger;

};



//***********************************************************************
// messenger class so we can change paramters with a macro command

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWith3Vector;
class G4UIcmdWithoutParameter;

#include "G4UImessenger.hh"
#include "globals.hh"

// class description:
//
//  This is a concrete class of G4UImessenger which handles commands to set
//  the BlochEq_mcgregor90 simulation parameters.
//

class BlochEq_mcgregor90_messenger: public G4UImessenger
{
  public:
    BlochEq_mcgregor90_messenger(BlochEq_mcgregor90* obj);
    ~BlochEq_mcgregor90_messenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    BlochEq_mcgregor90* fBlochEq_mcgregor90;

  private: //commands
    G4UIdirectory* dirBlochEq;
    G4UIcmdWith3Vector* gradientCmd;
    G4UIcmdWithADoubleAndUnit* gradFreqCmd;
    G4UIcmdWithoutParameter* printCmd;
    G4UIcmdWithoutParameter* fillmapCmd;

};


//***********************************************************************


#endif

