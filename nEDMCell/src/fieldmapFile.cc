#include "fieldmapFile.hh"

#include <stdio.h>
#include "TDirectory.h"
#include "TFile.h"

#ifdef ROOTMacros
ClassImp(fieldmapFile)
#include <iostream>
#define G4cout std::cout
#define G4endl std::endl
#endif

fieldmapFile::fieldmapFile(char *input_filename)
{
  if((strlen(input_filename) > 5) &&
     (strncmp(".root",input_filename + strlen(input_filename) - 5, 5) == 0)) {

    TDirectory *savedir = gDirectory;

    TFile mapHistFile(input_filename);
    if(mapHistFile.IsZombie()) {
      G4cout << "fieldmapFile error: map hist file not found: " << input_filename << G4endl;
      exit(1); // probably not the best way to quit
    }

    hBx = (TH3*)mapHistFile.Get("hBx");
    hBy = (TH3*)mapHistFile.Get("hBy");
    hBz = (TH3*)mapHistFile.Get("hBz");
    hFieldPars = (TH1*)mapHistFile.Get("hFieldPars");
    if(!hBx || !hBy || !hBz || !hFieldPars) { // make sure hists were found in file
      G4cout << "fieldmapFile error: hBx,hBy, hBz or hFieldPars not found in file "
             << mapHistFile.GetName() << G4endl;
      exit(2); // probably not the best way to quit
    }

    // don't save these to the output ROOT file,
    // and keep them in memory when mapHistFile closes
    hBx->SetDirectory(0);
    hBy->SetDirectory(0);
    hBz->SetDirectory(0);
    hFieldPars->SetDirectory(0);
    mapHistFile.Close();

    savedir->cd(); // restore current directory to output file

  } else { // assume it's an ascii file
    double xmin = -14.0;
    double xmax = -4.0;
    double dx = 2.0;
    double ymin = -7.2;
    double ymax = 7.2;
    double dy = 3.6;
    double zmin = -24.0;
    double zmax = 24.0;
    double dz = 12.0;

    int nbinx = int((xmax - xmin)/dx + 0.5);
    int nbiny = int((ymax - ymin)/dy + 0.5);
    int nbinz = int((zmax - zmin)/dz + 0.5);

    hBx = new TH3D("hBx","hBx",nbinx,xmin,xmax,nbiny,ymin,ymax,nbinz,zmin,zmax);
    hBy = new TH3D("hBy","hBy",nbinx,xmin,xmax,nbiny,ymin,ymax,nbinz,zmin,zmax);
    hBz = new TH3D("hBz","hBz",nbinx,xmin,xmax,nbiny,ymin,ymax,nbinz,zmin,zmax);
    hFieldPars = new TH1D("hFieldPars","hFieldPars",1,0.5,1.5);

    read_fieldmap(input_filename,hBx,hBy,hBz);
    // normalization based on field in x-direction.
    hFieldPars->SetBinContent(1, hBx->Integral()/(hBx->GetNbinsX()*hBx->GetNbinsY()*hBx->GetNbinsZ()));

    // don't save these to the output ROOT file
    hBx->SetDirectory(0);
    hBy->SetDirectory(0);
    hBz->SetDirectory(0);
    hFieldPars->SetDirectory(0);
  }

  // fB0x_norm should be set to the volume-average of Bx over the cell volume.
  fB0x_norm = hFieldPars->GetBinContent(1);

  fScaleDevs = 1.0; // amount to scale deviations from ideal field
}

fieldmapFile::~fieldmapFile()
{
}

void fieldmapFile::read_fieldmap(char *filename, TH3* hBx, TH3* hBy, TH3* hBz)
{
// hBx, hBy, hBz should have exactly the same binning, which should be
// appropriate for the input file.

  double x,y,z,Bx,By,Bz;

  FILE *fdat = fopen(filename, "r");

  int i = 0;
  while(1) {
    int retval = fscanf(fdat, "%lf %lf %lf %lE %lE %lE\n",
            &x, &y, &z, &Bx, &By, &Bz);
    if(i%100000 == 0) printf("%0.1f %0.1f %0.1f %e %e %e\n", x, y, z, Bx, By, Bz);
    ++i;

    int binx = hBx->GetXaxis()->FindBin(x);
    int biny = hBx->GetYaxis()->FindBin(y);
    int binz = hBx->GetZaxis()->FindBin(z);
    hBx->SetBinContent(binx, biny, binz, Bx);
    hBy->SetBinContent(binx, biny, binz, By);
    hBz->SetBinContent(binx, biny, binz, Bz);

    if(retval == EOF) break;
  }

  fclose(fdat);
}

