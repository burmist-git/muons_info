Int_t plots_ring_radius_vs_unixtime(){
  //TFile *f1 = new TFile("histSingle_rate.root");
  TFile *f1 = new TFile("histSingle.root");
  //
  TProfile *pr_ring_radius_vs_ut_all = (TProfile*)f1->Get("pr_ring_radius_vs_ut_all");
  //
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1800,500);
  c1->SetTitle("ring_radius_vs_unixtime");
  c1->SetName("ring_radius_vs_unixtime");
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
  //c1->SetLogy();
  //
  pr_ring_radius_vs_ut_all->SetLineColor(kBlack);
  pr_ring_radius_vs_ut_all->SetLineWidth(2.0);
  //
  pr_ring_radius_vs_ut_all->Draw();
  pr_ring_radius_vs_ut_all->GetXaxis()->SetTimeDisplay(1);
  //h1_subr->GetXaxis()->SetTimeFormat("#splitline{%m/%d}{%H:%M:%S}%F1970-01-01 00:00:00");
  pr_ring_radius_vs_ut_all->GetXaxis()->SetTimeFormat("#splitline{%m/%d/%y}{}%F1970-01-01 00:00:00");
  pr_ring_radius_vs_ut_all->GetXaxis()->SetLabelOffset(0.025);
  pr_ring_radius_vs_ut_all->GetXaxis()->SetTitle("Time");
  pr_ring_radius_vs_ut_all->GetYaxis()->SetTitle("Ring radius");
  //
  //pr_ring_radius_vs_ut_all->SetMinimum(0.08);
  //pr_ring_radius_vs_ut_all->SetMaximum(50.0);
  //
  //

  //TLegend *leg = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  //leg->AddEntry(gr_h1_rate, "Tagged", "l");
  //leg->AddEntry(gr_h1_rate_cut, "Selected", "l");
  //leg->Draw();
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
