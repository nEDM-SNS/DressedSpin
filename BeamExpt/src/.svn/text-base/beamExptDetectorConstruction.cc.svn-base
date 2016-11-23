
#include "beamExptDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"
#include "G4UserLimits.hh"

beamExptDetectorConstruction::beamExptDetectorConstruction()
 :  experimentalHall_log(0), pipe_log(0),
    experimentalHall_phys(0), pipe_phys(0)
{;}

beamExptDetectorConstruction::~beamExptDetectorConstruction()
{
}

G4VPhysicalVolume* beamExptDetectorConstruction::Construct()
{
  G4double pipe_radius = 4.0*cm;   // beam pipe radius
  G4double pipe_length = 91.0*cm;  // length of beam pipe


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

  G4double expHall_x = 1.2*pipe_length;
  G4double expHall_y = 1.2*pipe_length;
  G4double expHall_z = 1.2*pipe_length/2.;
  G4Box* experimentalHall_box
    = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);
  experimentalHall_log = new G4LogicalVolume(experimentalHall_box,
                                             Air,"expHall_log",0,0,0);
  experimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(0,0,0),
                                      experimentalHall_log,"expHall",0,false,0);
  experimentalHall_log->SetVisAttributes(G4VisAttributes::GetInvisible());


  //------------------------------ beam line
  // cylinder with axis along the z-direction

  // material that the volume is made of
  G4Material* vacuum =
      new G4Material("vacuum", z= 1., a= 1.01*g/mole, density= universe_mean_density,
                     kStateGas, temperature = 0.1*kelvin, pressure = 1.e-19*pascal);


  G4double innerR = 0*cm;
  G4double outerR = pipe_radius;
  // make the pipe longer by 0.05*pipe_length, because the extra length on
  // the end will be filled with a different material to represent the
  // detector.
  G4double halfheight = 1.05*pipe_length/2;
  G4double startPhi = 0.*deg;
  G4double deltaPhi = 360.*deg;

  // create the geometry object
  G4Tubs* pipe_tubs = new G4Tubs("pipe_tubs",innerR,outerR,halfheight,startPhi,deltaPhi);

  // create the logical volume in the shape of the geometry object
  pipe_log = new G4LogicalVolume(pipe_tubs,vacuum,"pipe_log",0,0,0);

  // place the logical volume in physical space
  // Pipe runs from z=0 to z=halfheight.
  pipe_phys = new G4PVPlacement(0,G4ThreeVector(0,0,halfheight),
             pipe_log,"pipe",experimentalHall_log,false,0);

  G4VisAttributes* pipe_att = new G4VisAttributes(G4Colour(0,0,1));
  pipe_log->SetVisAttributes(pipe_att);

  //------------------------------ end cap on beam line

  // material that the end cap "Analyzer" is made of
  // (it doesn't matter what material; we just have to be able to
  // easily distinguish the end of the pipe from the sides.)
  G4Material* AnaMat =
  new G4Material("Ana", z= 13., a= 26.98*g/mole, density= 2.7*g/cm3);

  G4double end_thickness = 0.05/2*pipe_length;
  // create the geometry object
  G4Tubs* pipeend_tubs = new G4Tubs("pipeend_tubs",innerR,outerR,
        end_thickness,startPhi,deltaPhi);

  // create the logical volume in the shape of the geometry object
  pipeend_log = new G4LogicalVolume(pipeend_tubs,AnaMat,"pipeend_log",0,0,0);

  // place the logical volume in physical space
  // Pipe end runs from z=halfheight-end_thickness to z=halfheight
  pipeend_phys = new G4PVPlacement(0,G4ThreeVector(0,0,halfheight - end_thickness),
             pipeend_log,"pipeend",pipe_log,false,0);

  G4VisAttributes* pipeend_att = new G4VisAttributes(G4Colour(1,0,0));
  pipeend_log->SetVisAttributes(pipeend_att);

  //------------------------------------------------------------------

  return experimentalHall_phys;
}


