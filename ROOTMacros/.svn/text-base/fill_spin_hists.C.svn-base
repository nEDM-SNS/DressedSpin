{
  gROOT->LoadMacro("libSpinsTree.so");

  TChain *chain = new TChain("Spins");
  char str[200];
  for(int i=0; i < 200; i++) {
    sprintf(str, "/data/npluser/smclayto/DressedSpin/nEDMCell/ROOT/sim_X0p0_T1_run%d.root", i);
    chain->Add(str);
  }
  TFile fout("/data/npluser/smclayto/DressedSpin/nEDMCell/sum_sim_X0p0_T1.root","RECREATE");

  SpinsTree tree(chain);
  tree.SetFieldMapFile(0); // 0 means use default file
  tree.MakeHists();
  tree.Loop();

  fout.cd();
  tree.hSx->Write();
  tree.hSy->Write();
  tree.hSz->Write();
  tree.hx->Write();
  tree.hy->Write();
  tree.hz->Write();
  tree.hSampledBx->Write();
  tree.hSampledBy->Write();
  tree.hSampledBz->Write();
  fout.Close();

}