#ifdef ROOTMacros
// use a different prototype if compiled for a ROOT session
void fieldmapFile::GetFieldVector(Float_t x, Float_t y, Float_t z,
 Double_t *pBx, Double_t *pBy, Double_t *pBz)
{
  double vec[3];
  vec[0] = x/10; // x,y,z in mm
  vec[1] = y/10;
  vec[2] = z/10;
#else
G4ThreeVector fieldmapFile::GetFieldVector(const G4ThreeVector &p)
{
  double vec[3];
  vec[0] = p.x()/cm;
  vec[1] = p.y()/cm;
  vec[2] = p.z()/cm;
#endif

#if 1
  // BlochEq code is extremely slow (or stuck) without interpolation
  double Bx = trilinearInterpolate(hBx, vec);
  double By = trilinearInterpolate(hBy, vec);
  double Bz = trilinearInterpolate(hBz, vec);

#else
  int binx = hBx->GetXaxis()->FindBin(vec[0]);
  int biny = hBx->GetYaxis()->FindBin(vec[1]);
  int binz = hBx->GetZaxis()->FindBin(vec[2]);
  double Bx = hBx->GetBinContent(binx,biny,binz);
  double By = hBy->GetBinContent(binx,biny,binz);
  double Bz = hBz->GetBinContent(binx,biny,binz);
#endif

  G4double normalized_Bx = Bx/fB0x_norm;
  G4double normalized_By = By/fB0x_norm;
  G4double normalized_Bz = Bz/fB0x_norm;

  // scale deviations from ideal values: normalized B_ideal = (1,0,0)
  G4double val_x = 1 + fScaleDevs*(normalized_Bx - 1);
  G4double val_y = fScaleDevs*normalized_By;
  G4double val_z = fScaleDevs*normalized_Bz;

#if ROOTMacros
  *pBx = val_x;
  *pBy = val_y;
  *pBz = val_z;
#else
  return G4ThreeVector(val_x, val_y, val_z);
#endif
}

G4double fieldmapFile::trilinearInterpolate(TH3* hist, const double vec[3])
{
  int binx = hist->GetXaxis()->FindBin(vec[0]);
  int biny = hist->GetYaxis()->FindBin(vec[1]);
  int binz = hist->GetZaxis()->FindBin(vec[2]);
  // the bin center should be the low side of the interval
  if(hist->GetXaxis()->GetBinCenter(binx) > vec[0]) --binx;
  if(hist->GetYaxis()->GetBinCenter(biny) > vec[1]) --biny;
  if(hist->GetZaxis()->GetBinCenter(binz) > vec[2]) --binz;

  double dx = hist->GetXaxis()->GetBinWidth(binx);
  double dy = hist->GetYaxis()->GetBinWidth(biny);
  double dz = hist->GetZaxis()->GetBinWidth(binz);
  // fractional distance between the vertices
  double xf = (vec[0] - hist->GetXaxis()->GetBinCenter(binx))/dx;
  double yf = (vec[1] - hist->GetYaxis()->GetBinCenter(biny))/dy;
  double zf = (vec[2] - hist->GetZaxis()->GetBinCenter(binz))/dz;

  double Vxyz = 0;
  for(int i=0; i < 2; i++) {
    double xw = 1 - xf;
    if(i == 1) xw = xf;
    for(int j=0; j < 2; j++) {
      double yw = 1 - yf;
      if(j == 1) yw = yf;
      for(int k=0; k < 2; k++) {
        double zw = 1 - zf;
        if(k == 1) zw = zf;
        double val = hist->GetBinContent(binx+i,biny+j,binz+k);
        Vxyz += val*xw*yw*zw;
      } // for k
    } // for j
  } // for i

  return Vxyz;
}

