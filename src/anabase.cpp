//my
#include "anabase.hh"

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

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

anabase::anabase(TString fileList) : fChain(0) 
{
  ifstream indata;
  TString rootFileName;
  //TChain *theChain = new TChain("arich");
  TChain *theChain = new TChain(treeName.Data());
  indata.open(fileList.Data()); 
  assert(indata.is_open());  
  while (indata  >> rootFileName ){
    if(indata.eof()){
      std::cout<<"EOF"<<std::endl;
      break;
    }
    cout<<"        adding "<<rootFileName<<endl;
    theChain->Add(rootFileName.Data(),-1);
  }
  indata.close();
  Init(theChain);
}

anabase::anabase(TString inFileName, Int_t keyID) : fChain(0) 
{
  if(keyID == 1){
    ifstream indata;
    //TChain *theChain = new TChain("T");
    TChain *theChain = new TChain(treeName.Data());
    cout<<"        adding "<<inFileName<<endl;
    theChain->Add(inFileName.Data(),-1);
    Init(theChain);
  }
  else
    assert(0);
}

void anabase::tGraphInit(TGraph *gr[nChannels], TString grName, TString grTitle){
  Int_t i;
  TString grNameh;
  TString grTitleh;
  for(i = 0;i<nChannels;i++){
    grNameh = grName; grNameh += "_"; grNameh += "ch_"; grNameh += i;
    grTitleh = grTitle; grTitleh += " "; grTitleh += "ch "; grTitleh += i;
    gr[i] = new TGraph();
    gr[i]->SetTitle(grTitleh.Data());
    gr[i]->SetName(grNameh.Data());
  }
}

void anabase::h1D1Init(TH1D *h1D1[nChannels],TString h1name, TString h1Title,
		      Int_t Nbin, Float_t Vmin, Float_t Vmax){
  Int_t i;
  TString h1nameh;
  TString h1Titleh;
  for(i = 0;i<nChannels;i++){    
    h1nameh = h1name; h1nameh += "_"; h1nameh += "ch_"; h1nameh += i;
    h1Titleh = h1Title; h1nameh += " "; h1Titleh += "ch "; h1Titleh += i;
    h1D1[i] = new TH1D(h1nameh.Data(), h1Titleh.Data(),
                       Nbin, Vmin, Vmax);
  }
}

void anabase::h2D2Init(TH2D *h2D1[nChannels],TString h2name, TString h2Title,
		      Int_t Nbin1, Float_t Vmin1, Float_t Vmax1,
		      Int_t Nbin2, Float_t Vmin2, Float_t Vmax2){
  Int_t i;
  TString h2nameh;
  TString h2Titleh;
  for(i = 0;i<nChannels;i++){    
    h2nameh = h2name; h2nameh += "_"; h2nameh += "ch_"; h2nameh += i;
    h2Titleh = h2Title; h2nameh += " "; h2Titleh += "ch "; h2Titleh += i;
    h2D1[i] = new TH2D(h2nameh.Data(), h2Titleh.Data(),
                       Nbin1, Vmin1, Vmax1,
		       Nbin2, Vmin2, Vmax2);
  }  
}

void anabase::tProfInit(TProfile *tprof[nChannels],TString prname, TString prTitle,
		       Int_t Nbin, Float_t Vmin, Float_t Vmax){
  Int_t i;
  TString prnameh;
  TString prTitleh;
  for(i = 0;i<nChannels;i++){    
    prnameh = prname; prnameh += "_"; prnameh += "ch_"; prnameh += i;
    prTitleh = prTitle; prnameh += " "; prTitleh += "ch "; prTitleh += i;
    tprof[i] = new TProfile(prnameh.Data(), prTitleh.Data(), Nbin, Vmin, Vmax,"");
  }
}

double anabase::getUnixTimeFromTime(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec){
  //time_t timer;
  struct tm y2k = {0};
  y2k.tm_year = d_year - 1900; y2k.tm_mon = d_month-1; y2k.tm_mday = d_day;
  y2k.tm_hour = d_hour;   y2k.tm_min = d_min; y2k.tm_sec = d_sec;
  return difftime(mktime(&y2k),0);
}

