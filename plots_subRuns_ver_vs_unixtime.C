Int_t plots_subRuns_ver_vs_unixtime(){
  TFile *f1 = new TFile("hist_subRunlist_for_root.root");
  //
  TH1D *h1_subr = (TH1D*)f1->Get("h1_subRun_tot");
  TH1D *h1_subr_v9 = (TH1D*)f1->Get("h1_subRun_tot_v9");
  TH1D *h1_subr_v10 = (TH1D*)f1->Get("h1_subRun_tot_v10");
  TH1D *h1_volc = (TH1D*)f1->Get("h1_Cumbre_Vieja_volcanic_eruption_tot");
  TH1D *h1_covid = (TH1D*)f1->Get("h1_covid_tot");
  TH1D *h1_struct = (TH1D*)f1->Get("h1_struct_tot");  
  //
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1800,600);
  c1->SetTitle("subRuns_ver_vs_unixtime");
  c1->SetName("subRuns_ver_vs_unixtime");
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  c1->SetRightMargin(0.03);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.03);
  c1->SetBottomMargin(0.1);
  //
  h1_subr->SetLineColor(kBlack);
  h1_subr_v9->SetLineColor(kBlue+2);
  h1_subr_v10->SetLineColor(kRed+2);
  //
  h1_subr->SetLineWidth(2);
  h1_subr_v9->SetLineWidth(2);
  h1_subr_v10->SetLineWidth(2);
  //
  //
  h1_volc->SetLineColor(kMagenta+2);
  h1_covid->SetLineColor(kGreen+2);
  h1_struct->SetLineColor(kYellow+2);
  h1_volc->SetLineWidth(3);
  h1_covid->SetLineWidth(3);
  h1_struct->SetLineWidth(3);  
  //
  //
  h1_subr->SetTitle("");
  //
  h1_subr->Draw();
  h1_subr->GetXaxis()->SetTimeDisplay(1);
  //h1_subr->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00");
  h1_subr->GetXaxis()->SetTimeFormat("#splitline{%m/%d/%y}{}%F1970-01-01 00:00:00");
  h1_subr->GetXaxis()->SetLabelOffset(0.025);

  h1_subr->SetMinimum(0.0);
  h1_subr->SetMaximum(10000.0);
  
  h1_subr_v9->Draw("same");
  h1_subr_v10->Draw("same");
  h1_volc->Draw("same");
  h1_covid->Draw("same");
  h1_struct->Draw("same");
  h1_subr->GetXaxis()->SetTitle("Time");
  h1_subr->GetYaxis()->SetTitle("Number of subruns per night");

  //
  //
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(h1_subr,     "lst-chain v0.9/v0.10", "l");
  leg->AddEntry(h1_subr_v9,  "lst-chain v0.9", "l");
  leg->AddEntry(h1_subr_v10, "lst-chain v0.10", "l");
  leg->AddEntry(h1_covid,   "COVID-19", "l");
  leg->AddEntry(h1_volc,   "Cumbre Vieja volcanic eruption", "l");
  leg->AddEntry(h1_struct,   "Structure integrity investigation", "l");
  //
  //
  leg->Draw();

  /*
  //
  //c1->Divide(1,3);
  //
  c1->cd(1);
  gr_ut->SetMarkerStyle(20);
  gr_ut->Draw("APL");
  gr_ut->GetXaxis()->SetTimeDisplay(1);
  gr_ut->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00");
  gr_ut->GetXaxis()->SetLabelOffset(0.025);
  //gr_ut->GetXaxis()->SetTitle("Time, h");
  //
  c1->cd(2);
  gr_rdt->SetMarkerStyle(20);
  gr_rdt->Draw("APL");
  gr_rdt->GetXaxis()->SetTimeDisplay(1);
  gr_rdt->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00"); 
  gr_rdt->GetXaxis()->SetLabelOffset(0.025);
  //
  c1->cd(3);
  gr_tts->SetMarkerStyle(20);
  gr_tts->Draw("APL");
  gr_tts->GetXaxis()->SetTimeDisplay(1);
  gr_tts->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00"); 
  gr_tts->GetXaxis()->SetLabelOffset(0.025);
  */
  return 0;
}
