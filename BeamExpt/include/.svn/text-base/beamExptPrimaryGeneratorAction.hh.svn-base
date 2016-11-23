
#ifndef beamExptPrimaryGeneratorAction_h
#define beamExptPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Navigator.hh"
#include "G4TouchableHandle.hh"
#include "G4Material.hh"

class G4ParticleGun;
class G4Event;

class beamExptGenMessenger;

class beamExptPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    beamExptPrimaryGeneratorAction();
    virtual ~beamExptPrimaryGeneratorAction();

    void SetKineticEnergy(G4double KE);
    G4double GetKineticEnergy();

    void SetVelocity(G4double vel); // sets particle KE consistent with this velocity
    G4double GetVelocity();

  public:
    void GeneratePrimaries(G4Event* anEvent);

  protected:
    G4ParticleGun* particleGun;
    G4double particleVelocity;

    beamExptGenMessenger* fMessenger;
};



//***********************************************************************
// messenger class so we can change paramters with macro commands

class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithADouble;

#include "G4UImessenger.hh"
#include "globals.hh"

// class description:
//
//  This is a concrete class of G4UImessenger which handles commands to set
//  the beamExptPrimaryGeneratorAction parameters.
//

class beamExptGenMessenger: public G4UImessenger
{
  public:
    beamExptGenMessenger(beamExptPrimaryGeneratorAction* obj);
    ~beamExptGenMessenger();

  public:
    void SetNewValue(G4UIcommand * command,G4String newValues);
    G4String GetCurrentValue(G4UIcommand * command);

  private:
    beamExptPrimaryGeneratorAction* fGenerator;

  private: //commands
    G4UIdirectory* dirPrimaryGen;
    G4UIcmdWithADouble* velocityCmd;

};


//***********************************************************************

#endif


