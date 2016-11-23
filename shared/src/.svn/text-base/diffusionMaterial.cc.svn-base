#include "diffusionMaterial.hh"

diffusionMaterial::diffusionMaterial(G4String name)
    : G4Material(name,2.,3.0*g/mole,125.*kg/m3,kStateGas,300*kelvin,1.013e5*pascal),
    fMeanFreePath(0.26*mm), fTemperature(300*kelvin), fPressure(1.0), 
    fParticleVelocity(1.57e5*cm/s), fD(1370.2*cm*cm/s)
{
}

diffusionMaterial::~diffusionMaterial()
{
}

void diffusionMaterial::SetTemperature(G4double temperature)
{
  fTemperature = temperature;
  changedPTv3();
}

void diffusionMaterial::SetPressure(G4double pressure)
{
  fPressure = pressure;
  changedPTv3();
}

void diffusionMaterial::SetParticleVelocity(G4double particle_velocity)
{
  fParticleVelocity = particle_velocity;
  changedPTv3();
}

void diffusionMaterial::changedPTv3()
{
  if(strcmp(this->GetName(),"He3Gas") == 0) {
    if(fTemperature < 4*kelvin) {
// from nacher94_HEVAC_model
      fD = 1.100e-5*m2/s*pow(fTemperature,1.65)/fPressure;
    } else {
// quoted in mcgregor90
      fD = 1370.2*pow(fTemperature/(300.*kelvin), 1.5)/fPressure*cm*cm/s; // pressure in torr
    }
    this->SetMeanFreePath(3*fD/fParticleVelocity);
  } else { // 3He in LHe4
    fD = 1.6/pow(fTemperature/kelvin, 7)*cm*cm/s;
    this->SetMeanFreePath(3*fD/(fParticleVelocity/std::sqrt(2.4)));
  }

G4cout << this->GetName() << ": D = " << fD/cm/cm*s << " cm^2/s"
       << ", T = " << fTemperature << " K"
       << ", P = " << fPressure << " torr"
       << ", v_3 = " << fParticleVelocity/cm*s << " cm/s"
       << ", lambda = " << this->GetMeanFreePath()/cm << " cm" << G4endl;
}


