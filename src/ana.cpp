//my
#include "ana.hh"

//root
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TGraph.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TRandom3.h>

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

void ana::Loop(TString histOut){
  //
  TH1D *h1_year = new TH1D("h1_year","h1_year", 7, 2019, 2025);
  TH1D *h1_month = new TH1D("h1_month","h1_month", 14, 0, 13);
  TH1D *h1_day = new TH1D("h1_day","h1_day", 33, 0, 32);
  TH1D *h1_ver = new TH1D("h1_ver","h1_ver", 3, 0, 3);
  TH1D *h1_nSubRun = new TH1D("h1_nSubRun","h1_nSubRun", 1000, 0, 1000);
  //  
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //
    if(jentry%10000000 == 0)
      cout<<jentry<<endl;
    //
    h1_year->Fill(year);
    h1_month->Fill(month);
    h1_day->Fill(day);
    h1_ver->Fill(ver);
    h1_nSubRun->Fill(nSubRun);    
  }
  TFile* rootFile = new TFile(histOut.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<histOut.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<histOut.Data()<<endl;
  //
  h1_year->Write();
  h1_month->Write();
  h1_day->Write();
  h1_ver->Write();
  h1_nSubRun->Write();
  //
  rootFile->Close();
}
