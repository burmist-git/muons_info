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

Int_t plots_cuts(){

  TString fileN;
  fileN = "./histSingle.root";
  //
  TFile *f1 = new TFile(fileN.Data());
  //  
  TH1D *h1_ring_size_all = (TH1D*)f1->Get("h1_ring_size_all");
  TH1D *h1_size_outside_all = (TH1D*)f1->Get("h1_size_outside_all");
  TH1D *h1_muon_efficiency_all = (TH1D*)f1->Get("h1_muon_efficiency_all");
  TH1D *h1_ring_containment_all = (TH1D*)f1->Get("h1_ring_containment_all");
  TH1D *h1_ring_completeness_all = (TH1D*)f1->Get("h1_ring_completeness_all");
  TH1D *h1_ring_width_all = (TH1D*)f1->Get("h1_ring_width_all");
  TH1D *h1_ring_radius_all = (TH1D*)f1->Get("h1_ring_radius_all");
  TH1D *h1_ring_center_r_all = (TH1D*)f1->Get("h1_ring_center_r_all");
  //  
  TH1D *h1_size_outside = (TH1D*)f1->Get("h1_size_outside");
  TH1D *h1_ring_containment = (TH1D*)f1->Get("h1_ring_containment");
  TH1D *h1_ring_completeness = (TH1D*)f1->Get("h1_ring_completeness");
  TH1D *h1_ring_size = (TH1D*)f1->Get("h1_ring_size");
  TH1D *h1_ring_width = (TH1D*)f1->Get("h1_ring_width");
  TH1D *h1_muon_efficiency = (TH1D*)f1->Get("h1_muon_efficiency");
  TH1D *h1_ring_radius = (TH1D*)f1->Get("h1_ring_radius");
  TH1D *h1_ring_center_r = (TH1D*)f1->Get("h1_ring_center_r");

  //
  //	  if(ring_center_r<1.1){
  //	    if(>1.02 && ring_radius<1.26){

  //
  //
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,1700,600);
  c1->Divide(4,2);
  //
  c1->cd(1);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_size_outside_all->SetLineColor(kBlack);
  h1_size_outside_all->SetLineWidth(3.0);
  h1_size_outside->SetLineColor(kRed+2);
  h1_size_outside->SetLineWidth(3.0);
  h1_size_outside_all->Draw();
  h1_size_outside->Draw("sames");
  h1_size_outside_all->GetXaxis()->SetTitle("size outside ring,  p.e.");
  //h1_size_outside_all->GetXaxis()->SetRangeUser(-0.13,-0.12);
  //
  c1->cd(2);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_ring_containment_all->SetLineColor(kBlack);
  h1_ring_containment_all->SetLineWidth(3.0);
  h1_ring_containment->SetLineColor(kRed+2);
  h1_ring_containment->SetLineWidth(3.0);
  h1_ring_containment_all->Draw();
  h1_ring_containment->Draw("sames");
  h1_ring_containment_all->GetXaxis()->SetTitle("");
  //
  c1->cd(3);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_ring_completeness_all->SetLineColor(kBlack);
  h1_ring_completeness_all->SetLineWidth(3.0);
  h1_ring_completeness->SetLineColor(kRed+2);
  h1_ring_completeness->SetLineWidth(3.0);
  h1_ring_completeness_all->Draw();
  h1_ring_completeness->Draw("sames");
  h1_ring_completeness_all->GetXaxis()->SetTitle("");
  //
  c1->cd(4);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_ring_size_all->SetLineColor(kBlack);
  h1_ring_size_all->SetLineWidth(3.0);
  h1_ring_size->SetLineColor(kRed+2);
  h1_ring_size->SetLineWidth(3.0);
  h1_ring_size_all->Draw();
  h1_ring_size->Draw("sames");
  h1_ring_size_all->GetXaxis()->SetTitle("");
  //
  c1->cd(5);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_ring_width_all->SetLineColor(kBlack);
  h1_ring_width_all->SetLineWidth(3.0);
  h1_ring_width->SetLineColor(kRed+2);
  h1_ring_width->SetLineWidth(3.0);
  h1_ring_width_all->Draw();
  h1_ring_width->Draw("sames");
  h1_ring_width_all->GetXaxis()->SetTitle("");
  //
  c1->cd(6);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_muon_efficiency_all->SetLineColor(kBlack);
  h1_muon_efficiency_all->SetLineWidth(3.0);
  h1_muon_efficiency->SetLineColor(kRed+2);
  h1_muon_efficiency->SetLineWidth(3.0);
  h1_muon_efficiency_all->Draw();
  h1_muon_efficiency->Draw("sames");
  h1_muon_efficiency_all->GetXaxis()->SetTitle("");
  //
  c1->cd(7);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_ring_radius_all->SetLineColor(kBlack);
  h1_ring_radius_all->SetLineWidth(3.0);
  h1_ring_radius->SetLineColor(kRed+2);
  h1_ring_radius->SetLineWidth(3.0);
  h1_ring_radius_all->Draw();
  h1_ring_radius->Draw("sames");
  h1_ring_radius_all->GetXaxis()->SetTitle("");
  //
  c1->cd(8);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_ring_center_r_all->SetLineColor(kBlack);
  h1_ring_center_r_all->SetLineWidth(3.0);
  h1_ring_center_r->SetLineColor(kRed+2);
  h1_ring_center_r->SetLineWidth(3.0);
  h1_ring_center_r_all->Draw();
  h1_ring_center_r->Draw("sames");
  h1_ring_center_r_all->GetXaxis()->SetTitle("");
  //
  //
  return 0;
}
