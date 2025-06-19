//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>


#include <TDatime.h>
#include <TTimeStamp.h>

using namespace std;

void TH2D_divide( TH2D *h2_w, TH2D *h2, TH2D *h2_norm);
void TH1D_divide( TH1D *h1_w, TH1D *h1, TH1D *h1_norm);

Int_t plot_df_short(){
  //
  //
  //  impact_r_array    ring_center_r      ring_completeness
  //0 9.350664340217245 0.5739507862562909 0.6
  //1 7.199680038070672 0.8175034689302004 0.6
  //2 5.215973474301579 1.5043935330621380 0.6666666666666666
  //3 5.984899361935497 0.4053314038598204 0.8
  //4 7.406048318897023 0.4805541871057896 0.6
  //5 4.273218472201460 1.7616342063498018 0.6
  //6 9.972782659526732 1.0392290689369390 0.5
  //7 5.726992723261843 1.1663576152281827 0.7
  //8 7.731349912508189 0.5438444869397915 0.5666666666666667
  //
  //
  TString mot;
  Int_t ev_id;
  Double_t impact_r_array;
  Double_t ring_center_r;
  Double_t ring_completeness;
  //  
  //ifstream csvfFile("test.csv");
  ifstream csvfFile("test_v0.10.csv");
  Int_t i = 0;
  //
  //
  for(i = 0;i<3;i++)
    csvfFile>>mot;
  //
  TGraph *gr_entry_ID = new TGraph();
  gr_entry_ID->SetNameTitle("gr_entry_ID","gr_entry_ID");
  //
  TH1D *h1_impact_r_array = new TH1D("h1_impact_r_array","h1_impact_r_array",200, 0.0, 12.0);
  TH1D *h1_ring_center_r = new TH1D("h1_ring_center_r","h1_ring_center_r",200, 0.0, 3.0);
  TH1D *h1_ring_completeness = new TH1D("h1_ring_completeness","h1_ring_completeness",200, 0.0, 1.1);
  //
  TH1D *h1_ring_center_r_cut = new TH1D("h1_ring_center_r_cut","h1_ring_center_r_cut",50, 0.0, 3.0);
  TH1D *h1_ring_center_r_cut_w = new TH1D("h1_ring_center_r_cut_w","h1_ring_center_r_cut_w",50, 0.0, 3.0);
  TH1D *h1_ring_center_r_cut_d = new TH1D("h1_ring_center_r_cut_d","h1_ring_center_r_cut_d",50, 0.0, 3.0);
  //
  //
  TH2D *h2_impact_r_array_vs_ring_center_r = new TH2D("h2_impact_r_array_vs_ring_center_r","h2_impact_r_array_vs_ring_center_r",30, 0.0, 3.0,30, 0.0, 12.0);
  TH2D *h2_impact_r_array_vs_ring_center_r_w = new TH2D("h2_impact_r_array_vs_ring_center_r_w","h2_impact_r_array_vs_ring_center_r_w",30, 0.0, 3.0,30, 0.0, 12.0);
  TH2D *h2_impact_r_array_vs_ring_center_r_d = new TH2D("h2_impact_r_array_vs_ring_center_r_d","h2_impact_r_array_vs_ring_center_r_d",30, 0.0, 3.0,30, 0.0, 12.0);  
  //
  //
  while(csvfFile>>
	ev_id>>
	impact_r_array>>
	ring_center_r>>
	ring_completeness){
    //
    gr_entry_ID->SetPoint(gr_entry_ID->GetN(),gr_entry_ID->GetN(),ev_id);
    h1_impact_r_array->Fill(impact_r_array);
    h1_ring_center_r->Fill(ring_center_r);
    if(impact_r_array<5){
      h1_ring_center_r_cut->Fill(ring_center_r);
      h1_ring_center_r_cut_w->Fill(ring_center_r, ring_completeness);
    }
    h1_ring_completeness->Fill(ring_completeness);
    //
    h2_impact_r_array_vs_ring_center_r->Fill(ring_center_r, impact_r_array);
    h2_impact_r_array_vs_ring_center_r_w->Fill(ring_center_r, impact_r_array, ring_completeness);
    //
  }
  csvfFile.close();
  //
  TH2D_divide(h2_impact_r_array_vs_ring_center_r_w,h2_impact_r_array_vs_ring_center_r,h2_impact_r_array_vs_ring_center_r_d);
  TH1D_divide(h1_ring_center_r_cut_w,h1_ring_center_r_cut,h1_ring_center_r_cut_d);
  //

  //
  h2_impact_r_array_vs_ring_center_r_d->SetMinimum(0.0);
  h2_impact_r_array_vs_ring_center_r_d->SetMaximum(1.0);
  //
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1800,600);
  gr_entry_ID->Draw("APL");
  //
  TCanvas *c2 = new TCanvas("c2","c2",10,10,800,800);
  h1_impact_r_array->Draw();
  //
  TCanvas *c3 = new TCanvas("c3","c3",10,10,800,800);
  h1_ring_center_r->Draw();
  h1_ring_center_r_cut->Draw("same");
  //
  TCanvas *c4 = new TCanvas("c4","c4",10,10,800,800);
  h1_ring_completeness->Draw();
  //
  TCanvas *c5 = new TCanvas("c5","c5",10,10,800,800);
  h2_impact_r_array_vs_ring_center_r->Draw("ZCOLOR");
  //
  TCanvas *c6 = new TCanvas("c6","c6",10,10,800,800);
  h2_impact_r_array_vs_ring_center_r_d->Draw("ZCOLOR");
  //
  TCanvas *c7 = new TCanvas("c7","c7",10,10,800,800);
  h1_ring_center_r_cut_d->Draw();
  //
  TFile* rootFile = new TFile("histOut_plot_df_short.root", "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<"histOut_plot_df_short.root"<<" is zombi"<<endl;
    //assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<"histOut_plot_df_short.root"<<endl;
  h1_ring_center_r_cut_d->Write();
  //
  //
  rootFile->Close();
  //
  //
  return 0;
}

void TH2D_divide( TH2D *h2_w, TH2D *h2, TH2D *h2_norm){
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

void TH1D_divide( TH1D *h1_w, TH1D *h1, TH1D *h1_norm){
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
