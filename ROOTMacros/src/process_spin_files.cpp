l#include <string.h>
#include <TH1.h>
#include <TROOT.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <TFile.h>
#include <TList.h>
#include <TKey.h>
#include <TClass.h>
#include "SpinsTree.h"
#include <TChainElement.h>

void process_spin_files(Char_t* dirName = ".", Char_t* outFileName = "./added.root", Char_t* listFileName = "./filelist.txt")
{
  printf("Input directory = %s\n",dirName);
  printf("Output file     = %s\n",outFileName);

  TFile* outFile = new TFile(outFileName,"RECREATE");

  std::ifstream runlist_file(listFileName);
  if(!runlist_file.is_open()) {
    printf("can't open runlist file\n");
    return;
  }

  // argument is name of the TTree in input files
  TChain *chain = new TChain("Spins");

  Char_t name[200];
  char line[200];
  while(!runlist_file.getline(line, 200).eof()) {
    // get rid of newline
    int len = strlen(line);
    if(len <= 1 || len >= 200) continue;
    line[len] = '\0';
    sprintf(name, "%s/%s", dirName, line);
    printf("Adding file %s\n",name);

    chain->Add(name); // file not opened here by default
  }

  TObjArray *fileElements = chain->GetListOfFiles();
  TIter next(fileElements);
  TChainElement *chEl = 0;
  while( chEl = (TChainElement*)next() ) {
    TFile inFile(chEl->GetTitle());
    printf("inFile: %s\n", inFile.GetName());

    // the list of stuff that we've already done
    Char_t **histsDone = new Char_t *[10000]; 
    Int_t numHistsDone = 0;

    TList* lok = inFile.GetListOfKeys();
    TIter* nextkey = new TIter(lok);
    // loop over all keys in the files
    TKey *key;
    while ((key = (TKey*)nextkey->Next()))
    {
      TObject* obj = key->ReadObj();
      if (!(obj->IsA()->InheritsFrom("TH1"))) continue; // the object isn't a histo
      TH1* newHist = (TH1*)obj;
      const Char_t* histName = newHist->GetName();

      for(Int_t i = 0; i < numHistsDone; i++)
      {
        if(!strcmp(histsDone[i], histName))
        {
          continue;
        }
      }

      Char_t *s = new Char_t[strlen(histName)+1];  
      strcpy(s, histName);
      histsDone[numHistsDone] = s;
      numHistsDone++;


      TH1* oldHist = (TH1*)outFile->Get(histName);
      if(newHist->Integral() >= 0 || newHist->Integral() < 0) // exclude NaN
      {
        if (!oldHist)
        {
          // printf("%s doesn't exist yet\n",histName);
//          outFile->cd();
//          obj->Write(key->GetName());
//          inFile->cd();

            newHist->SetDirectory(outFile);
        }
        else
        {
          // printf("Adding to %s\n",histName);
          oldHist->Add(newHist);
          delete newHist;
        }
      }
    }

    for(Int_t i = 0; i < numHistsDone; i++)
    {
      delete[] histsDone[i];
    }
    delete[] histsDone;
  } // for iirun

  // process trees from all files
  SpinsTree tree(chain);
  tree.SetFieldMapFile("/home/ehl7/fieldmaps/n34-field-10mgauss.root");
//  tree.SetFieldMapFile("/home/ehl7/fieldmaps/negx-jedmod_truescale_cell_B=0.01G.root");
  tree.SetAvgB(0.01); // nominal Bx field in gauss
  tree.SetGyromagneticRatio(-20393.963); // rad/gauss/sec (should match the value in TBlochEq.cpp)
  tree.MakeHists(outFile);
  tree.Loop();


  outFile->Write();
  outFile->Close();

  runlist_file.close();
}


void show_usage()
{
  printf("process_spin_files [-d directory] [-o outfilename] [-l listfile]\n");
  return;
}

int main(int argc, char **argv)
{
  if(argc < 3) {
    show_usage();
    return 1;
  }
  if((argc > 1) && (strcmp(argv[1],"-h") == 0)) {
    show_usage();
    return 2;
  }

  Char_t dirname[256];
  Char_t outfilename[256];
  Char_t listfilename[256];

  sprintf(dirname, ".");
  sprintf(outfilename, "./added.root");

  int iarg = 1;
  while(iarg < argc-1) {
    if(strcmp(argv[iarg],"-d") == 0) {
      strncpy(dirname,argv[iarg+1],256);
    } else if(strcmp(argv[iarg],"-o") == 0) {
      strncpy(outfilename,argv[iarg+1],256);
    } else if(strcmp(argv[iarg],"-l") == 0) {
      strncpy(listfilename,argv[iarg+1],256);
    } else {
      printf("unrecognized option: %s\n", argv[iarg]);
      show_usage();
      return 3;
    }
    iarg += 2;
  }
  printf("dirname: %s\n", dirname);
  printf("outfilename: %s\n", outfilename);
  printf("listfilename: %s\n", listfilename);

  process_spin_files(dirname, outfilename, listfilename);

  return 0;
}

