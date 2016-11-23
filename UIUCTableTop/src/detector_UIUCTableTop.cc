
#include "detector_UIUCTableTop.hh"

#include "diffusionMaterial.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"

detector_UIUCTableTop::detector_UIUCTableTop()
{
}

detector_UIUCTableTop::~detector_UIUCTableTop()
{
}

void detector_UIUCTableTop::ConstructCell()
{
  //------------------------------ measurement cell
  // The cell is cylindrical with axis along the z-axis.
  // The holding field H_0 defines the z-axis (horizontal in the
  // UIUC dressed spin experiment).


  // material that the volume is made of
  diffusionMaterial* cell_mat = new diffusionMaterial("He3Gas");

  G4double innerR = 0*cm;
  G4double outerR = 2.5*cm;  // cell radius
  G4double halfheight = 2.5*cm;  // half-height of the cell
  G4double startPhi = 0.*deg;
  G4double deltaPhi = 360.*deg;

//  G4double zOffset = 2.0*cm; // amount to shift cell in z direction
  G4double zOffset = 0.0*cm; // amount to shift cell in z direction

  // create the geometry object
  G4Tubs* cell_tubs = new G4Tubs("cell_tubs",innerR,outerR,halfheight,startPhi,deltaPhi);

  // create the logical volume in the shape of the geometry object
  cell_log = new G4LogicalVolume(cell_tubs,cell_mat,"cell_log",0,0,0);

  // place the logical volume in physical space
  G4RotationMatrix cell_rot; // this object lets us rotate the volume in physical space
//  cell_rot.rotateY(90.*deg); // rotate by 90 degrees about the y-axis
  cell_phys = new G4PVPlacement(G4Transform3D(cell_rot,
             G4ThreeVector(0,0,zOffset)), // shift cell along z
             cell_log,"cell",experimentalHall_log,false,0);


  // set outer limits used by dressedSpinPrimaryGeneratorAction::ChooseInitialPosition()
  // to find a starting point within the cell.
  fCellXmin = -outerR;
  fCellXmax = outerR;
  fCellYmin = -outerR;
  fCellYmax = outerR;
  fCellZmin = -halfheight + zOffset;
  fCellZmax = halfheight + zOffset;
  //------------------------------------------------------------------

#ifdef DRAW_COILS
  G4Material* Al = new G4Material("Aluminum",13.,26.98*g/mole,2.7*g/cm3);

  G4VisAttributes* cell_att = new G4VisAttributes(G4Colour(1,0.5,0.5));
  cell_log->SetVisAttributes(cell_att);

  //********************* holding field coils ********************
  G4double B0coil_R = 50.0*cm;
  G4double B0coil_dR = 0.5*cm;
  G4Tubs* B0coil_tubs = new G4Tubs("B0coil_tubs",
         B0coil_R - B0coil_dR, B0coil_R + B0coil_dR,
         B0coil_dR, startPhi,deltaPhi);
  G4LogicalVolume* B0coil_log = new G4LogicalVolume(B0coil_tubs,Al,"B0coil_log",0,0,0);
  G4RotationMatrix B0coil_rot; // this object lets us rotate the volume in physical space
  G4VPhysicalVolume* B0coil_phys_1 = new G4PVPlacement(G4Transform3D(B0coil_rot,
             G4ThreeVector(0,0,B0coil_R/2)),
             B0coil_log,"B0coil_1",experimentalHall_log,false,0);
  G4VPhysicalVolume* B0coil_phys_2 = new G4PVPlacement(G4Transform3D(B0coil_rot,
             G4ThreeVector(0,0,-B0coil_R/2)),
             B0coil_log,"B0coil_2",experimentalHall_log,false,0);

  G4VisAttributes* B0coil_att = new G4VisAttributes(G4Colour::Cyan());
  B0coil_log->SetVisAttributes(B0coil_att);

  //********************* dressing field coils ********************
  G4double B1coil_R = 10.0*cm;
  G4double B1coil_dR = 0.5*cm;
  G4Tubs* B1coil_tubs = new G4Tubs("B1coil_tubs",
         B1coil_R - B1coil_dR, B1coil_R + B1coil_dR,
         B1coil_dR, startPhi,deltaPhi);
  G4LogicalVolume* B1coil_log = new G4LogicalVolume(B1coil_tubs,Al,"B1coil_log",0,0,0);
  G4RotationMatrix B1coil_rot; // this object lets us rotate the volume in physical space
  B1coil_rot.rotateX(90.*deg); // rotate by 90 degrees about the x-axis
  G4VPhysicalVolume* B1coil_phys_1 = new G4PVPlacement(G4Transform3D(B1coil_rot,
             G4ThreeVector(0,B1coil_R/2,0)),
             B1coil_log,"B1coil_1",experimentalHall_log,false,0);
  G4VPhysicalVolume* B1coil_phys_2 = new G4PVPlacement(G4Transform3D(B1coil_rot,
             G4ThreeVector(0,-B1coil_R/2,0)),
             B1coil_log,"B1coil_2",experimentalHall_log,false,0);

  G4VisAttributes* B1coil_att = new G4VisAttributes(G4Colour::Red());
  B1coil_log->SetVisAttributes(B1coil_att);

  //********************* Bv field coils ********************
  G4double Bvcoil_R = 25.4*cm;
  G4double Bvcoil_dR = 0.5*cm;
  G4Tubs* Bvcoil_tubs = new G4Tubs("Bvcoil_tubs",
         Bvcoil_R - Bvcoil_dR, Bvcoil_R + Bvcoil_dR,
         Bvcoil_dR, startPhi,deltaPhi);
  G4LogicalVolume* Bvcoil_log = new G4LogicalVolume(Bvcoil_tubs,Al,"Bvcoil_log",0,0,0);
  G4RotationMatrix Bvcoil_rot; // this object lets us rotate the volume in physical space
  Bvcoil_rot.rotateX(90.*deg); // rotate by 90 degrees about the x-axis
  G4VPhysicalVolume* Bvcoil_phys_1 = new G4PVPlacement(G4Transform3D(Bvcoil_rot,
             G4ThreeVector(0,Bvcoil_R/2,0)),
             Bvcoil_log,"Bvcoil_1",experimentalHall_log,false,0);
  G4VPhysicalVolume* Bvcoil_phys_2 = new G4PVPlacement(G4Transform3D(Bvcoil_rot,
             G4ThreeVector(0,-Bvcoil_R/2,0)),
             Bvcoil_log,"Bvcoil_2",experimentalHall_log,false,0);

  G4VisAttributes* Bvcoil_att = new G4VisAttributes(G4Colour::Blue());
  Bvcoil_log->SetVisAttributes(Bvcoil_att);

#endif

}


