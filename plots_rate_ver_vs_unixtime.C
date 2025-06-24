Int_t plots_rate_ver_vs_unixtime(){
  TFile *f1 = new TFile("histSingle_rate.root");
  //
  TGraph *gr_h1_rate = (TGraph*)f1->Get("gr_h1_rate");
  TGraph *gr_h1_rate_cut = (TGraph*)f1->Get("gr_h1_rate_cut");
  //
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1800,500);
  c1->SetTitle("rate_ver_vs_unixtime");
  c1->SetName("rate_ver_vs_unixtime");
  //
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetStatColor(kWhite);
  gStyle->SetOptStat(kFALSE);
  //
  c1->SetRightMargin(0.01);
  c1->SetLeftMargin(0.05);
  c1->SetTopMargin(0.03);
  c1->SetBottomMargin(0.1);
  c1->SetLogy();
  //
  gr_h1_rate->SetLineColor(kBlack);
  gr_h1_rate_cut->SetLineColor(kRed+2);
  gr_h1_rate->SetMarkerColor(kBlack);
  gr_h1_rate_cut->SetMarkerColor(kRed+2);
  gr_h1_rate->SetLineWidth(2.0);
  gr_h1_rate_cut->SetLineWidth(2.0);
  //
  TMultiGraph *mg = new TMultiGraph();  
  mg->Add(gr_h1_rate);
  mg->Add(gr_h1_rate_cut);
  //
  //
  //
  mg->Draw("AP");
  mg->GetXaxis()->SetTimeDisplay(1);
  //h1_subr->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00");
  mg->GetXaxis()->SetTimeFormat("#splitline{%m/%d/%y}{}%F1970-01-01 00:00:00");
  mg->GetXaxis()->SetLabelOffset(0.025);
  mg->GetXaxis()->SetTitle("Time");
  mg->GetYaxis()->SetTitle("Rate, Hz");
  //
  mg->SetMinimum(0.08);
  mg->SetMaximum(50.0);
  //
  //
  TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg->AddEntry(gr_h1_rate, "Tagged", "l");
  leg->AddEntry(gr_h1_rate_cut, "Selected", "l");
  leg->Draw();
  //
  //
  /*  
  h1_subr_v9->Draw("same");
  h1_subr_v10->Draw("same");
  h1_volc->Draw("same");
  h1_covid->Draw("same");
  h1_struct->Draw("same");
  h1_subr->GetXaxis()->SetTitle("Time");
  h1_subr->GetYaxis()->SetTitle("Number of subruns per night");
  */
  /*  
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
  */
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
