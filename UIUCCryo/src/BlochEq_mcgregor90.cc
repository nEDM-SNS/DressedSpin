#include "BlochEq_mcgregor90.hh"

BlochEq_mcgregor90::BlochEq_mcgregor90()
{
  G4cout << "Creating BlochEq_mcgregor90 object" << G4endl;

  fMessenger = new BlochEq_mcgregor90_messenger(this);

  gradHz = G4ThreeVector(0,0,0);

  fGradFreq = 0; // gradient frequency

}

BlochEq_mcgregor90::~BlochEq_mcgregor90()
{
  delete fMessenger;
}

G4ThreeVector BlochEq_mcgregor90::Bfield(const G4double t, const G4ThreeVector &p)
{
//  return G4ThreeVector(0, 0, 0.53*gauss + x*fdHzdx*1e-5*gauss/cm);
  G4double delta_Hz = p * gradHz*1e-5*gauss/cm;
  return G4ThreeVector(0, 0, 0.53*gauss + cos(2*pi*fGradFreq*t)*delta_Hz);
}

void BlochEq_mcgregor90::ShowParams()
{
  G4cout << "grad H_z = " << gradHz << " nT/cm" << G4endl;
  G4cout << "freqeuncy of grad H_z = " << fGradFreq/hertz << " Hz" << G4endl;
}



//***********************************************************************
// messenger class so we can change paramters with a macro command


#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4ios.hh"

BlochEq_mcgregor90_messenger::BlochEq_mcgregor90_messenger(BlochEq_mcgregor90* obj)
  :fBlochEq_mcgregor90(obj)
{
  dirBlochEq = new G4UIdirectory("/BlochEq/");
  dirBlochEq->SetGuidance("BlochEq commands.");

  gradientCmd = new G4UIcmdWith3Vector("/BlochEq/SetGradient",this);
  gradientCmd->SetGuidance("Set field gradient (dH_z/dx, dH_z/dy, dH_z/dz) in nT/cm");
  gradientCmd->SetParameterName("dH_z/dx","dH_z/dy","dH_z/dz",true,true);

  gradFreqCmd = new G4UIcmdWithADoubleAndUnit("/BlochEq/SetGradFreq",this);
  gradFreqCmd->SetGuidance("Set frequency of field gradient in Hz");
  gradFreqCmd->SetParameterName("gradFreq",true,true);
  gradFreqCmd->SetDefaultUnit("hertz");

  printCmd = new G4UIcmdWithoutParameter("/BlochEq/ShowParameters",this);
  printCmd->SetGuidance("print parameters to stdout");

}

BlochEq_mcgregor90_messenger::~BlochEq_mcgregor90_messenger()
{
  delete gradientCmd;
  delete gradFreqCmd;
  delete printCmd;
  delete dirBlochEq;
}

void BlochEq_mcgregor90_messenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==gradientCmd )
  { fBlochEq_mcgregor90->SetGradient(gradientCmd->GetNew3VectorValue(newValues)); }
  else if( command==gradFreqCmd )
  { fBlochEq_mcgregor90->SetGradFreq(gradFreqCmd->GetNewDoubleValue(newValues)); }
  else if( command==printCmd )
  { fBlochEq_mcgregor90->ShowParams(); }
}

G4String BlochEq_mcgregor90_messenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==gradientCmd )
  { cv = gradientCmd->ConvertToString(fBlochEq_mcgregor90->GetGradient()); }
  else if( command==gradFreqCmd )
  { cv = gradFreqCmd->ConvertToString(fBlochEq_mcgregor90->GetGradFreq()); }
  return cv;
}



