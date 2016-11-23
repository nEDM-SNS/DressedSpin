#ifndef fieldMap_h
#define fieldMap_h 1

#include "dressedSpinPrimaryGeneratorAction.hh"
#include "dressedSpinDetectorConstruction.hh"
#include "dressedSpinPhysicsList.hh"

#include "TH3.h"

class fieldMap_messenger;

class fieldMap
{
  public:

  fieldMap();
  virtual ~fieldMap();

  void SetPrimaryGeneratorObj(dressedSpinPrimaryGeneratorAction* obj) { fGenAction = obj; }
  void SetDetectorObj(dressedSpinDetectorConstruction* obj) { fDetector = obj; }
  void SetPhysicsListObj(dressedSpinPhysicsList* obj) { fPhysicsList = obj; }

  void Compute();

  protected:
  dressedSpinPrimaryGeneratorAction* fGenAction;
  dressedSpinDetectorConstruction* fDetector;
  dressedSpinPhysicsList* fPhysicsList;

  TH3* hBfieldMap_Norm; // bin content is 1 if in cell, 0 otherwise
  TH3* hBfieldMap_x; // x-component
  TH3* hBfieldMap_y; // y-component
  TH3* hBfieldMap_z; // z-component

  TH3* hBfieldGradHzx; // x-component of grad Hz
  TH3* hBfieldGradHzy; // y-component of grad Hz
  TH3* hBfieldGradHzz; // z-component of grad Hz

  fieldMap_messenger* fMessenger;

};



//***********************************************************************
// messenger class so we can change parameters with a macro command

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
//  the fieldMap simulation parameters.
//

class fieldMap_messenger: public G4UImessenger
{
  public:
    fieldMap_messenger(fieldMap* obj);
    ~fieldMap_messenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    fieldMap* fFieldMap;

  private: //commands
    G4UIdirectory* dirFieldMap;
    G4UIcmdWithoutParameter* computeCmd;

};


//***********************************************************************


#endif