anabase::~anabase(){
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void anabase::Loop(TString histOut){
}

Int_t anabase::GetEntry(Long64_t entry){
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t anabase::LoadTree(Long64_t entry){
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void anabase::Init(TTree *tree){
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
  //fChain->SetBranchAddress("evt", &evt, &b_evt);
  //fChain->SetBranchAddress("run", &run, &b_run);
  //fChain->SetBranchAddress("pValue", &pValue, &b_pValue);
  //...
  //...
  //
  //---------------------------------------------------
  // ADD HERE :
   fChain->SetBranchAddress("run_id", &run_id, &b_run_id);
   fChain->SetBranchAddress("year", &year, &b_year);
   fChain->SetBranchAddress("month", &month, &b_month);
   fChain->SetBranchAddress("day", &day, &b_day);
   fChain->SetBranchAddress("ver", &ver, &b_ver);
   fChain->SetBranchAddress("nSubRun", &nSubRun, &b_nSubRun);
   fChain->SetBranchAddress("nMuonsPerRun", &nMuonsPerRun, &b_nMuonsPerRun);
   fChain->SetBranchAddress("event_id", &event_id, &b_event_id);
   fChain->SetBranchAddress("event_time", &event_time, &b_event_time);
   fChain->SetBranchAddress("mc_energy", &mc_energy, &b_mc_energy);
   fChain->SetBranchAddress("ring_size", &ring_size, &b_ring_size);
   fChain->SetBranchAddress("size_outside", &size_outside, &b_size_outside);
   fChain->SetBranchAddress("ring_center_x", &ring_center_x, &b_ring_center_x);
   fChain->SetBranchAddress("ring_center_y", &ring_center_y, &b_ring_center_y);
   fChain->SetBranchAddress("ring_radius", &ring_radius, &b_ring_radius);
   fChain->SetBranchAddress("ring_width", &ring_width, &b_ring_width);
   fChain->SetBranchAddress("good_ring", &good_ring, &b_good_ring);
   fChain->SetBranchAddress("muon_efficiency", &muon_efficiency, &b_muon_efficiency);
   fChain->SetBranchAddress("ring_containment", &ring_containment, &b_ring_containment);
   fChain->SetBranchAddress("ring_completeness", &ring_completeness, &b_ring_completeness);
   fChain->SetBranchAddress("impact_parameter", &impact_parameter, &b_impact_parameter);
   fChain->SetBranchAddress("impact_x_array", &impact_x_array, &b_impact_x_array);
   fChain->SetBranchAddress("impact_y_array", &impact_y_array, &b_impact_y_array);
   fChain->SetBranchAddress("radial_stdev", &radial_stdev, &b_radial_stdev);
   fChain->SetBranchAddress("radial_skewness", &radial_skewness, &b_radial_skewness);
   fChain->SetBranchAddress("radial_excess_kurtosis", &radial_excess_kurtosis, &b_radial_excess_kurtosis);
   fChain->SetBranchAddress("num_pixels_in_ring", &num_pixels_in_ring, &b_num_pixels_in_ring);
   fChain->SetBranchAddress("mean_pixel_charge_around_ring", &mean_pixel_charge_around_ring, &b_mean_pixel_charge_around_ring);
   fChain->SetBranchAddress("hg_peak_sample", &hg_peak_sample, &b_hg_peak_sample);
   fChain->SetBranchAddress("lg_peak_sample", &lg_peak_sample, &b_lg_peak_sampley);
  //---------------------------------------------------
  Notify();
}

Bool_t anabase::Notify(){
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  return kTRUE;
}

void anabase::Show(Long64_t entry){
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}

Int_t anabase::Cut(Long64_t entry){
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}

void anabase::TH2D_divide( TH2D *h2_w, TH2D *h2, TH2D *h2_norm){
  Double_t val;
  Double_t norm;
  Double_t val_norm;
  for(Int_t i = 1;i<=h2_w->GetNbinsX();i++){
    for(Int_t j = 1;j<=h2_w->GetNbinsY();j++){
      val = h2_w->GetBinContent(i,j);
      norm = h2->GetBinContent(i,j);
      if(norm>0)
        val_norm = val/norm;
      else
        val_norm = 0.0;
      h2_norm->SetBinContent(i,j,val_norm);
    }
  }
}

void anabase::TH1D_divide( TH1D *h1_w, TH1D *h1, TH1D *h1_norm){
  Double_t val;
  Double_t norm;
  Double_t val_norm;
  for(Int_t i = 1;i<=h1_w->GetNbinsX();i++){
    val = h1_w->GetBinContent(i);
    norm = h1->GetBinContent(i);
    if(norm>0)
      val_norm = val/norm;
    else
      val_norm = 0.0;
    h1_norm->SetBinContent(i,val_norm);
  }
}

void anabase::TH1D_divide( TH1D *h1, TH1D *h1_norm, Double_t norm){
  Double_t val;
  Double_t val_norm;
  for(Int_t i = 1;i<=h1->GetNbinsX();i++){
    val = h1->GetBinContent(i);
    if(norm>0)
      val_norm = val/norm;
    else
      val_norm = 0.0;
    h1_norm->SetBinContent(i,val_norm);
  }
}
