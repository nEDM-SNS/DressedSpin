#include "BlochEq_UIUCTableTop.hh"

BlochEq_UIUCTableTop::BlochEq_UIUCTableTop()
{
  G4cout << "Creating BlochEq_UIUCTableTop object" << G4endl;

  holdingField.SetRadius(0.5*m);
  holdingField.SetFieldAtOrigin(0.260*gauss);

  dressingField.SetRadius(0.1*m);
  dressingField.SetFieldAtOrigin(0.0843*gauss);
  fB1Freq = 1625/s; // dressing frequency (Hz)

  earthCompField.SetRadius(0.254*m);
  earthCompField.SetFieldAtOrigin(0.2124*3.125*gauss);

  fB_earth = G4ThreeVector(0, -1*earthCompField.GetFieldAtOrigin(), 0.140*gauss);


  fMessenger = new BlochEq_UIUCTableTop_messenger(this);

}

BlochEq_UIUCTableTop::~BlochEq_UIUCTableTop()
{
  delete fMessenger;
}

G4ThreeVector BlochEq_UIUCTableTop::Bfield(const G4double t, const G4ThreeVector &p)
{
  G4double B0r, B0z; // holding field
  G4double B1r, B1z; // dressing field
  G4double Ber, Bez; // earth field compensation coils

  G4double x = p.x();
  G4double y = p.y();
  G4double z = p.z();

  G4double r_holding = sqrt(x*x + y*y);
  G4double z_holding = z;
  holdingField.Bfield(r_holding, z_holding, B0r, B0z);
  G4ThreeVector B0;
  B0.setZ(B0z);
  if(r_holding/cm < 1e-15) {
    B0.setX(0);
    B0.setY(0);
  } else {
    B0.setX(B0r*fabs(x)/r_holding);
    B0.setY(B0r*fabs(y)/r_holding);
  }

  // dressing coils are parallel to the xz plane
  G4double r_dressing = sqrt(x*x + z*z);
  G4double z_dressing = y;
  dressingField.Bfield(r_dressing, z_dressing, B1r, B1z);
  G4ThreeVector B1;
  B1.setY(B1z);

  // the earth field compensation coils are aligned with dressing coils
  earthCompField.Bfield(r_dressing, z_dressing, Ber, Bez);
  G4ThreeVector Be;
  Be.setY(Bez);

  if(r_dressing/cm < 1e-15) {
    B1.setX(0);
    B1.setZ(0);
    Be.setX(0);
    Be.setZ(0);
  } else {
    B1.setX(B1r*fabs(x)/r_dressing);
    B1.setZ(B1r*fabs(z)/r_dressing);
    Be.setX(Ber*fabs(x)/r_dressing);
    Be.setZ(Ber*fabs(z)/r_dressing);
  }

  // add holding and dressing fields, and additional background field
  return B0 + Be + fB_earth + cos(2*pi*fB1Freq*t)*B1;
}


void BlochEq_UIUCTableTop::ShowParams()
{
  G4cout << "B_0 radius: " << holdingField.GetRadius()/cm << " cm" << G4endl;
  G4cout << "B_0 current: " << holdingField.GetCurrent()/ampere << " ampere-turns" << G4endl;
  G4cout << "|B_0| at origin: " << holdingField.GetFieldAtOrigin()/gauss << " gauss" << G4endl;

  G4cout << "B_1 radius: " << dressingField.GetRadius()/cm << " cm" << G4endl;
  G4cout << "B_1 current: " << dressingField.GetCurrent()/ampere << " ampere-turns" << G4endl;
  G4cout << "|B_1| at origin: " << dressingField.GetFieldAtOrigin()/gauss << " gauss" << G4endl;
  G4cout << "f_1: " << fB1Freq/(1/s) << " Hz" << G4endl;

  G4cout << "B_v radius: " << earthCompField.GetRadius()/cm << " cm" << G4endl;
  G4cout << "B_v current: " << earthCompField.GetCurrent()/ampere << " ampere-turns" << G4endl;
  G4cout << "|B_v| at origin: " << earthCompField.GetFieldAtOrigin()/gauss << " gauss" << G4endl;

  G4cout << "Background field: " << fB_earth/gauss << " gauss" << G4endl;
}



//***********************************************************************
// messenger class so we can change parameters with a macro command

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4ios.hh"

