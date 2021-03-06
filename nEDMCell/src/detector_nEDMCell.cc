
#include "detector_nEDMCell.hh"

#include "diffusionMaterial.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "globals.hh"

detector_nEDMCell::detector_nEDMCell()
{
}

detector_nEDMCell::~detector_nEDMCell()
{
}

void detector_nEDMCell::ConstructCell()
{
  //------------------------------ measurement cell

  // material that the volume is made of
  diffusionMaterial* cell_mat = new diffusionMaterial("LHe4");

  // set outer limits used by dressedSpinPrimaryGeneratorAction::ChooseInitialPosition()
  // to find a starting point within the cell.
  //------------------------------------------------------------------
  fCellXmin = 4.9*cm;
  fCellXmax = 12.7*cm;
  fCellYmin = -5.0*cm;
  fCellYmax = 5.0*cm;
  fCellZmin = -20.0*cm;
  fCellZmax = 20.0*cm;

  G4double Rx = (fCellXmax - fCellXmin)/2.;
  G4double Ry = (fCellYmax - fCellYmin)/2.;
  G4double Rz = (fCellZmax - fCellZmin)/2.;

  G4double xOffset = (fCellXmin + fCellXmax)/2.; // amount to shift cell in x direction
  G4double yOffset = (fCellYmin + fCellYmax)/2.; // amount to shift cell in y direction
  G4double zOffset = (fCellZmin + fCellZmax)/2.; // amount to shift cell in z direction

  // create the geometry object
  G4Box* cell_box = new G4Box("cell_box",Rx,Ry,Rz);

  // create the logical volume in the shape of the geometry object
  cell_log = new G4LogicalVolume(cell_box,cell_mat,"cell_log",0,0,0);

  // place the logical volume in physical space
  G4RotationMatrix cell_rot; // this object lets us rotate the volume in physical space
//  cell_rot.rotateY(90.*deg); // rotate by 90 degrees about the y-axis
  cell_phys = new G4PVPlacement(G4Transform3D(cell_rot,
             G4ThreeVector(xOffset,yOffset,zOffset)),
             cell_log,"cell",experimentalHall_log,false,0);

  G4VisAttributes* cell_att = new G4VisAttributes(G4Colour(0.5,0.5,1.0));
  cell_log->SetVisAttributes(cell_att);

}

