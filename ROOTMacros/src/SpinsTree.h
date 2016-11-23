//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 11 10:19:52 2008 by ROOT version 5.18/00
// from TTree Spins/Spin vectors
// found on file: /data/npluser/smclayto/DressedSpin/nEDMCell/ROOT/sim_X0p0_run0.root
//////////////////////////////////////////////////////////

#ifndef SpinsTree_h
#define SpinsTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TObject.h>
#include <TH2.h>
#include <TH3.h>

#include "fieldmapFile.hh"

class SpinsTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        t;
   Float_t         x;
   Float_t         y;
   Float_t         z;
   Float_t         Sx;
   Float_t         Sy;
   Float_t         Sz;

   // List of branches
   TBranch        *b_t;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_Sx;   //!
   TBranch        *b_Sy;   //!
   TBranch        *b_Sz;   //!

   SpinsTree(TTree *tree=0);
   virtual ~SpinsTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   void MakeHists(TFile *outFile = 0);
   void SetAvgB(double val) { fAvgB = val; } // in gauss
   void SetGyromagneticRatio(double val) { fgamma = val; } // in rad/gauss/sec
   double fDt; // time interval between Fills
   double fAvgB;
   double fgamma;
   TH1 *hSx;
   TH1 *hSy;
   TH1 *hSz;
   TH1 *hx;
   TH1 *hy;
   TH1 *hz;
   TH3 *hxyz;

   TH1 *htreetest;

   TH2 *hPhaseVsTime;

   fieldmapFile* holdingFieldMap;
   void SetFieldMapFile(char* filename);
   void SetHoldingFieldDeviationScaling(double factor);
   TH1 *hSampledBx;
   TH1 *hSampledBy;
   TH1 *hSampledBz;

   ClassDef(SpinsTree, 1)
};

#endif

#ifdef SpinsTree_cxx
SpinsTree::SpinsTree(TTree *tree) : holdingFieldMap(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data/npluser/smclayto/DressedSpin/nEDMCell/ROOT/sim_X0p0_run0.root");
      if (!f) {
         f = new TFile("/data/npluser/smclayto/DressedSpin/nEDMCell/ROOT/sim_X0p0_run0.root");
      }
      tree = (TTree*)gDirectory->Get("Spins");

   }
   Init(tree);
}

SpinsTree::~SpinsTree()
{
   if(holdingFieldMap) delete holdingFieldMap;
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SpinsTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SpinsTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SpinsTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("t", &t, &b_t);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("Sx", &Sx, &b_Sx);
   fChain->SetBranchAddress("Sy", &Sy, &b_Sy);
   fChain->SetBranchAddress("Sz", &Sz, &b_Sz);
   Notify();
}

Bool_t SpinsTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void SpinsTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SpinsTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SpinsTree_cxx
