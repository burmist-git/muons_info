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

Int_t plots_r(){

  TString fileN01;
  TString fileN02;
  TString fileN03;
  TString fileN04;
  TString fileN05;
  TString fileNtot;
  fileN01 = "./histSingle_2020year.root";
  fileN02 = "./histSingle_2021year.root";
  fileN03 = "./histSingle_2022year.root";
  fileN04 = "./histSingle_2023year.root";
  fileN05 = "./histSingle_2024year.root";
  fileNtot = "./histSingle.root";
  //
  TFile *f1 = new TFile(fileN01.Data());
  TFile *f2 = new TFile(fileN02.Data());
  TFile *f3 = new TFile(fileN03.Data());
  TFile *f4 = new TFile(fileN04.Data());
  TFile *f5 = new TFile(fileN05.Data());
  TFile *ftot = new TFile(fileNtot.Data());
  
  TGraph *gr_1 = (TGraph*)f1->Get("gr_month_vs_ring_radius");
  TGraph *gr_2 = (TGraph*)f2->Get("gr_month_vs_ring_radius");
  TGraph *gr_3 = (TGraph*)f3->Get("gr_month_vs_ring_radius");
  TGraph *gr_4 = (TGraph*)f4->Get("gr_month_vs_ring_radius");
  TGraph *gr_5 = (TGraph*)f5->Get("gr_month_vs_ring_radius");

  TH1D *h1_ring_radius_w = (TH1D*)ftot->Get("h1_ring_radius_3m");
  TH1D *h1_ring_radius_s = (TH1D*)ftot->Get("h1_ring_radius_8m");

  
  TGraph *gr = new TGraph();
  TGraph *gr_new = new TGraph();
  //
  Double_t x, y;
  //
  //
  for(Int_t i = 0;i<gr_1->GetN();i++){
    gr_1->GetPoint(i,x,y);
    gr->SetPoint(gr->GetN(),x+12*0,y);
  }
  for(Int_t i = 0;i<gr_2->GetN();i++){
    gr_2->GetPoint(i,x,y);
    gr->SetPoint(gr->GetN(),x+12*0,y);
  }
  for(Int_t i = 0;i<gr_3->GetN();i++){
    gr_3->GetPoint(i,x,y);
    gr->SetPoint(gr->GetN(),x+12*0,y);
  }
  for(Int_t i = 0;i<gr_4->GetN();i++){
    gr_4->GetPoint(i,x,y);
    gr->SetPoint(gr->GetN(),x+12*0,y);
  }
  for(Int_t i = 0;i<gr_5->GetN();i++){
    gr_5->GetPoint(i,x,y);
    gr->SetPoint(gr->GetN(),x+12*0,y);
  }
  //
  //
  Double_t yave = 0.0;
  Double_t nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 0.9 && x < 1.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint(0,1.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 1.9 && x < 2.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 1, 2.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 2.9 && x < 3.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 2, 3.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 3.9 && x < 4.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 3, 4.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 4.9 && x < 5.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 4, 5.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 5.9 && x < 6.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 5, 6.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 6.9 && x < 7.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 6, 7.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 7.9 && x < 8.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 7, 8.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 8.9 && x < 9.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 8, 9.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 9.9 && x < 10.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 9, 10.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 10.9 && x < 11.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 10, 11.0, yave/nave);  
  //
  yave = 0.0;
  nave = 0.0;
  for(Int_t i = 0;i<gr->GetN();i++){
    gr->GetPoint(i,x,y);
    if(x > 11.9 && x < 12.1 ){
      yave+=y;
      nave++;
    }
  }
  gr_new->SetPoint( 11, 12.0, yave/nave);  

  //
  //
  //TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,800,800);
  TCanvas *c1 = new TCanvas("c1",fileN01.Data(),10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
 
  //h1_1->SetLineColor(kBlack);
  //h1_1->SetLineWidth(3.0);

  //h1_1->Draw();
  //h1_1->GetXaxis()->SetTitle("Value, Unit");
  //h1_1->GetXaxis()->SetRangeUser(-0.13,-0.12);


  TMultiGraph *mg = new TMultiGraph();  
  gr_1->SetLineColor(kBlack);
  gr_1->SetLineWidth(3.0);
  gr_1->SetMarkerColor(kBlack);
  gr_1->SetMarkerStyle(20);
  //
  mg->Add(gr_1);
  mg->Add(gr_2);
  mg->Add(gr_3);
  mg->Add(gr_4);
  mg->Add(gr_5);
  mg->Draw("apl");

  TCanvas *c2 = new TCanvas("c2",fileN01.Data(),10,10,600,600);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  gr_new->Draw("APL");
  //
  //
  TGraphErrors *gr_err = new TGraphErrors();
  for(Int_t i = 0; i < gr_new->GetN();i++){
    Double_t x,y;
    gr_new->GetPoint(i,x,y);
    gr_err->SetPoint(i,x,y);
    gr_err->SetPointError( i, 0.0, 0.003);
  }

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
