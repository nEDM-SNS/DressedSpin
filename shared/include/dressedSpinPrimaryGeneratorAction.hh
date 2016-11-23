
#ifndef dressedSpinPrimaryGeneratorAction_h
#define dressedSpinPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Navigator.hh"
#include "G4TouchableHandle.hh"
#include "G4Material.hh"
#include "G4ParticleDefinition.hh"

class G4ParticleGun;
class G4Event;
class dressedSpinParameters;


class dressedSpinPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    dressedSpinPrimaryGeneratorAction(G4ParticleDefinition* particle_def = 0);
    virtual ~dressedSpinPrimaryGeneratorAction();

    // this method must be called before GeneratePrimaries
    void SetDressedSpinParametersObj(dressedSpinParameters* obj) { kinetic_params = obj; }

    void SetKineticEnergy(G4double KE);
    void SetInitialPolarization(G4ThreeVector& vec);
    G4ThreeVector GetInitialPolarization();
    G4double GetKineticEnergy();
    G4double GetVelocity() { return particleVelocity; }
    G4double GetMass() { return particleMass; }

  public:
    void GeneratePrimaries(G4Event* anEvent);

    bool PointIsInCell(const G4ThreeVector& p);
       // caution: also sets fStartingMaterial to the material at point p

    G4Material* GetStartingMaterial() { return fStartingMaterial; }

  protected:
    virtual void ChooseInitialPosition();

    dressedSpinParameters *kinetic_params;
    G4ParticleGun* particleGun;
    G4ThreeVector NewMomentum;
    G4double particleMass;
    G4double particleVelocity;

    G4Navigator* aNavigator;
    G4TouchableHandle aTouchableHandle;

    G4Material* fStartingMaterial;
};


#endif



