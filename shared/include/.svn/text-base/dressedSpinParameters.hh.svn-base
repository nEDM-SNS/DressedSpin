#ifndef dressedSpinParameters_h
#define dressedSpinParameters_h 1

#include "dressedSpinMessenger.hh"
#include "dressedSpinDetectorConstruction.hh"
#include "dressedSpinPhysicsList.hh"
#include "dressedSpinPrimaryGeneratorAction.hh"
#include "globals.hh"

#include "TH1.h"

class dressedSpinMessenger;

class dressedSpinParameters
{
  public:
  dressedSpinParameters();
  ~dressedSpinParameters();

  void SetDetectorConstruction(dressedSpinDetectorConstruction* ptr) { detector = ptr; }
  void SetPrimaryGeneratorAction(dressedSpinPrimaryGeneratorAction* ptr) { gen_action = ptr; }
  void SetPhysicsList(dressedSpinPhysicsList* ptr) { physics = ptr; }

  void SetTemperature(G4double temperature);
  void SetPressure(G4double pressure);

  G4double GetTemperature() { return fT; }
  G4double GetPressure() { return fPressure; }

  G4double GetThermalVelocity();

  void FillParamHist(); // fill present parameter values into histogram
  void ShowParams();    // print parameters to STDOUT

  void changedPT(); // recalculate T- and P-dependent parameters.
                    // also sets KE of dressedSpinPrimaryGeneratorAction::particleGun
  private:

  dressedSpinMessenger* paramsMessenger;
  dressedSpinDetectorConstruction* detector;
  dressedSpinPrimaryGeneratorAction* gen_action;
  dressedSpinPhysicsList* physics;

  G4double fT; // temperature
  G4double fPressure; // pressure (not relevant for cryo temperatures)
  G4double fD; // diffusion constant

  TH1 *hParameters;

};

#endif

