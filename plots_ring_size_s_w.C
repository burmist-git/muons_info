//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <time.h>

using namespace std;

void TH1D_norm( TH1D *h1, Double_t norm);

Int_t plots_ring_size_s_w(){

  TString fileN01;
  TString fileN02;
  TString fileN03;
  TString fileNtot;
  fileN01 = "./histSingle_2021year.root";
  fileN02 = "./histSingle_2023year.root";
  fileN03 = "./histSingle_2024year.root";
  fileNtot = "./histSingle_allyear_nvar.root";
  //
  TFile *f1 = new TFile(fileN01.Data());
  TFile *f2 = new TFile(fileN02.Data());
  TFile *f3 = new TFile(fileN03.Data());
  TFile *ftot = new TFile(fileNtot.Data());
  
  TH1D *h1_1_w = (TH1D*)f1->Get("h1_ring_size_3m");
  TH1D *h1_2_w = (TH1D*)f2->Get("h1_ring_size_3m");
  TH1D *h1_3_w = (TH1D*)f3->Get("h1_ring_size_3m");
  TH1D *h1_1_s = (TH1D*)f1->Get("h1_ring_size_8m");
  TH1D *h1_2_s = (TH1D*)f2->Get("h1_ring_size_8m");
  TH1D *h1_3_s = (TH1D*)f3->Get("h1_ring_size_8m");
  TH1D *h1_tot_w = (TH1D*)ftot->Get("h1_ring_size_3m");
  TH1D *h1_tot_s = (TH1D*)ftot->Get("h1_ring_size_8m");
  //
  //

  //
  TH1D_norm(h1_1_w,h1_1_w->GetEntries());
  TH1D_norm(h1_1_s,h1_1_s->GetEntries());
  TH1D_norm(h1_2_w,h1_2_w->GetEntries());
  TH1D_norm(h1_2_s,h1_2_s->GetEntries());
  TH1D_norm(h1_3_w,h1_3_w->GetEntries());
  TH1D_norm(h1_3_s,h1_3_s->GetEntries());
  TH1D_norm(h1_tot_w,h1_tot_w->GetEntries());
  TH1D_norm(h1_tot_s,h1_tot_s->GetEntries());
  //
  
  //gStyle->SetOptStat(kFALSE); 
  //h1_1->SetLineColor(kBlack);
  //h1_1->SetLineWidth(3.0);
  //h1_1->Draw();
  //h1_1->GetXaxis()->SetTitle("Value, Unit");
  //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);

  TCanvas *c1 = new TCanvas("c1",fileN01.Data(),10,10,1700,500);
  c1->Divide(4,1);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);

  c1->cd(1);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  h1_1_w->GetXaxis()->SetRangeUser(1600,3330);
  h1_1_w->SetLineColor(kBlack);
  h1_1_w->SetLineWidth(3.0);
  h1_1_s->SetLineColor(kRed+2);
  h1_1_s->SetLineWidth(3.0);  
  h1_1_w->SetTitle("2021");
  h1_1_w->Draw();
  h1_1_s->Draw("sames");
  h1_1_w->GetXaxis()->SetTitle("Ring size, p.e.");
  
  c1->cd(2);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  h1_2_w->GetXaxis()->SetRangeUser(1600,3300);
  h1_2_w->SetLineColor(kBlack);
  h1_2_w->SetLineWidth(3.0);
  h1_2_s->SetLineColor(kRed+2);
  h1_2_s->SetLineWidth(3.0);  
  h1_2_w->SetTitle("2023");
  h1_2_w->Draw();
  h1_2_s->Draw("sames");
  h1_2_w->GetXaxis()->SetTitle("Ring size, p.e.");
  
  c1->cd(3);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  h1_3_w->SetLineColor(kBlack);
  h1_3_w->SetLineWidth(3.0);
  h1_3_s->SetLineColor(kRed+2);
  h1_3_s->SetLineWidth(3.0);  
  h1_3_w->GetXaxis()->SetRangeUser(1600,3300);
  h1_3_w->SetTitle("2024");
  h1_3_w->Draw();
  h1_3_s->Draw("sames");
  h1_3_w->GetXaxis()->SetTitle("Ring size, p.e.");
  
  c1->cd(4);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);

  h1_tot_w->SetLineColor(kBlack);
  h1_tot_w->SetLineWidth(3.0);
  h1_tot_s->SetLineColor(kRed+2);
  h1_tot_s->SetLineWidth(3.0);  
  h1_tot_w->GetXaxis()->SetRangeUser(1600,3300);
  h1_tot_w->SetTitle("2020-2025");
  h1_tot_w->Draw();
  h1_tot_s->Draw("sames");
  h1_tot_w->GetXaxis()->SetTitle("Ring size, p.e.");
  
  /*
  TCanvas *c3 = new TCanvas("c3",fileNtot.Data(),10,10,1700,500);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  c3->Divide(2,1);
  c3->cd(2);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  //
  gr_err->SetLineColor(kBlack);
  gr_err->SetLineWidth(3.0);
  gr_err->SetMarkerColor(kBlack);
  gr_err->SetMarkerStyle(20);

  gr_err->Draw("APL");
  gr_err->GetXaxis()->SetTitle("Month");
  gr_err->GetYaxis()->SetTitle("Max. prob. val. of ring radius, deg");
  
  
  
  //
  c3->cd(1);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);

  
  h1_ring_radius_w->SetLineColor(kBlack);
  h1_ring_radius_w->SetLineWidth(3.0);
  h1_ring_radius_w->SetMarkerColor(kBlack);
  h1_ring_radius_w->SetMarkerStyle(1);
  //
  h1_ring_radius_s->SetLineColor(kRed+2);
  h1_ring_radius_s->SetLineWidth(3.0);
  h1_ring_radius_s->SetMarkerColor(kRed+2);
  h1_ring_radius_s->SetMarkerStyle(1);
  //
  //
  h1_ring_radius_s->Rebin(2);
  h1_ring_radius_w->Rebin(2);
  //
  //  
  h1_ring_radius_w->SetMinimum(0.0);
  h1_ring_radius_w->SetMaximum(0.04);
  h1_ring_radius_w->SetTitle("");
  h1_ring_radius_w->Draw("HIST");
  h1_ring_radius_s->Draw("HIST sames");
  h1_ring_radius_w->GetXaxis()->SetTitle("Muon ring radius, deg");
  //
  TLegend *leg002 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg002->AddEntry(h1_ring_radius_w, "March", "apl");
  leg002->AddEntry(h1_ring_radius_s, "August", "apl");  
  leg002->Draw();    
  //
  //
  //
  //
*/


  
  
  //mg->GetXaxis()->SetTitle("ValueX, Unit");
  //mg->GetYaxis()->SetTitle("ValueY, Unit");

  /*
  TString legInfo;
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  for(i = 0;i<nChannels;i++){
    legInfo = "ch ";legInfo += i;
    leg->AddEntry(gr_Arr[i], legInfo.Data(), "apl");
  }
  leg->Draw();
  */  

  return 0;
}

void TH1D_norm( TH1D *h1, Double_t norm){
  Double_t val;
  Double_t val_norm;
  for(Int_t i = 1;i<=h1->GetNbinsX();i++){
    val = h1->GetBinContent(i);
    if(norm>0)
      val_norm = val/norm;
    else
      val_norm = 0.0;
    h1->SetBinContent(i,val_norm);
  }
}
