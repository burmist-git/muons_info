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

Int_t plots_cuts_runID(){

  TString fileN;
  fileN = "./histSingle.root";
  //
  TFile *f1 = new TFile(fileN.Data());
  //  
  TH1D *h1_run_time_s = (TH1D*)f1->Get("h1_run_time_s");
  TH1D *h1_nSubRun_per_run = (TH1D*)f1->Get("h1_nSubRun_per_run");
  TH1D *h1_nmuons_per_run = (TH1D*)f1->Get("h1_nmuons_per_run");
  TH1D *h1_nmuons_per_run_9v = (TH1D*)f1->Get("h1_nmuons_per_run_9v");
  TH1D *h1_nmuons_per_run_10v = (TH1D*)f1->Get("h1_nmuons_per_run_10v");
  //
  TH1D *h1_runSelection_nSubRun_per_run = (TH1D*)f1->Get("h1_runSelection_nSubRun_per_run");
  TH1D *h1_runSelection_nmuons_per_run = (TH1D*)f1->Get("h1_runSelection_nmuons_per_run");
  TH1D *h1_runSelection_nSubRun_per_run_cut = (TH1D*)f1->Get("h1_runSelection_nSubRun_per_run_cut");
  TH1D *h1_runSelection_nmuons_per_run_cut = (TH1D*)f1->Get("h1_runSelection_nmuons_per_run_cut");
  TH1D *h1_runSelection_run_time_s = (TH1D*)f1->Get("h1_runSelection_run_time_s");
  TH1D *h1_runSelection_run_time_s_cut = (TH1D*)f1->Get("h1_runSelection_run_time_s_cut");
  //
  //
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  TCanvas *c1 = new TCanvas("c1",fileN.Data(),10,10,1700,400);
  c1->Divide(3,1);
  //
  c1->cd(1);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_run_time_s->Rebin(2);
  h1_run_time_s->SetLineColor(kBlack);
  h1_run_time_s->SetLineWidth(3.0);
  h1_run_time_s->SetTitle("");
  h1_run_time_s->Draw();
  h1_run_time_s->GetXaxis()->SetTitle("run time, s");
  h1_run_time_s->GetXaxis()->SetRangeUser(0,1500);
  h1_run_time_s->GetXaxis()->SetLabelSize(0.06);
  h1_run_time_s->GetYaxis()->SetLabelSize(0.06);
  h1_run_time_s->GetXaxis()->SetTitleSize(0.06);
  //
  c1->cd(2);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  //gPad->SetLogy();
  h1_nSubRun_per_run->Rebin(2);
  h1_nSubRun_per_run->SetLineColor(kBlack);
  h1_nSubRun_per_run->SetLineWidth(3.0);
  h1_nSubRun_per_run->SetTitle("");
  h1_nSubRun_per_run->Draw();
  h1_nSubRun_per_run->GetXaxis()->SetTitle("number of sub runs per run");
  h1_nSubRun_per_run->GetXaxis()->SetRangeUser(0,425);
  h1_nSubRun_per_run->GetXaxis()->SetLabelSize(0.06);
  h1_nSubRun_per_run->GetYaxis()->SetLabelSize(0.06);
  h1_nSubRun_per_run->GetXaxis()->SetTitleSize(0.06);
  //
  c1->cd(3);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  //gPad->SetLogy();
  h1_nmuons_per_run->Rebin(10);
  h1_nmuons_per_run_9v->Rebin(10);
  h1_nmuons_per_run_10v->Rebin(10);
  h1_nmuons_per_run->SetLineColor(kBlack);
  h1_nmuons_per_run->SetLineWidth(3.0);
  h1_nmuons_per_run_10v->SetLineColor(kRed+2);
  h1_nmuons_per_run_10v->SetLineWidth(3.0);
  h1_nmuons_per_run_9v->SetLineColor(kBlue+2);
  h1_nmuons_per_run_9v->SetLineWidth(3.0);
  h1_nmuons_per_run->SetTitle("");
  h1_nmuons_per_run->Draw();
  h1_nmuons_per_run_10v->Draw("sames");
  h1_nmuons_per_run_9v->Draw("sames");
  h1_nmuons_per_run->GetXaxis()->SetTitle("number of muons per run");
  h1_nmuons_per_run->GetXaxis()->SetLabelSize(0.06);
  h1_nmuons_per_run->GetYaxis()->SetLabelSize(0.06);
  h1_nmuons_per_run->GetXaxis()->SetTitleSize(0.06);
  //
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_nmuons_per_run,  "lst-chain v0.9/v0.10", "l");
  leg->AddEntry(h1_nmuons_per_run_9v,  "lst-chain v0.9", "l");
  leg->AddEntry(h1_nmuons_per_run_10v, "lst-chain v0.10", "l");
  leg->Draw();
  //
  //
  //
  //

  //
  //
  //
  //
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  //gStyle->SetOptStat(kFALSE);
  TCanvas *c2 = new TCanvas("c2",fileN.Data(),10,10,1700,400);
  c2->Divide(3,1);
  //
  c2->cd(1);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  gPad->SetLogy();
  h1_runSelection_run_time_s->Rebin(2);
  h1_runSelection_run_time_s_cut->Rebin(2);
  h1_runSelection_run_time_s->SetLineColor(kBlack);
  h1_runSelection_run_time_s->SetLineWidth(3.0);
  h1_runSelection_run_time_s_cut->SetLineColor(kRed+2);
  h1_runSelection_run_time_s_cut->SetLineWidth(3.0);
  h1_runSelection_run_time_s->SetTitle("");
  h1_runSelection_run_time_s->Draw();
  h1_runSelection_run_time_s_cut->Draw("sames");
  h1_runSelection_run_time_s->GetXaxis()->SetTitle("run time, s");
  h1_runSelection_run_time_s->GetXaxis()->SetRangeUser(0,1500);
  h1_runSelection_run_time_s->GetXaxis()->SetLabelSize(0.06);
  h1_runSelection_run_time_s->GetYaxis()->SetLabelSize(0.06);
  h1_runSelection_run_time_s->GetXaxis()->SetTitleSize(0.06);
  //
  c2->cd(2);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  //gPad->SetLogy();
  h1_runSelection_nSubRun_per_run->Rebin(2);
  h1_runSelection_nSubRun_per_run->SetLineColor(kBlack);
  h1_runSelection_nSubRun_per_run->SetLineWidth(3.0);
  h1_runSelection_nSubRun_per_run_cut->Rebin(2);
  h1_runSelection_nSubRun_per_run_cut->SetLineColor(kRed+2);
  h1_runSelection_nSubRun_per_run_cut->SetLineWidth(3.0);
  h1_runSelection_nSubRun_per_run->SetTitle("");
  h1_runSelection_nSubRun_per_run->Draw();
  h1_runSelection_nSubRun_per_run_cut->Draw("sames");
  h1_runSelection_nSubRun_per_run->GetXaxis()->SetTitle("number of sub runs per run");
  h1_runSelection_nSubRun_per_run->GetXaxis()->SetRangeUser(0,425);
  h1_runSelection_nSubRun_per_run->GetXaxis()->SetLabelSize(0.06);
  h1_runSelection_nSubRun_per_run->GetYaxis()->SetLabelSize(0.06);
  h1_runSelection_nSubRun_per_run->GetXaxis()->SetTitleSize(0.06);
  //
  c2->cd(3);
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.1);
  //gPad->SetLogy();
  h1_runSelection_nmuons_per_run->Rebin(10);
  h1_runSelection_nmuons_per_run_cut->Rebin(10);
  h1_runSelection_nmuons_per_run->SetLineColor(kBlack);
  h1_runSelection_nmuons_per_run->SetLineWidth(3.0);
  h1_runSelection_nmuons_per_run_cut->SetLineColor(kRed+2);
  h1_runSelection_nmuons_per_run_cut->SetLineWidth(3.0);
  h1_runSelection_nmuons_per_run->SetTitle("");
  h1_runSelection_nmuons_per_run->Draw();
  h1_runSelection_nmuons_per_run_cut->Draw("sames");
  h1_runSelection_nmuons_per_run->GetXaxis()->SetTitle("number of muons per run");
  h1_runSelection_nmuons_per_run->GetXaxis()->SetLabelSize(0.06);
  h1_runSelection_nmuons_per_run->GetYaxis()->SetLabelSize(0.06);
  h1_runSelection_nmuons_per_run->GetXaxis()->SetTitleSize(0.06);
  //
  //
  //TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  //leg->AddEntry(h1_nmuons_per_run,  "lst-chain v0.9/v0.10", "l");
  //leg->AddEntry(h1_nmuons_per_run_9v,  "lst-chain v0.9", "l");
  //leg->AddEntry(h1_nmuons_per_run_10v, "lst-chain v0.10", "l");
  //leg->Draw();
  //
  return 0;
}
