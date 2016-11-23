#include "BlochEq_nEDMField.hh"

BlochEq_nEDMField::BlochEq_nEDMField()
{
  G4cout << "Creating BlochEq_nEDMField object" << G4endl;

  SetHoldingFieldAtOrigin(10e-3*gauss);
  fRotatingFrameFlag = false;
#if 0
  holdingFieldMap = new fieldmapFile("/data/npluser/smclayto/n34-field-10mgauss.dat");
#else
  // use ROOT version of field map (it's faster than starting from ascii file)
//  holdingFieldMap = new fieldmapFile("/home/ehl7/fieldmaps/negx-jedmod_truescale_cell_B=0.01G.root");
//  holdingFieldMap = new fieldmapFile("/home/ehl7/fieldmaps/n34-field-10mgauss.root");
  holdingFieldMap = new fitField;
#endif

  fB1y_nom = fB0x_nom*1.2;
  fB1Freq = 1625/s; // dressing frequency (Hz)

  fMessenger = new BlochEq_nEDMField_messenger(this);
}

BlochEq_nEDMField::~BlochEq_nEDMField()
{
  delete fMessenger;
}

void BlochEq_nEDMField::SetHoldingFieldAtOrigin(G4double val)
{
  fB0x_nom = val;
  omega_x = -(fgamma/gauss/s)*fB0x_nom;
}

void BlochEq_nEDMField::ScaleHoldingFieldDeviations(G4double scale)
{
  holdingFieldMap->SetScaleDevsFactor(scale);
}

G4ThreeVector BlochEq_nEDMField::Bfield(const G4double t, const G4ThreeVector &p)
{

  // holding field
//  G4ThreeVector B0_lab = holdingFieldMap->GetFieldVector(p);
  G4ThreeVector B0_lab = holdingFieldMap->GetFieldVector(p)*fB0x_nom;
//	G4cout << "GetFieldVector returned: " << B0_lab << G4endl;

//  G4ThreeVector B0_lab = G4ThreeVector(fB0x_nom, 0, 0);

  // dressing coils are parallel to the xz plane
//  G4ThreeVector B1_lab = G4ThreeVector(0, fB1y_nom, 0);

//   dB1dz, Val1:
//  G4ThreeVector B1_lab = G4ThreeVector(0, fB1y_nom + 1.5e-5*gauss/cm*p.z(), 0);

//   dB1dz, Val2:
//  G4ThreeVector B1_lab = G4ThreeVector(0, fB1y_nom + 0.5e-6*gauss/cm*p.z(), 0);

  // add holding and dressing fields
//  G4ThreeVector B_lab = B0_lab + cos(2*pi*fB1Freq*t)*B1_lab;

	//Holding Field only
  G4ThreeVector B_lab = B0_lab;

  if(fRotatingFrameFlag) {
    // transform field to rotating frame: omega_x = -(fgamma/gauss/s)*fB0x_nom
    G4double cwzt = cos(omega_x*t);
    G4double swzt = sin(omega_x*t);
    G4ThreeVector B_rot = G4ThreeVector(B_lab.x() - fB0x_nom,
                                        B_lab.z()*cwzt + B_lab.y()*swzt,
                                        -B_lab.z()*swzt + B_lab.y()*cwzt);
    return B_rot;
  } else {
    return B_lab;
  }
}


void BlochEq_nEDMField::ShowParams()
{
  G4cout << "|B_0| at origin: " << fB0x_nom/gauss << " gauss" << G4endl;
  G4cout << "B_0 gradient scaling factor: " << holdingFieldMap->GetScaleDevsFactor() << G4endl;

  G4cout << "|B_1| at origin: " << fB1y_nom/gauss << " gauss" << G4endl;
  G4cout << "f_1: " << fB1Freq/(1/s) << " Hz" << G4endl;

}



//***********************************************************************
// messenger class so we can change parameters with a macro command

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4ios.hh"

BlochEq_nEDMField_messenger::BlochEq_nEDMField_messenger(BlochEq_nEDMField* obj)
  :fBlochEq_nEDMField(obj)
{
  dirBlochEq = new G4UIdirectory("/BlochEq/");
  dirBlochEq->SetGuidance("BlochEq commands.");

  //************** begin holding field parameters **************
  holdingFieldAtOriginCmd = 
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetHoldingFieldAtOrigin",this);
  holdingFieldAtOriginCmd->SetGuidance(
        "Set nominal holding field magnitude");
  holdingFieldAtOriginCmd->SetParameterName("holdingFieldAtOrigin",true,true);
  holdingFieldAtOriginCmd->SetDefaultUnit("gauss");

  holdingFieldDevsCmd = 
            new G4UIcmdWithADouble("/BlochEq/ScaleHoldingFieldDeviations",this);
  holdingFieldDevsCmd->SetGuidance(
        "Set scaling of deviations of holding field from ideal");
  holdingFieldDevsCmd->SetParameterName("holdingFieldDevs",true,true);
  //************** end holding field parameters ****************

  //************ begin dressing field parameters **************
  dressingFieldAtOriginCmd = 
            new G4UIcmdWithADoubleAndUnit("/BlochEq/SetDressingFieldAtOrigin",this);
  dressingFieldAtOriginCmd->SetGuidance(
        "Set nominal dressing field magnitude");
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

BlochEq_nEDMField_messenger::~BlochEq_nEDMField_messenger()
{
  delete holdingFieldAtOriginCmd;
  delete holdingFieldDevsCmd;
  delete dressingFieldAtOriginCmd;
  delete dressingFieldFreqCmd;
  delete printCmd;
  delete dirBlochEq;
}

void BlochEq_nEDMField_messenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==holdingFieldAtOriginCmd)
  { fBlochEq_nEDMField->SetHoldingFieldAtOrigin(
               holdingFieldAtOriginCmd->GetNewDoubleValue(newValues)); }
  else if( command==holdingFieldDevsCmd)
  { fBlochEq_nEDMField->ScaleHoldingFieldDeviations(
               holdingFieldDevsCmd->GetNewDoubleValue(newValues)); }
  //********************************************************************
  else if( command==dressingFieldAtOriginCmd)
  { fBlochEq_nEDMField->SetDressingFieldAtOrigin(
               dressingFieldAtOriginCmd->GetNewDoubleValue(newValues)); }
  else if( command==dressingFieldFreqCmd)
  { fBlochEq_nEDMField->SetB1Freq(
               dressingFieldAtOriginCmd->GetNewDoubleValue(newValues)); }
  //********************************************************************
  else if( command==printCmd )
  { fBlochEq_nEDMField->ShowParams(); }
}

G4String BlochEq_nEDMField_messenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==holdingFieldAtOriginCmd)
  { cv = holdingFieldAtOriginCmd->ConvertToString(
               fBlochEq_nEDMField->GetHoldingFieldAtOrigin()); }
  else if( command==dressingFieldAtOriginCmd)
  { cv = dressingFieldAtOriginCmd->ConvertToString(
               fBlochEq_nEDMField->GetDressingFieldAtOrigin()); }
  else if( command==dressingFieldFreqCmd)
  { cv = dressingFieldFreqCmd->ConvertToString(
               fBlochEq_nEDMField->GetB1Freq()); }
  return cv;
}




