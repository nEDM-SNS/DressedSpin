#ifndef detector_UIUCCryo_H
#define detector_UIUCCryo_H 1

#include "dressedSpinDetectorConstruction.hh"
#include "MixingFraction.hh"

class detector_UIUCCryo : public dressedSpinDetectorConstruction
{
  public:

    detector_UIUCCryo();
    ~detector_UIUCCryo();

    // there must be enough 4He for bulk liquid to form
    void SetMolesHelium(G4double n4, G4double n3);

    // material properties should be defined in these methods.
    void SetParticleVelocity(G4double v_3);
    void SetTemperature(G4double temperature);
    void SetPressure(G4double pressure);


  protected:
    void ConstructCell(); // called by Construct()

    G4LogicalVolume* celltop_log;
    G4VPhysicalVolume* celltop_phys;

    MixingFraction* mix;

    G4double innerR;     // 0.
    G4double outerR;     // cell radius
    G4double startPhi;   // 0.
    G4double deltaPhi;   // 2*pi
    G4double halfheight; // cell half-height
    G4double zOffset;    // offset of cell in z

    void makeCellTop(G4double height_of_liquid);

  private:
    
};

#endif