BlochEq_UIUCTableTop_messenger::BlochEq_UIUCTableTop_messenger(BlochEq_UIUCTableTop* obj)
  :fBlochEq_UIUCTableTop(obj)
{
  dirBlochEq = new G4UIdirectory("/BlochEq/");
  dirBlochEq->SetGuidance("BlochEq commands.");

  //************** begin holding field parameters **************
  holdingFieldRadiusCmd =
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetHoldingFieldRadius",this);
  holdingFieldRadiusCmd->SetGuidance("Set B0 coil radius");
  holdingFieldRadiusCmd->SetParameterName("holdingFieldRadius",true,true);
  holdingFieldRadiusCmd->SetDefaultUnit("cm");

  holdingFieldCurrentCmd =
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetHoldingFieldCurrent",this);
  holdingFieldCurrentCmd->SetGuidance("Set B0 coil current (ampere-turns)");
  holdingFieldCurrentCmd->SetParameterName("holdingFieldCurrent",true,true);
  holdingFieldCurrentCmd->SetDefaultUnit("ampere");

  holdingFieldAtOriginCmd = 
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetHoldingFieldAtOrigin",this);
  holdingFieldAtOriginCmd->SetGuidance(
        "Set holding field magnitude at origin (sets current appropriately)");
  holdingFieldAtOriginCmd->SetParameterName("holdingFieldAtOrigin",true,true);
  holdingFieldAtOriginCmd->SetDefaultUnit("gauss");
  //************** end holding field parameters ****************

  //************ begin earthComp field parameters **************
  earthCompFieldRadiusCmd =
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetEarthCompFieldRadius",this);
  earthCompFieldRadiusCmd->SetGuidance("Set Bv coil radius");
  earthCompFieldRadiusCmd->SetParameterName("earthCompFieldRadius",true,true);
  earthCompFieldRadiusCmd->SetDefaultUnit("cm");

  earthCompFieldCurrentCmd =
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetEarthCompFieldCurrent",this);
  earthCompFieldCurrentCmd->SetGuidance("Set Bv coil current (ampere-turns)");
  earthCompFieldCurrentCmd->SetParameterName("earthCompFieldCurrent",true,true);
  earthCompFieldCurrentCmd->SetDefaultUnit("ampere");

  earthCompFieldAtOriginCmd = 
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetEarthCompFieldAtOrigin",this);
  earthCompFieldAtOriginCmd->SetGuidance(
        "Set earthComp field magnitude at origin (sets current appropriately)");
  earthCompFieldAtOriginCmd->SetParameterName("earthComdFieldAtOrigin",true,true);
  earthCompFieldAtOriginCmd->SetDefaultUnit("gauss");
  //************** end earthComp field parameters ****************

  //************ begin dressing field parameters **************
  dressingFieldRadiusCmd =
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetDressingFieldRadius",this);
  dressingFieldRadiusCmd->SetGuidance("Set B1 coil radius");
  dressingFieldRadiusCmd->SetParameterName("dressingFieldRadius",true,true);
  dressingFieldRadiusCmd->SetDefaultUnit("cm");

  dressingFieldCurrentCmd =
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetDressingFieldCurrent",this);
  dressingFieldCurrentCmd->SetGuidance("Set B1 coil current (ampere-turns)");
  dressingFieldCurrentCmd->SetParameterName("dressingFieldCurrent",true,true);
  dressingFieldCurrentCmd->SetDefaultUnit("ampere");

  dressingFieldAtOriginCmd = 
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetDressingFieldAtOrigin",this);
  dressingFieldAtOriginCmd->SetGuidance(
        "Set dressing field magnitude at origin (sets current appropriately)");
  dressingFieldAtOriginCmd->SetParameterName("dressingFieldAtOrigin",true,true);
  dressingFieldAtOriginCmd->SetDefaultUnit("gauss");

  dressingFieldFreqCmd =
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetDressingFieldFreq",this);
  dressingFieldFreqCmd->SetGuidance("Set B1 frequency");
  dressingFieldFreqCmd->SetParameterName("dressingFieldFreq",true,true);
  dressingFieldFreqCmd->SetDefaultUnit("hertz");
  //************** end dressing field parameters ****************


  printCmd = new G4UIcmdWithoutParameter("/BlochEq/ShowParameters",this);
  printCmd->SetGuidance("print parameters to stdout");

}

BlochEq_UIUCTableTop_messenger::~BlochEq_UIUCTableTop_messenger()
{
  delete holdingFieldRadiusCmd;
  delete holdingFieldCurrentCmd;
  delete holdingFieldAtOriginCmd;
  delete earthCompFieldRadiusCmd;
  delete earthCompFieldCurrentCmd;
  delete earthCompFieldAtOriginCmd;
  delete dressingFieldRadiusCmd;
  delete dressingFieldCurrentCmd;
  delete dressingFieldAtOriginCmd;
  delete dressingFieldFreqCmd;
  delete printCmd;
  delete dirBlochEq;
}

