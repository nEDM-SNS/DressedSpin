#include "fieldMap.hh"

fieldMap::fieldMap()
{
  fMessenger = new fieldMap_messenger(this);

  hBfieldMap_Norm = 0;
  hBfieldMap_x = 0;
  hBfieldMap_y = 0;
  hBfieldMap_z = 0;
  hBfieldGradHzx = 0;
  hBfieldGradHzy = 0;
  hBfieldGradHzz = 0;
}

fieldMap::~fieldMap()
{
  delete fMessenger;
}

#include "G4RunManager.hh"

void fieldMap::Compute()
{
  BlochEq* blochEq = fPhysicsList->GetNeutralSpinRotation()->GetBlochEqObj();

  if( !hBfieldMap_Norm ) {
    G4double xmin = fDetector->GetCellXmin();
    G4double xmax = fDetector->GetCellXmax();
    G4double ymin = fDetector->GetCellYmin();
    G4double ymax = fDetector->GetCellYmax();
    G4double zmin = fDetector->GetCellZmin();
    G4double zmax = fDetector->GetCellZmax();

    hBfieldMap_Norm = new TH3D("hBfieldMap_Norm","Indicates if bin is inside cell",
          100, xmin/cm, xmax/cm, 100, ymin/cm, ymax/cm, 100, zmin/cm, zmax/cm);
    hBfieldMap_Norm->GetXaxis()->SetTitle("x (cm)");
    hBfieldMap_Norm->GetYaxis()->SetTitle("y (cm)");
    hBfieldMap_Norm->GetZaxis()->SetTitle("z (cm)");
    hBfieldMap_x = (TH3*)hBfieldMap_Norm->Clone("hBfieldMap_x");
    hBfieldMap_x->SetTitle("x-component of net B-field");
    hBfieldMap_y = (TH3*)hBfieldMap_Norm->Clone("hBfieldMap_y");
    hBfieldMap_y->SetTitle("y-component of net B-field");
    hBfieldMap_z = (TH3*)hBfieldMap_Norm->Clone("hBfieldMap_z");
    hBfieldMap_z->SetTitle("z-component of net B-field");

    hBfieldGradHzx = (TH3*)hBfieldMap_Norm->Clone("hBfieldGradHzx");
    hBfieldGradHzx->SetTitle("x-component of grad H_{z}");
    hBfieldGradHzy = (TH3*)hBfieldMap_Norm->Clone("hBfieldGradHzy");
    hBfieldGradHzy->SetTitle("y-component of grad H_{z}");
    hBfieldGradHzz = (TH3*)hBfieldMap_Norm->Clone("hBfieldGradHzz");
    hBfieldGradHzz->SetTitle("z-component of grad H_{z}");
  }

  double dx = 0.1*hBfieldMap_x->GetXaxis()->GetBinWidth(1)*cm;
  double dy = 0.1*hBfieldMap_x->GetYaxis()->GetBinWidth(1)*cm;
  double dz = 0.1*hBfieldMap_x->GetZaxis()->GetBinWidth(1)*cm;
  for(int binz=1; binz <= hBfieldMap_x->GetNbinsZ(); binz++) {
    double z = hBfieldMap_x->GetZaxis()->GetBinCenter(binz)*cm;
    for(int biny=1; biny <= hBfieldMap_x->GetNbinsY(); biny++) {
      double y = hBfieldMap_x->GetYaxis()->GetBinCenter(biny)*cm;
      for(int binx=1; binx <= hBfieldMap_x->GetNbinsX(); binx++) {
        double x = hBfieldMap_x->GetXaxis()->GetBinCenter(binx)*cm;
        G4ThreeVector p = G4ThreeVector(x, y, z);

        if(fGenAction->PointIsInCell(p)) hBfieldMap_Norm->SetBinContent(binx,biny,binz,1);
        else hBfieldMap_Norm->SetBinContent(binx,biny,binz,0);

        G4ThreeVector B = blochEq->Bfield(0, p);
        hBfieldMap_x->SetBinContent(binx, biny, binz, B.x()/gauss);
        hBfieldMap_y->SetBinContent(binx, biny, binz, B.y()/gauss);
        hBfieldMap_z->SetBinContent(binx, biny, binz, B.z()/gauss);

        G4ThreeVector B_lowx = blochEq->Bfield(0, G4ThreeVector(x-dx,y,z));
        G4ThreeVector B_highx = blochEq->Bfield(0, G4ThreeVector(x+dx,y,z));
        G4ThreeVector B_lowy = blochEq->Bfield(0, G4ThreeVector(x,y-dy,z));
        G4ThreeVector B_highy = blochEq->Bfield(0, G4ThreeVector(x,y+dy,z));
        G4ThreeVector B_lowz = blochEq->Bfield(0, G4ThreeVector(x,y,z-dz));
        G4ThreeVector B_highz = blochEq->Bfield(0, G4ThreeVector(x,y,z+dz));

        G4ThreeVector dBdx = (B_highx - B_lowx)/(2*dx);
        G4ThreeVector dBdy = (B_highy - B_lowy)/(2*dy);
        G4ThreeVector dBdz = (B_highz - B_lowz)/(2*dz);

        G4ThreeVector gradBz = G4ThreeVector(dBdx.z(),dBdy.z(),dBdz.z());

        hBfieldGradHzx->SetBinContent(binx,biny,binz, gradBz.x()/gauss*cm);
        hBfieldGradHzy->SetBinContent(binx,biny,binz, gradBz.y()/gauss*cm);
        hBfieldGradHzz->SetBinContent(binx,biny,binz, gradBz.z()/gauss*cm);
      } // for binx
    } // for biny
  } // for binz


}



//***********************************************************************
// messenger class so we can change paramters with a macro command


#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4ios.hh"

fieldMap_messenger::fieldMap_messenger(fieldMap* obj)
  :fFieldMap(obj)
{
  dirFieldMap = new G4UIdirectory("/FieldMap/");
  dirFieldMap->SetGuidance("FieldMap commands.");

  computeCmd = new G4UIcmdWithoutParameter("/FieldMap/Compute",this);
  computeCmd->SetGuidance("create and fill field map histograms");

}

fieldMap_messenger::~fieldMap_messenger()
{
  delete computeCmd;
  delete dirFieldMap;
}

void fieldMap_messenger::SetNewValue(G4UIcommand * command,G4String newValues)
{
  if( command==computeCmd)
  { fFieldMap->Compute(); }
}

G4String fieldMap_messenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;

//  if( command==gradientCmd )
//  { cv = gradientCmd->ConvertToString(ffieldMap->GetGradient()); }

  return cv;
}


