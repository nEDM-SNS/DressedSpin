#ifndef BlochEq_vxE_h
#define BlochEq_vxE_h 1

#include "BlochEq.hh"
#include "helmholtzCoils.hh"

class BlochEq_vxE_messenger;

//*********************************************************************
// This is an example of a BlochEq object for applying perfectly
// uniform magnetic and electric fields.  The messenger object also
// defined allows the parameters to be changed with macro commands.
//*********************************************************************

class BlochEq_vxE : public BlochEq
{
  public:

  BlochEq_vxE();
  virtual ~BlochEq_vxE();

  G4ThreeVector Bfield(const G4double t, const G4ThreeVector& p);
  G4ThreeVector Efield(const G4double t, const G4ThreeVector& p);

  void SetHoldingFieldAtOrigin(G4double val) { fB0x_nom = val; }
  G4double GetHoldingFieldAtOrigin() { return fB0x_nom; }
  void SetElectricFieldAtOrigin(G4double val) { fE0x_nom = val; }
  G4double GetElectricFieldAtOrigin() { return fE0x_nom; }

  void ShowParams();

  protected:

  G4double fB0x_nom; // nominal B0_x field
  G4double fE0x_nom; // nominal E0_x field

  BlochEq_vxE_messenger* fMessenger;

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

class BlochEq_vxE_messenger: public G4UImessenger
{
  public:
    BlochEq_vxE_messenger(BlochEq_vxE* obj);
    ~BlochEq_vxE_messenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    BlochEq_vxE* fBlochEq_vxE;

  private: //commands
    G4UIdirectory* dirBlochEq;

    G4UIcmdWithADoubleAndUnit* holdingFieldAtOriginCmd;
    G4UIcmdWithADouble* electricFieldAtOriginCmd;

    G4UIcmdWithoutParameter* printCmd;

};


//***********************************************************************


#endif


