
#include "detector_mcgregor90.hh"

#include "diffusionMaterial.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"

detector_mcgregor90::detector_mcgregor90()
{
}

detector_mcgregor90::~detector_mcgregor90()
{
}

void detector_mcgregor90::ConstructCell()
{
  //------------------------------ measurement cell
  // The cell is cylindrical with axis along the z-axis.
  // The holding field H_0 defines the z-axis (horizontal in the
  // UIUC dressed spin experiment).


  // material that the volume is made of
  diffusionMaterial* cell_mat = new diffusionMaterial("He3Gas");

  G4double innerR = 0*cm;
  G4double outerR = 12.35/2*cm;  // cell radius
  G4double halfheight = 12.35/2*cm;  // half-height of the cell
  G4double startPhi = 0.*deg;
  G4double deltaPhi = 360.*deg;

  // create the geometry object
  G4Tubs* cell_tubs = new G4Tubs("cell_tubs",innerR,outerR,halfheight,startPhi,deltaPhi);

  // create the logical volume in the shape of the geometry object
  cell_log = new G4LogicalVolume(cell_tubs,cell_mat,"cell_log",0,0,0);

  // place the logical volume in physical space
  G4RotationMatrix cell_rot; // this object lets us rotate the volume in physical space
  cell_rot.rotateY(90.*deg); // rotate by 90 degrees about the y-axis
                             // to align the cell along the x-axis
  cell_phys = new G4PVPlacement(G4Transform3D(cell_rot,
             G4ThreeVector(0,0,0)),
             cell_log,"cell",experimentalHall_log,false,0);

  // set outer limits used by dressedSpinPrimaryGeneratorAction::ChooseInitialPosition()
  // to find a starting point within the cell.
  fCellXmin = -halfheight;
  fCellXmax = halfheight;
  fCellYmin = -outerR;
  fCellYmax = outerR;
  fCellZmin = -outerR;
  fCellZmax = outerR;

  //------------------------------------------------------------------
}

