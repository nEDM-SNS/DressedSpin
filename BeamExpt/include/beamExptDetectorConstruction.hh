#ifndef beamExptDetectorConstruction_H
#define beamExptDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

class beamExptDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    beamExptDetectorConstruction();
    virtual ~beamExptDetectorConstruction();

    G4VPhysicalVolume* Construct();

    G4VPhysicalVolume* GetWorldPV() { return experimentalHall_phys; }
    G4LogicalVolume* GetPipeLV() { return pipe_log; }

  protected:
    // Logical volumes
    //
    G4LogicalVolume* experimentalHall_log;
    G4LogicalVolume* pipe_log;
    G4LogicalVolume* pipeend_log;

    // Physical volumes
    //
    G4VPhysicalVolume* experimentalHall_phys;
    G4VPhysicalVolume* pipe_phys;
    G4VPhysicalVolume* pipeend_phys;

};

#endif

