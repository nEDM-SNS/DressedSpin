#ifndef diffusionMaterial_hh
#define diffusionMaterial_hh 1

#include "G4Material.hh"
#include "G4ios.hh"
#include "globals.hh"

class diffusionMaterial : public G4Material
{
  public:
  diffusionMaterial(G4String name);
  virtual ~diffusionMaterial();

  G4double GetMeanFreePath() { return fMeanFreePath; }
  void SetMeanFreePath(G4double lambda) { fMeanFreePath = lambda; }

  // set temperature/pressure/velocity, and calculate mean free path based on
  // the diffusion constant and the particle velocity
  void SetTemperature(G4double temperature);
  void SetPressure(G4double presssure);
  void SetParticleVelocity(G4double particle_velocity);

  G4double GetTemperature() { return fTemperature; }
  G4double GetPressure() { return fPressure; }
  G4double GetParticleVelocity() { return fParticleVelocity; }
  G4double GetD() { return fD; } // diffusion constant

  private:
  G4double fMeanFreePath;
  G4double fTemperature;
  G4double fPressure;  // (torr) not used if LHe4
  G4double fParticleVelocity; // understood to be the particle velocity if in vacuum
  G4double fD; // diffusion constant

  void changedPTv3();

};

#endif

