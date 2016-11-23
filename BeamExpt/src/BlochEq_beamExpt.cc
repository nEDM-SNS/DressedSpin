#include "BlochEq_beamExpt.hh"

BlochEq_beamExpt::BlochEq_beamExpt()
{
  fMessenger = new BlochEq_beamExpt_messenger(this);

  fB0 = G4ThreeVector(10*gauss, 0., 0.);

  fB1 = G4ThreeVector(5*gauss, 0., 0.);
  fB1freq = 0;
  fB1phase = 0;
}

BlochEq_beamExpt::~BlochEq_beamExpt()
{
  delete fMessenger;
}

G4ThreeVector BlochEq_beamExpt::Bfield(const G4double t, const G4ThreeVector &p)
{
  return fB0 + fB1*cos(2*pi*fB1freq*t + fB1phase);
}

void BlochEq_beamExpt::ShowParams()
{
  G4cout << "B0: " << fB0/gauss << " gauss" << G4endl;
  G4cout << "B1: " << fB1/gauss << " gauss" << G4endl;
  G4cout << "B1 frequency: " << fB1freq/hertz << " Hz" << G4endl;
  G4cout << "B1 phase: " << fB1phase << " rad" << G4endl;
}


//***********************************************************************
// messenger class so we can change parameters with a macro commands


#include "G4UIdirectory.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4ios.hh"

BlochEq_beamExpt_messenger::BlochEq_beamExpt_messenger(BlochEq_beamExpt* obj)
  :fBlochEq_beamExpt(obj)
{
  dirBlochEq = new G4UIdirectory("/BlochEq/");
  dirBlochEq->SetGuidance("BlochEq commands.");

  B0Cmd = new G4UIcmdWith3VectorAndUnit("/BlochEq/SetB0",this);
  B0Cmd->SetGuidance("Set holding field");
  B0Cmd->SetParameterName("B0_x","B0_y","B0_z",true,true);
  B0Cmd->SetDefaultUnit("gauss");

  B1Cmd = new G4UIcmdWith3VectorAndUnit("/BlochEq/SetB1",this);
  B1Cmd->SetGuidance("Set maximum of B1");
  B1Cmd->SetParameterName("B1_x","B1_y","B1_z",true,true);
  B1Cmd->SetDefaultUnit("gauss");

  B1freqCmd = new G4UIcmdWithADoubleAndUnit("/BlochEq/SetB1freq",this);
  B1freqCmd->SetGuidance("Set frequency of field in Hz");
  B1freqCmd->SetParameterName("B1freq",true,true);
  B1freqCmd->SetDefaultUnit("hertz");

  B1phaseCmd = new G4UIcmdWithADouble("/BlochEq/SetB1phase",this);
  B1phaseCmd->SetGuidance("Set phase of field in radians");
  B1phaseCmd->SetParameterName("B1phase",true,true);

  printCmd = new G4UIcmdWithoutParameter("/BlochEq/ShowParameters",this);
  printCmd->SetGuidance("print parameters to stdout");

}

BlochEq_beamExpt_messenger::~BlochEq_beamExpt_messenger()
{
  delete B0Cmd;
  delete B1Cmd;
  delete B1freqCmd;
  delete B1phaseCmd;
  delete printCmd;
  delete dirBlochEq;
}

void BlochEq_beamExpt_messenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==B0Cmd )
  { fBlochEq_beamExpt->SetB0(B0Cmd->GetNew3VectorValue(newValues)); }
  else if( command==B1Cmd )
  { fBlochEq_beamExpt->SetB1(B1Cmd->GetNew3VectorValue(newValues)); }
  else if( command==B1freqCmd )
  { fBlochEq_beamExpt->SetB1freq(B1freqCmd->GetNewDoubleValue(newValues)); }
  else if( command==B1phaseCmd )
  { fBlochEq_beamExpt->SetB1phase(B1phaseCmd->GetNewDoubleValue(newValues)); }
  else if( command==printCmd )
  { fBlochEq_beamExpt->ShowParams(); }
}

G4String BlochEq_beamExpt_messenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==B0Cmd )
  { cv = B0Cmd->ConvertToString(fBlochEq_beamExpt->GetB0()); }
  else if( command==B1Cmd )
  { cv = B1Cmd->ConvertToString(fBlochEq_beamExpt->GetB1()); }
  else if( command==B1freqCmd )
  { cv = B1freqCmd->ConvertToString(fBlochEq_beamExpt->GetB1freq()); }
  else if( command==B1phaseCmd )
  { cv = B1phaseCmd->ConvertToString(fBlochEq_beamExpt->GetB1phase()); }
  return cv;
}


