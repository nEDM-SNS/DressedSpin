
#include "detector_UIUCCryo.hh"

#include "diffusionMaterial.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4GeometryManager.hh"
#include "globals.hh"
#include "MixingFraction.hh"

detector_UIUCCryo::detector_UIUCCryo()
{
  mix = new MixingFraction;
  mix->SetWoverk(1.54); // heat of mixing (K)
  mix->Setn4(4.5/22.4); // 4.5 liters at STP
  mix->Setn3(250./760./22.4/1000); // 250 torr-cc at room temperature
  mix->SetVm(32); // molar volume of LHe4 (cc)
  mix->SetT(0.4); // temperature (K)

  celltop_phys = 0;
  celltop_log = 0;
}

detector_UIUCCryo::~detector_UIUCCryo()
{
  delete mix;
}

void detector_UIUCCryo::SetParticleVelocity(G4double particle_velocity)
{
  if(cell_log) {
    diffusionMaterial *mat = (diffusionMaterial*)(cell_log->GetMaterial());
    mat->SetParticleVelocity(particle_velocity);
  }
  if(celltop_log) {
    diffusionMaterial *mat2 = (diffusionMaterial*)(celltop_log->GetMaterial());
    mat2->SetParticleVelocity(particle_velocity);
  }
}

void detector_UIUCCryo::SetMolesHelium(G4double n4, G4double n3)
{
  mix->Setn4(n4);
  mix->Setn3(n3);

  G4double Xliq = mix->GetXliq(); // 3He concentration in liquid
  G4double nliq = mix->Getnliq(); // total amount of liquid (mol)
  G4double Vliq = nliq*mix->GetVm()*cm3; // calc volume (cc) of liquid from molar volume of LHe4
  G4double hliq = Vliq/(pi*outerR*outerR);
G4cout << "n4 = " << n4 << " mol, n3 = " << n3 << " mol"
       << ", hliq = " << hliq/cm << " cm" << G4endl;

  G4GeometryManager::GetInstance()->OpenGeometry(cell_phys);
  makeCellTop(hliq); // change liquid level in cell
  G4GeometryManager::GetInstance()->CloseGeometry(cell_phys);
}

void detector_UIUCCryo::SetTemperature(G4double temperature)
{
// this method assumes the conditions are consistent with bulk liquid formation

  mix->SetT(temperature); // temperature (K)
  // recalculate equilibrium concentration, liquid height
  SetMolesHelium(mix->Getn4(), mix->Getn3());

  if(cell_log) {
    diffusionMaterial *mat = (diffusionMaterial*)(cell_log->GetMaterial());
    mat->SetTemperature(temperature);
  }
  if(celltop_log) {
    diffusionMaterial *mat2 = (diffusionMaterial*)(celltop_log->GetMaterial());
    G4cout << "celltop pressure = " << mix->Getp3() + mix->Getp4() << " torr" << G4endl;
    mat2->SetTemperature(temperature);
    mat2->SetPressure(mix->Getp3()+mix->Getp4());
  }
}

void detector_UIUCCryo::SetPressure(G4double pressure)
{
// don't allow pressure to be set like this: it will be set according
// to the temperature.
#if 0
  if(cell_log) {
    diffusionMaterial *mat = (diffusionMaterial*)(cell_log->GetMaterial());
    mat->SetPressure(pressure);
  }
  if(celltop_log) {
    diffusionMaterial *mat2 = (diffusionMaterial*)(celltop_log->GetMaterial());
    mat2->SetPressure(pressure);
  }
#endif
}

void detector_UIUCCryo::ConstructCell()
{
//------------------------------ measurement cell
// The cell is cylindrical with axis along the z-axis.
// The holding field H_0 defines the z-axis (vertical in the
// UIUC cryo experiment).

// material that the volume is made of
  diffusionMaterial* cell_mat = new diffusionMaterial("LHe4");

  innerR = 0*cm;
  outerR = 0.5*5./8*2.54*cm;  // cell radius
  halfheight = 0.5*3.375*2.54*cm;  // half-height of the cell
  startPhi = 0.*deg;
  deltaPhi = 360.*deg;

  zOffset = 0.0*cm; // amount to shift cell in z direction

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

  G4VisAttributes* cell_att = new G4VisAttributes(G4Colour(0.5,0.5,1.0));
  cell_log->SetVisAttributes(cell_att);

// set outer limits used by dressedSpinPrimaryGeneratorAction::ChooseInitialPosition()
// to find a starting point within the cell.
// (ToDo: change this to use G4VSolid::CalculateExtent)
  fCellXmin = -outerR;
  fCellXmax = outerR;
  fCellYmin = -outerR;
  fCellYmax = outerR;
  fCellZmin = -halfheight + zOffset;
  fCellZmax = halfheight + zOffset;
  //------------------------------------------------------------------


//  mix->SetV(pi*outerR*outerR*2*halfheight/cm3); // total volume of cell (cc)
  mix->SetV(cell_tubs->GetCubicVolume()/cm3); // total volume of cell
  G4cout << "Cell volume = " << mix->GetV() << " cm3" << G4endl;

  // default to half-full cell
  G4double n4 = 0.5*mix->GetV()/mix->GetVm();
  G4double n3 = 1e-6*n4; // on the order of natural concentation
  SetMolesHelium(n4, n3);
}

void detector_UIUCCryo::makeCellTop(G4double height_of_liquid)
{
//--------------- part of cell that contains gas not liquid
  G4double celltop_height = 2*halfheight - height_of_liquid; // total length without liquid

  if(!celltop_phys) {
    G4Tubs* celltop_tubs = new G4Tubs("celltop_tubs",innerR,outerR,
              celltop_height/2.,startPhi,deltaPhi);

// material that the volume is made of
    diffusionMaterial* celltop_mat = new diffusionMaterial("He3Gas");
    celltop_mat->SetMeanFreePath(100*cm);

    celltop_log = new G4LogicalVolume(celltop_tubs,celltop_mat,
              "celltop_log",0,0,0);

    celltop_phys = new G4PVPlacement(0,
              G4ThreeVector(0,0,halfheight - celltop_height/2),
              celltop_log,"celltop",cell_log,false,0);
  } else {
    G4Tubs* celltop_tubs = (G4Tubs*)(celltop_log->GetSolid());
    celltop_tubs->SetZHalfLength(celltop_height/2.);
    celltop_phys->SetTranslation(G4ThreeVector(0,0,halfheight - celltop_height/2.));
  }

}

