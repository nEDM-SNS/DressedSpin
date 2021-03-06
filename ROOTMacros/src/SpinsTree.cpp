#define SpinsTree_cxx
#include "SpinsTree.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TMath.h>

ClassImp(SpinsTree)

void SpinsTree::SetFieldMapFile(char* filename)
{
  if(filename) holdingFieldMap = new fieldmapFile(filename);
  else holdingFieldMap = new fieldmapFile("/home/ehl7/fieldmaps/n34-field-10mgauss.root");
}

void SpinsTree::SetHoldingFieldDeviationScaling(double factor)
{
  if(holdingFieldMap) holdingFieldMap->SetScaleDevsFactor(factor);
}


void SpinsTree::MakeHists(TFile *outFile)
{
  fChain->GetEntry(0);
  Double_t tmin = t;
  fChain->GetEntry(1);
  fDt = t - tmin;
  fChain->GetEntry(fChain->GetEntries() - 1);
  Double_t tmax = t;
  Int_t nbins = Int_t((tmax - tmin)/fDt + 0.5) + 1;

  hSx = new TH1D("hSx","x-component of spin vs. time",nbins,tmin-fDt/2,tmax+fDt/2);
  hSy = new TH1D("hSy","y-component of spin vs. time",nbins,tmin-fDt/2,tmax+fDt/2);
  hSz = new TH1D("hSz","z-component of spin vs. time",nbins,tmin-fDt/2,tmax+fDt/2);

  hPhaseVsTime = new TH2D("hPhaseVsTime","#Delta#phi of the transverse spin",
      999,-TMath::Pi(),TMath::Pi(), 101, -5., 1005.);
  hPhaseVsTime->GetXaxis()->SetTitle("#Delta#phi");
  hPhaseVsTime->GetYaxis()->SetTitle("Time (s)");

//  double xmin = -127.;
//  double xmax = -49.;
  double xmin = 49.;
  double xmax = 127.;
  double ymin = -50.;
  double ymax = 50.;
  double zmin = -200.;
  double zmax = 200.;
  int nbinsx = int(xmax - xmin + 0.5);
  int nbinsy = int(ymax - ymin + 0.5);
  int nbinsz = int(zmax - zmin + 0.5);
  hx = new TH1D("hx","x-position of particle",nbinsx,xmin,xmax);
  hy = new TH1D("hy","y-position of particle",nbinsy,ymin,ymax);
  hz = new TH1D("hz","z-position of particle",nbinsz,zmin,zmax);
  hxyz = new TH3D("hxyz","position of particle",
            nbinsx,xmin,xmax,nbinsy,ymin,ymax,nbinsz,zmin,zmax);

  if(holdingFieldMap) {
    hSampledBx = new TH1D("hSampledBx","hSampledBx",20000,0.998, 1.002);
    hSampledBy = new TH1D("hSampledBy","hSampledBy",20000,-0.002, 0.002);
    hSampledBz = new TH1D("hSampledBz","hSampledBz",20000,-0.002, 0.002);
  }

  if(outFile) {
    hSx->SetDirectory(outFile);
    hSy->SetDirectory(outFile);
    hSz->SetDirectory(outFile);
    hPhaseVsTime->SetDirectory(outFile);
    hx->SetDirectory(outFile);
    hy->SetDirectory(outFile);
    hz->SetDirectory(outFile);
    hxyz->SetDirectory(outFile);
    hSampledBx->SetDirectory(outFile);
    hSampledBy->SetDirectory(outFile);
    hSampledBz->SetDirectory(outFile);
  }

}

void SpinsTree::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Double_t tprev = -1000;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      hSx->Fill(t, Sx);
      hSy->Fill(t, Sy);
      hSz->Fill(t, Sz);
      hx->Fill(x);
      hy->Fill(y);
      hz->Fill(z);
      hxyz->Fill(x,y,z);

      int tbin = hPhaseVsTime->GetYaxis()->FindBin(t);
      double t_mid = hPhaseVsTime->GetYaxis()->GetBinCenter(tbin);
      if(t >= t_mid && t < t_mid + fDt) {
        double phi_spin = TMath::ATan2(Sy, Sz);
        double phi_temp = fgamma*fAvgB*t;
        double phi_avg = 2*TMath::Pi()*(phi_temp/(2*TMath::Pi()) - TMath::Floor(phi_temp/(2*TMath::Pi())));
        double deltaphi = phi_spin - phi_avg;
        if(deltaphi < -TMath::Pi()) deltaphi += 2*TMath::Pi();
        hPhaseVsTime->Fill(deltaphi, t);
      }

      if(holdingFieldMap) {
        Double_t Bx,By,Bz;
        holdingFieldMap->GetFieldVector(x,y,z,&Bx,&By,&Bz);
        hSampledBx->Fill(Bx);
        hSampledBy->Fill(By);
        hSampledBz->Fill(Bz);
      }

      if(t < tprev) std::cout << "jentry = " << jentry << std::endl;
      tprev = t;
   }
}