void BlochEq_UIUCTableTop_messenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==holdingFieldRadiusCmd)
  { fBlochEq_UIUCTableTop->GetHoldingFieldCoils()->SetRadius(
               holdingFieldRadiusCmd->GetNewDoubleValue(newValues)); }
  else if( command==holdingFieldCurrentCmd)
  { fBlochEq_UIUCTableTop->GetHoldingFieldCoils()->SetCurrent(
               holdingFieldCurrentCmd->GetNewDoubleValue(newValues)); }
  else if( command==holdingFieldAtOriginCmd)
  { fBlochEq_UIUCTableTop->GetHoldingFieldCoils()->SetFieldAtOrigin(
               holdingFieldAtOriginCmd->GetNewDoubleValue(newValues)); }
  //********************************************************************
  else if( command==earthCompFieldRadiusCmd)
  { fBlochEq_UIUCTableTop->GetEarthCompFieldCoils()->SetRadius(
               earthCompFieldRadiusCmd->GetNewDoubleValue(newValues));
    fBlochEq_UIUCTableTop->GetB_earth_ptr()->setY(
              -1*fBlochEq_UIUCTableTop->GetEarthCompFieldCoils()->GetFieldAtOrigin()); }
  else if( command==earthCompFieldCurrentCmd)
  { fBlochEq_UIUCTableTop->GetEarthCompFieldCoils()->SetCurrent(
               earthCompFieldCurrentCmd->GetNewDoubleValue(newValues));
    fBlochEq_UIUCTableTop->GetB_earth_ptr()->setY(
              -1*fBlochEq_UIUCTableTop->GetEarthCompFieldCoils()->GetFieldAtOrigin()); }
  else if( command==earthCompFieldAtOriginCmd)
  { fBlochEq_UIUCTableTop->GetEarthCompFieldCoils()->SetFieldAtOrigin(
               earthCompFieldAtOriginCmd->GetNewDoubleValue(newValues));
    fBlochEq_UIUCTableTop->GetB_earth_ptr()->setY(
              -1*fBlochEq_UIUCTableTop->GetEarthCompFieldCoils()->GetFieldAtOrigin()); }
  //********************************************************************
  else if( command==dressingFieldRadiusCmd)
  { fBlochEq_UIUCTableTop->GetDressingFieldCoils()->SetRadius(
               dressingFieldRadiusCmd->GetNewDoubleValue(newValues)); }
  else if( command==dressingFieldCurrentCmd)
  { fBlochEq_UIUCTableTop->GetDressingFieldCoils()->SetCurrent(
               dressingFieldCurrentCmd->GetNewDoubleValue(newValues)); }
  else if( command==dressingFieldAtOriginCmd)
  { fBlochEq_UIUCTableTop->GetDressingFieldCoils()->SetFieldAtOrigin(
               dressingFieldAtOriginCmd->GetNewDoubleValue(newValues)); }
  else if( command==dressingFieldFreqCmd)
  { fBlochEq_UIUCTableTop->SetB1Freq(
               dressingFieldAtOriginCmd->GetNewDoubleValue(newValues)); }
  else if( command==printCmd )
  { fBlochEq_UIUCTableTop->ShowParams(); }
}

G4String BlochEq_UIUCTableTop_messenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==holdingFieldRadiusCmd)
  { cv = holdingFieldRadiusCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetHoldingFieldCoils()->GetRadius()); }
  else if( command==holdingFieldCurrentCmd)
  { cv = holdingFieldCurrentCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetHoldingFieldCoils()->GetCurrent()); }
  else if( command==holdingFieldAtOriginCmd)
  { cv = holdingFieldAtOriginCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetHoldingFieldCoils()->GetFieldAtOrigin()); }
  else if( command==earthCompFieldRadiusCmd)
  { cv = earthCompFieldRadiusCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetEarthCompFieldCoils()->GetRadius()); }
  else if( command==earthCompFieldCurrentCmd)
  { cv = earthCompFieldCurrentCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetEarthCompFieldCoils()->GetCurrent()); }
  else if( command==earthCompFieldAtOriginCmd)
  { cv = earthCompFieldAtOriginCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetEarthCompFieldCoils()->GetFieldAtOrigin()); }
  else if( command==dressingFieldRadiusCmd)
  { cv = dressingFieldRadiusCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetDressingFieldCoils()->GetRadius()); }
  else if( command==dressingFieldCurrentCmd)
  { cv = dressingFieldCurrentCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetDressingFieldCoils()->GetCurrent()); }
  else if( command==dressingFieldAtOriginCmd)
  { cv = dressingFieldAtOriginCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetDressingFieldCoils()->GetFieldAtOrigin()); }
  else if( command==dressingFieldFreqCmd)
  { cv = dressingFieldFreqCmd->ConvertToString(
               fBlochEq_UIUCTableTop->GetB1Freq()); }
  return cv;
}




