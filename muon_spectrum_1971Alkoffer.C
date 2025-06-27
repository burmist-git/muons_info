///////////////////////////////////////////////////
// mom_min  mom_max mom_ave rate/cm/cm/sr/s/(GeV/c)
//  0.20     0.50    0.34   ( 3.92  0.62 ) x 10 -3
//  0.50     0.80    0.64   ( 3.59  0.49 ) x 10 -3
//  0.80     2.00    1.32   ( 2.57  0.29 ) x 10 -3
//  2.00     4.00    2.86   ( 1.11  0.13 ) x 10 -3
//  4.00     6.00    4.91   ( 4.13  0.59 ) x 10 -4
//  0.98     1.24    1.11   ( 2.90  0.20 ) x 10 -3
//  0.20     0.40    0.29   ( 3.57  0.35 ) x 10 -3
//  0.40     0.60    0.50   ( 3.70  0.35 ) x 10 -3
//  0.60     1.00    0.79   ( 3.41  0.28 ) x 10 -3
//  1.00     1.50    1.24   ( 2.73  0.23 ) x 10 -3
//  1.50     2.50    1.95   ( 1.73  0.15 ) x 10 -3
//  2.50     4.00    3.17   ( 7.92  0.65 ) x 10 -4
//  4.00     6.00    4.91   ( 4.24  0.37 ) x 10 -4
//  6.00    10.00    7.76   ( 1.84  0.17 ) x 10 -4
//  10.0    13.00   11.40   ( 1.13  0.01 ) x 10 -4
//  13.0    17.00   14.80   ( 6.04  0.08 ) x 10 -5
//  17.0    25.00   20.50   ( 2.51  0.03 ) x 10 -5
//  25.0    40.00   31.40   ( 8.01  0.13 ) x 10 -6
//  40.0    70.00   52.30   ( 1.89  0.05 ) x 10 -6
//  70.0   128.00   93.00   ( 3.38  0.14 ) x 10 -7
// 128.0   250.00  175.00   ( 5.19  0.37 ) x 10 -8
// 250.0   450.00  329.00   ( 7.84  1.12 ) x 10 -9
// 450.0  1000.00  642.00   ( 6.40  1.92 ) x 10 -10
///////////////////////////////////////////////////

Double_t power_law(Double_t *x, Double_t *par);
Double_t get_muon_spectrum_1971Alkoffer(Double_t muon_p_GeVc);
void load_muon_spectrum_1971Alkoffer(TString dataf, TGraphErrors *gr);
void fill_graph(TGraph *gr, Int_t np, Double_t pmin, Double_t pmax);

Int_t muon_spectrum_1971Alkoffer(){
  TGraphErrors *gr = new TGraphErrors();
  load_muon_spectrum_1971Alkoffer("1971Alkoffer_muon.spectrum", gr);
  TGraph *gr_fit = new TGraph();
  fill_graph(gr_fit, 100000,0.2,1000);
  gr->Draw("AP");
  //gr_fit->Draw("same");

  Double_t pMin = 11;
  Double_t pMax = 1000;
  const Int_t npar = 2;
  Double_t inParameters[npar];
  inParameters[0] = 1.0e+0;
  inParameters[1] = 2.0;
  //
  TF1 *f_power_law = new TF1( "f_power_law", power_law, pMin, pMax, npar);
  f_power_law->SetParameters(inParameters);
  f_power_law->SetParName(0, "A");
  f_power_law->SetParName(1, "B");
  //f_power_law->FixParameter(0,inParameters[0]);
  //f_power_law->FixParameter(1,inParameters[1]);
  gPad->SetLogx();
  gPad->SetLogy();
  gr->Fit("f_power_law","","",pMin, pMax);

  
  //TMultiGraph *mg = new TMultiGraph();  
  //mg->Add(gr);
  //mg->Add(gr_fit);
  //mg->Draw("ap");
  //mg->GetXaxis()->SetTitle("ValueX, Unit");
  //mg->GetYaxis()->SetTitle("ValueY, Unit");

  
  return 0;
}

Double_t get_muon_spectrum_1971Alkoffer(Double_t muon_p_GeVc){
  Double_t P = 1.0;
  Double_t A = 0.199;
  Double_t r1 = 0.76;
  Double_t B1 = 90.0;
  Double_t gamma = 2.63;
  Double_t muon_m_GeVc = 0.1057;
  Double_t E = TMath::Sqrt(muon_p_GeVc*muon_p_GeVc + muon_m_GeVc*muon_m_GeVc) - muon_m_GeVc;
  //
  Double_t diff_intencity_per_cm2_per_s_per_sr_perGeVc = 0.0;
  if(muon_p_GeVc < 0.2 || muon_p_GeVc > 1000.0)
    return diff_intencity_per_cm2_per_s_per_sr_perGeVc;
  //
  diff_intencity_per_cm2_per_s_per_sr_perGeVc = P*A*TMath::Power(E,-gamma)*(B1/(E + B1)/r1);
  return diff_intencity_per_cm2_per_s_per_sr_perGeVc;
}

// mom_min  mom_max mom_ave rate/cm/cm/sr/s/(GeV/c)
//  0.20     0.50    0.34   ( 3.92  0.62 ) x 10 -3
//  0.50     0.80    0.64   ( 3.59  0.49 ) x 10 -3
void load_muon_spectrum_1971Alkoffer(TString dataf, TGraphErrors *gr){
  //
  ifstream fFile(dataf.Data());
  TString mot;
  Double_t mom_min, mom_max, mom_ave, rate, rate_err;
  Int_t power_int;  
  //
  Double_t v_rate, v_rate_err, p, p_err;
  //
  if(fFile.is_open()){
    for(Int_t i = 0;i<4;i++)
      fFile>>mot;
    while(fFile>>mom_min>>mom_max>>mom_ave>>mot>>rate>>rate_err>>mot>>mot>>mot>>power_int){
      v_rate = rate*TMath::Power(10,(Double_t)power_int);
      v_rate_err = rate_err*TMath::Power(10,(Double_t)power_int);
      p = mom_ave;
      p_err = (mom_max - mom_min)/2.0/TMath::Sqrt(12.0);
      Int_t npp = gr->GetN();
      gr->SetPoint(npp,p,v_rate*p);
      gr->SetPointError(npp,p_err,v_rate_err);
    }
    fFile.close();
  }
}

void fill_graph(TGraph *gr, Int_t np, Double_t pmin, Double_t pmax){
  Double_t p;
  Double_t r;
  for(Int_t i = 0;i<np;i++){
    p = pmin + (pmax - pmin)/(np - 1)*i;
    r = get_muon_spectrum_1971Alkoffer(p);
    gr->SetPoint(i,p,r);
  }
}

Double_t power_law(Double_t *x, Double_t *par){
  Double_t A  = par[0];
  Double_t B  = par[1];
  Double_t val = A/(TMath::Power(x[0],B));
  return val;
}
