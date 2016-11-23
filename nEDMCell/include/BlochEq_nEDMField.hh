#ifndef BlochEq_nEDMField_h
#define BlochEq_nEDMField_h 1

#include "BlochEq.hh"
#include "fieldmapFile.hh"
#include "fitField.hh"

class BlochEq_nEDMField_messenger;

// The B0 field parameterization is not very good.  It's better to use
// the B0 field map and trilinear interpolation (in the fieldmapFile obj),
// as long as derivatives of B do not have to be continuous across
// the fieldmap grid.
#define BMAP_PARAM 0

class BlochEq_nEDMField : public BlochEq
{
  public:

  BlochEq_nEDMField();
  virtual ~BlochEq_nEDMField();

  G4ThreeVector Bfield(const G4double t, const G4ThreeVector& p);

  void SetHoldingFieldAtOrigin(G4double val);
  G4double GetHoldingFieldAtOrigin() { return fB0x_nom; }
  void ScaleHoldingFieldDeviations(G4double scale);
  void SetRotatingFrameFlag(G4bool val) { fRotatingFrameFlag = val; }
  G4bool GetRotatingFrameFlag() { return fRotatingFrameFlag; }

  void SetDressingFieldAtOrigin(G4double val) { fB1y_nom = val; }
  G4double GetDressingFieldAtOrigin() { return fB1y_nom; }
  void SetB1Freq(G4double val) { fB1Freq = val; }
  G4double GetB1Freq() { return fB1Freq; }

  void ShowParams();

  protected:

  fitField* holdingFieldMap;
//  fieldmapFile* holdingFieldMap;
  G4double fB0x_nom; // nominal B0_x field
  G4bool fRotatingFrameFlag;
  G4double omega_x;  // = -fB0x_nom/gamma, angular velocity of rotating frame

  G4double fB1y_nom; // nominal B1_y field
  G4double fB1Freq;

  BlochEq_nEDMField_messenger* fMessenger;

#if BMAP_PARAM
  double Bx_par[35];
  double By_par[35];
  double Bz_par[35];
  void init_Bx_pars();
  void init_By_pars();
  void init_Bz_pars();
#endif
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

class BlochEq_nEDMField_messenger: public G4UImessenger
{
  public:
    BlochEq_nEDMField_messenger(BlochEq_nEDMField* obj);
    ~BlochEq_nEDMField_messenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    BlochEq_nEDMField* fBlochEq_nEDMField;

  private: //commands
    G4UIdirectory* dirBlochEq;

    G4UIcmdWithADoubleAndUnit* holdingFieldAtOriginCmd;
    G4UIcmdWithADouble* holdingFieldDevsCmd;

    G4UIcmdWithADoubleAndUnit* dressingFieldAtOriginCmd;
    G4UIcmdWithADoubleAndUnit* dressingFieldFreqCmd;

    G4UIcmdWithoutParameter* printCmd;

};


//***********************************************************************


#endif


