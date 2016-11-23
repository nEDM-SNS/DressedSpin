
#include "dressedSpinDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4UserLimits.hh"
#include "diffusionMaterial.hh"

dressedSpinDetectorConstruction::dressedSpinDetectorConstruction()
 :  experimentalHall_log(0), cell_log(0),
    experimentalHall_phys(0), cell_phys(0)
{;}

dressedSpinDetectorConstruction::~dressedSpinDetectorConstruction()
{
}

G4VPhysicalVolume* dressedSpinDetectorConstruction::Construct()
{

  //--- variables and objects used later for materials specifications
  G4String name;
  G4String symbol;
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
  G4double temperature;
  G4double pressure;
  G4int ncomponents;
  G4double fractionmass;

  a = 14.01*g/mole;
  G4Element* N  = new G4Element(name="Nitrogen",symbol="N" , z= 7., a);

  a = 16.00*g/mole;
  G4Element* O  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);

  //------------------------------------------------------ volumes

  //------------------------------ experimental hall (world volume)
  density = 1.290*mg/cm3;
  G4Material* Air = 
      new G4Material("Air", density, ncomponents=2);
  Air->AddElement(N, fractionmass=0.7);
  Air->AddElement(O, fractionmass=0.3);

  G4double expHall_x = 1.0*m;
  G4double expHall_y = 1.0*m;
  G4double expHall_z = 1.0*m;
  G4Box* experimentalHall_box
    = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);
  experimentalHall_log = new G4LogicalVolume(experimentalHall_box,
                                             Air,"expHall_log",0,0,0);
  experimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(),
                                      experimentalHall_log,"expHall",0,false,0);
  experimentalHall_log->SetVisAttributes(G4VisAttributes::GetInvisible());

  // set maximum boundaries that contain the cell.
  // These limits should be reduced to the actual cell limits
  // in ConstructCell().
  fCellXmin = -expHall_x;
  fCellXmax = expHall_x;
  fCellYmin = -expHall_y;
  fCellYmax = expHall_y;
  fCellZmin = -expHall_z;
  fCellZmax = expHall_z;

  ConstructCell();

#if 0
// (doesn't work: error when trying to use the G4UserSpecialCuts in the physics list)
  G4double maxTime = 10*s; // maximum "time of flight" of the particle
  cell_log->SetUserLimits(new G4UserLimits(DBL_MAX,DBL_MAX,maxTime));
#endif

  return experimentalHall_phys;
}

void dressedSpinDetectorConstruction::ConstructCell()
{
  G4cerr << "Base class method dressedSpinDetectorConstruction::ConstructCell() should not be called!" << G4endl;
}

void dressedSpinDetectorConstruction::SetParticleVelocity(G4double particle_velocity)
{
  if(cell_log) {
    diffusionMaterial* mat = (diffusionMaterial*)(cell_log->GetMaterial());
    mat->SetParticleVelocity(particle_velocity);
  }
}

void dressedSpinDetectorConstruction::SetTemperature(G4double temperature)
{
  if(cell_log) {
    diffusionMaterial* mat = (diffusionMaterial*)(cell_log->GetMaterial());
    mat->SetTemperature(temperature);
  }
}

void dressedSpinDetectorConstruction::SetPressure(G4double pressure)
{
  if(cell_log) {
    diffusionMaterial* mat = (diffusionMaterial*)(cell_log->GetMaterial());
    mat->SetPressure(pressure);
  }
}


