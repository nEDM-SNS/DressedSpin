#include "dressedSpinMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4ios.hh"

dressedSpinMessenger::dressedSpinMessenger(dressedSpinParameters* params)
  :fKineticParams(params)
{
  kineticsDirectory = new G4UIdirectory("/kinetics/");
  kineticsDirectory->SetGuidance("Kinetic parameters commands.");

  temperatureCmd = new G4UIcmdWithADoubleAndUnit("/kinetics/SetTemperature",this);
  temperatureCmd->SetGuidance("Set system temperature (sets particle velocity, scales D)");
  temperatureCmd->SetParameterName("temperature",true,true);
  temperatureCmd->SetDefaultUnit("kelvin");

  pressureCmd = new G4UIcmdWithADouble("/kinetics/SetPressure",this);
  pressureCmd->SetGuidance("Set system pressure in torr (scales D)");
  pressureCmd->SetParameterName("pressure",true,true);

  printCmd = new G4UIcmdWithoutParameter("/kinetics/ShowParameters",this);
  printCmd->SetGuidance("print parameters to stdout");

}

dressedSpinMessenger::~dressedSpinMessenger()
{
  delete temperatureCmd;
  delete pressureCmd;
  delete printCmd;
  delete kineticsDirectory;
}

void dressedSpinMessenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==temperatureCmd )
  { fKineticParams->SetTemperature(temperatureCmd->GetNewDoubleValue(newValues)); }
  else if( command==pressureCmd )
  { fKineticParams->SetPressure(pressureCmd->GetNewDoubleValue(newValues)); }
  else if( command==printCmd )
  { fKineticParams->ShowParams(); }
}

G4String dressedSpinMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==temperatureCmd )
  { cv = temperatureCmd->ConvertToString(fKineticParams->GetTemperature(),"kelvin"); }
  if( command==pressureCmd )
  { cv = pressureCmd->ConvertToString(fKineticParams->GetPressure()); }
  return cv;
}

