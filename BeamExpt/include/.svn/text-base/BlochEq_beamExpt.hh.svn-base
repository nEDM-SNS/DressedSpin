#ifndef BlochEq_beamExpt_h
#define BlochEq_beamExpt_h 1

#include "BlochEq.hh"

class BlochEq_beamExpt_messenger;

class BlochEq_beamExpt : public BlochEq
{
  public:

  BlochEq_beamExpt();
  virtual ~BlochEq_beamExpt();

  G4ThreeVector Bfield(const G4double t, const G4ThreeVector& p);

  void SetB0(G4ThreeVector val) { fB0 = val; }
  G4ThreeVector GetB0() { return fB0; }

  void SetB1(G4ThreeVector val) { fB1 = val; }
  G4ThreeVector GetB1() { return fB1; }

  void SetB1freq(G4double val) { fB1freq = val; }
  G4double GetB1freq() { return fB1freq; }

  void SetB1phase(G4double val) { fB1phase = val; }
  G4double GetB1phase() { return fB1phase; }

  void ShowParams();

  protected:

  G4ThreeVector fB0; // amplitude (vector) of holding field
  G4ThreeVector fB1; // amplitude (vector) of B1 field
  G4double fB1freq; // frequency of B1 field
  G4double fB1phase; // phase of B1 field

  BlochEq_beamExpt_messenger* fMessenger;

};



//***********************************************************************
// messenger class so we can change paramters with a macro command

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithoutParameter;

#include "G4UImessenger.hh"
#include "globals.hh"

// class description:
//
//  This is a concrete class of G4UImessenger which handles commands to set
//  the BlochEq_beamExpt simulation parameters.
//

class BlochEq_beamExpt_messenger: public G4UImessenger
{
  public:
    BlochEq_beamExpt_messenger(BlochEq_beamExpt* obj);
    ~BlochEq_beamExpt_messenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    BlochEq_beamExpt* fBlochEq_beamExpt;

  private: //commands
    G4UIdirectory* dirBlochEq;
    G4UIcmdWith3VectorAndUnit* B0Cmd; // constant holding field
    G4UIcmdWith3VectorAndUnit* B1Cmd; // dressing field amplitude (vector)
    G4UIcmdWithADoubleAndUnit* B1freqCmd; // applied frequency
    G4UIcmdWithADouble* B1phaseCmd;  // phase (of cosine) of applied field
    G4UIcmdWithoutParameter* printCmd;

};


//***********************************************************************


#endif

