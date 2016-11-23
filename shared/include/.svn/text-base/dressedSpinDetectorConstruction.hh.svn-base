#ifndef dressedSpinDetectorConstruction_H
#define dressedSpinDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

class dressedSpinDetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    dressedSpinDetectorConstruction();
    virtual ~dressedSpinDetectorConstruction();

    G4VPhysicalVolume* Construct();

    G4VPhysicalVolume* GetWorldPV() { return experimentalHall_phys; }
    G4LogicalVolume* GetCellLV() { return cell_log; }
    G4double GetCellXmin() { return fCellXmin; }
    G4double GetCellXmax() { return fCellXmax; }
    G4double GetCellYmin() { return fCellYmin; }
    G4double GetCellYmax() { return fCellYmax; }
    G4double GetCellZmin() { return fCellZmin; }
    G4double GetCellZmax() { return fCellZmax; }

    // diffusion material properties should be set in these methods.
    virtual void SetParticleVelocity(G4double v_3);
    virtual void SetTemperature(G4double temperature);
    virtual void SetPressure(G4double pressure);

  protected:
    virtual void ConstructCell(); // called by Construct()

    // Logical volumes
    //
    G4LogicalVolume* experimentalHall_log;
    G4LogicalVolume* cell_log;

    // Physical volumes
    //
    G4VPhysicalVolume* experimentalHall_phys;
    G4VPhysicalVolume* cell_phys;

    G4double fCellXmin;
    G4double fCellXmax;
    G4double fCellYmin;
    G4double fCellYmax;
    G4double fCellZmin;
    G4double fCellZmax;
};

#endif

