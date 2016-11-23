#include "BlochEq_vxE.hh"

BlochEq_vxE::BlochEq_vxE()
{
  G4cout << "Creating BlochEq_vxE object" << G4endl;

  fB0x_nom = 10e-3*gauss;
  fE0x_nom = 1.0e6*volt/cm;

  fMessenger = new BlochEq_vxE_messenger(this);

}

BlochEq_vxE::~BlochEq_vxE()
{
  delete fMessenger;
}


G4ThreeVector BlochEq_vxE::Bfield(const G4double t, const G4ThreeVector &p)
{
  return G4ThreeVector(fB0x_nom, 0, 0);
}

G4ThreeVector BlochEq_vxE::Efield(const G4double t, const G4ThreeVector &p)
{
  return G4ThreeVector(fE0x_nom, 0, 0);
}


void BlochEq_vxE::ShowParams()
{
  G4cout << "|B_0| at origin: " << fB0x_nom/gauss << " gauss" << G4endl;
  G4cout << "|E_0| at origin: " << fE0x_nom/(volt/cm) << " V/cm" << G4endl;

}



//***********************************************************************
// messenger class so we can change parameters with a macro command

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4ios.hh"

BlochEq_vxE_messenger::BlochEq_vxE_messenger(BlochEq_vxE* obj)
  :fBlochEq_vxE(obj)
{
  dirBlochEq = new G4UIdirectory("/BlochEq/");
  dirBlochEq->SetGuidance("BlochEq commands.");

  //************** begin holding field parameters **************
  holdingFieldAtOriginCmd = 
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetHoldingFieldAtOrigin",this);
  holdingFieldAtOriginCmd->SetGuidance(
        "Set holding field magnitude at origin (sets current appropriately)");
  holdingFieldAtOriginCmd->SetParameterName("holdingFieldAtOrigin",true,true);
  holdingFieldAtOriginCmd->SetDefaultUnit("gauss");
  //************** end holding field parameters ****************

  //************** begin electric field parameters **************
  electricFieldAtOriginCmd = 
            new G4UIcmdWithADouble("/BlochEq/SetElectricFieldAtOrigin",this);
  electricFieldAtOriginCmd->SetGuidance(
        "Set electric field magnitude in volts/cm");
  electricFieldAtOriginCmd->SetParameterName("electricFieldAtOrigin",true,true);
  //************** end electric field parameters ****************

  printCmd = new G4UIcmdWithoutParameter("/BlochEq/ShowParameters",this);
  printCmd->SetGuidance("print parameters to stdout");

}

BlochEq_vxE_messenger::~BlochEq_vxE_messenger()
{
  delete holdingFieldAtOriginCmd;
  delete electricFieldAtOriginCmd;
  delete printCmd;
  delete dirBlochEq;
}

void BlochEq_vxE_messenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==holdingFieldAtOriginCmd)
  { fBlochEq_vxE->SetHoldingFieldAtOrigin(
               holdingFieldAtOriginCmd->GetNewDoubleValue(newValues)); }
  else if( command==electricFieldAtOriginCmd)
  { fBlochEq_vxE->SetElectricFieldAtOrigin(
               electricFieldAtOriginCmd->GetNewDoubleValue(newValues)*volt/cm); }
  else if( command==printCmd )
  { fBlochEq_vxE->ShowParams(); }
}

G4String BlochEq_vxE_messenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==holdingFieldAtOriginCmd)
  { cv = holdingFieldAtOriginCmd->ConvertToString(
               fBlochEq_vxE->GetHoldingFieldAtOrigin()); }
  else if( command==electricFieldAtOriginCmd)
  { cv = electricFieldAtOriginCmd->ConvertToString(
               fBlochEq_vxE->GetElectricFieldAtOrigin()/(volt/cm)); }
  return cv;
}




