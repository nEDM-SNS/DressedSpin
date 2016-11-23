#ifndef BlochEq_UIUCTableTop_h
#define BlochEq_UIUCTableTop_h 1

#include "BlochEq.hh"
#include "helmholtzCoils.hh"

class BlochEq_UIUCTableTop_messenger;

class BlochEq_UIUCTableTop : public BlochEq
{
  public:

  BlochEq_UIUCTableTop();
  virtual ~BlochEq_UIUCTableTop();

  G4ThreeVector Bfield(const G4double t, const G4ThreeVector& p);

  helmholtzCoils* GetHoldingFieldCoils() { return &holdingField; }
  helmholtzCoils* GetDressingFieldCoils() { return &dressingField; }
  helmholtzCoils* GetEarthCompFieldCoils() { return &earthCompField; }

  void SetB1Freq(G4double val) { fB1Freq = val; }
  G4double GetB1Freq() { return fB1Freq; }

  G4ThreeVector* GetB_earth_ptr() { return &fB_earth; }

  void ShowParams();

  protected:

  helmholtzCoils holdingField;
  helmholtzCoils dressingField;
  helmholtzCoils earthCompField;

  G4double fB1Freq;

  G4ThreeVector fB_earth; // uniform constant background field

  BlochEq_UIUCTableTop_messenger* fMessenger;

};





//***********************************************************************
// messenger class so we can change paramters with a macro command

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;

#include "G4UImessenger.hh"
#include "globals.hh"

class BlochEq_UIUCTableTop_messenger: public G4UImessenger
{
  public:
    BlochEq_UIUCTableTop_messenger(BlochEq_UIUCTableTop* obj);
    ~BlochEq_UIUCTableTop_messenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    BlochEq_UIUCTableTop* fBlochEq_UIUCTableTop;

  private: //commands
    G4UIdirectory* dirBlochEq;

    G4UIcmdWithADoubleAndUnit* holdingFieldRadiusCmd;
    G4UIcmdWithADoubleAndUnit* holdingFieldCurrentCmd;
    G4UIcmdWithADoubleAndUnit* holdingFieldAtOriginCmd;

    G4UIcmdWithADoubleAndUnit* dressingFieldRadiusCmd;
    G4UIcmdWithADoubleAndUnit* dressingFieldCurrentCmd;
    G4UIcmdWithADoubleAndUnit* dressingFieldAtOriginCmd;
    G4UIcmdWithADoubleAndUnit* dressingFieldFreqCmd;

    G4UIcmdWithADoubleAndUnit* earthCompFieldRadiusCmd;
    G4UIcmdWithADoubleAndUnit* earthCompFieldCurrentCmd;
    G4UIcmdWithADoubleAndUnit* earthCompFieldAtOriginCmd;

    G4UIcmdWithoutParameter* printCmd;

};


//***********************************************************************


#endif


