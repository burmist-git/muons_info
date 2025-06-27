//my
#include "ana.hh"

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
#include <TRandom3.h>
#include <TMath.h>
#include <TGraphErrors.h>

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

void ana::get_UT_first_and_last(){
  Long64_t jentry;
  Long64_t ientry;
  Long64_t nentries;
  Long64_t nbytes = 0, nb = 0;
  //
  _rnd = new TRandom3(21231231);
  //
  nentries = fChain->GetEntriesFast();
  //
  jentry = 0;
  ientry = LoadTree(jentry);
  nb = fChain->GetEntry(jentry);  nbytes += nb;
  _UT_start = event_time;
  cout<<year<<" "<<month<<" "<<_UT_start<<endl;
  //
  jentry = nentries - 1;
  ientry = LoadTree(jentry);
  nb = fChain->GetEntry(jentry);  nbytes += nb;
  _UT_stop = event_time;
  cout<<year<<" "<<month<<" "<<_UT_stop<<endl;
  _dUT = _UT_stop - _UT_start;
}

void ana::Loop(TString histOut){
  //
  get_UT_first_and_last();
  //
  TH1D *h1_year = new TH1D("h1_year","h1_year", 7, 2019, 2025);
  TH1D *h1_month = new TH1D("h1_month","h1_month", 14, 0, 13);
  TH1D *h1_day = new TH1D("h1_day","h1_day", 33, 0, 32);
  TH1D *h1_ver = new TH1D("h1_ver","h1_ver", 3, 0, 3);
  TH1D *h1_nSubRun = new TH1D("h1_nSubRun","h1_nSubRun", 1000, 0, 1000);
  TH1D *h1_nMuonsPerRun = new TH1D("h1_nMuonsPerRun","h1_nMuonsPerRun", 1000, 0, 100000);
  //
  TH1D *h1_run_id = new TH1D("h1_run_id","h1_run_id", 10000, 0, 100000);
  //  
  //TH1D *h1_rate = new TH1D("h1_rate","h1_rate", (Int_t)_dUT/1000.0, 0, _dUT);
  //TH1D *h1_rate_cut = new TH1D("h1_rate_cut","h1_rate_cut", (Int_t)_dUT/1000.0, 0, _dUT);
  TH1D *h1_rate_all = new TH1D("h1_rate_all","h1_rate_all", (Int_t)_dUT/1000, _UT_start, _UT_stop);
  TH1D *h1_rate = new TH1D("h1_rate","h1_rate", (Int_t)_dUT/1000, _UT_start, _UT_stop);
  TH1D *h1_rate_cut = new TH1D("h1_rate_cut","h1_rate_cut", (Int_t)_dUT/1000, _UT_start, _UT_stop);
  TH1D *h1_rate_v9 = new TH1D("h1_rate_v9","h1_rate_v9", (Int_t)_dUT/1000, _UT_start, _UT_stop);
  TH1D *h1_rate_cut_v9 = new TH1D("h1_rate_cut_v9","h1_rate_cut_v9", (Int_t)_dUT/1000, _UT_start, _UT_stop);
  TH1D *h1_rate_v10 = new TH1D("h1_rate_v10","h1_rate_v10", (Int_t)_dUT/1000, _UT_start, _UT_stop);
  TH1D *h1_rate_cut_v10 = new TH1D("h1_rate_cut_v10","h1_rate_cut_v10", (Int_t)_dUT/1000, _UT_start, _UT_stop);

  //
  TH1D *h1_rate_9v = new TH1D("h1_rate_9v","h1_rate_9v", (Int_t)_dUT/100.0, 0, _dUT);
  TH1D *h1_rate_10v = new TH1D("h1_rate_10v","h1_rate_10v", (Int_t)_dUT/100.0, 0, _dUT);
  //
  TH1D *h1_good_ring = new TH1D("h1_good_ring","h1_good_ring", 10, -1.0, 2.0);
  //
  //
  TH1D *h1_ring_size_all = new TH1D("h1_ring_size_all","h1_ring_size_all", 1000, -100, 20000);
  TH1D *h1_size_outside_all = new TH1D("h1_size_outside_all","h1_size_outside_all",  200, -10, 30);
  TH1D *h1_muon_efficiency_all = new TH1D("h1_muon_efficiency_all","h1_muon_efficiency_all", 1000, -0.1, 1.1);
  TH1D *h1_ring_containment_all = new TH1D("h1_ring_containment_all","h1_ring_containment_all", 1000, -0.1, 1.1);
  TH1D *h1_ring_completeness_all = new TH1D("h1_ring_completeness_all","h1_ring_completeness_all", 1000, -0.1, 1.1);
  TH1D *h1_ring_width_all = new TH1D("h1_ring_width_all","h1_ring_width_all", 1000, 0.0, 0.5);
  //
  TH1D *h1_ring_size = new TH1D("h1_ring_size","h1_ring_size", 1000, -100, 20000);
  TH1D *h1_size_outside = new TH1D("h1_size_outside","h1_size_outside",  200, -10, 30);
  TH1D *h1_ring_center_x = new TH1D("h1_ring_center_x","h1_ring_center_x", 1000, -3.0, 3.0);
  TH1D *h1_ring_center_y = new TH1D("h1_ring_center_y","h1_ring_center_y", 1000, -3.0, 3.0);
  TH1D *h1_ring_radius = new TH1D("h1_ring_radius","h1_ring_radius", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_all = new TH1D("h1_ring_radius_all","h1_ring_radius_all", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_winter = new TH1D("h1_ring_radius_winter","h1_ring_radius_winter", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_summer = new TH1D("h1_ring_radius_summer","h1_ring_radius_summer", 1000, 0.0, 2.0);
  //
  TProfile *pr_ring_radius_vs_ut_all = new TProfile("pr_ring_radius_vs_ut_all","pr_ring_radius_vs_ut_all",  (Int_t)_dUT/100.0, _UT_start, _UT_stop);
  TProfile *pr_ring_radius_vs_ut = new TProfile("pr_ring_radius_vs_ut","pr_ring_radius_vs_ut",  (Int_t)_dUT/86400.000, 0, _dUT);
  TProfile *pr_ring_width_vs_ut = new TProfile("pr_ring_width_vs_ut","pr_ring_width_vs_ut",  (Int_t)_dUT/1000.0, 0, _dUT);
  TProfile *pr_muon_efficiency_vs_ut = new TProfile("pr_muon_efficiency_vs_ut","pr_muon_efficiency_vs_ut",  (Int_t)_dUT/1000.0, 0, _dUT);
  TProfile *pr_muon_efficiency_vs_ring_width = new TProfile("pr_muon_efficiency_vs_ring_width","pr_muon_efficiency_vs_ring_width", 400, 0.0, 0.11);
  TProfile *pr_muon_efficiency_vs_ring_radius = new TProfile("pr_muon_efficiency_vs_ring_radius","pr_muon_efficiency_vs_ring_radius", 400, 1.0, 1.3);
  //
  //  
  TH1D *h1_ring_radius_24year_11month_29day = new TH1D("h1_ring_radius_24year_11month_29day","h1_ring_radius_24year_11month_29day", 1000, 0.0, 2.0);
  TH2D *h2_ring_radius_24year_11month_29day = new TH2D("h2_ring_radius_24year_11month_29day","h2_ring_radius_24year_11month_29day", 1000, 0.0, 220000, 300, 0.8, 1.4);
  //
  TH1D *h1_ring_radius_1m = new TH1D("h1_ring_radius_1m","h1_ring_radius_1m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_2m = new TH1D("h1_ring_radius_2m","h1_ring_radius_2m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_3m = new TH1D("h1_ring_radius_3m","h1_ring_radius_3m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_4m = new TH1D("h1_ring_radius_4m","h1_ring_radius_4m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_5m = new TH1D("h1_ring_radius_5m","h1_ring_radius_5m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_6m = new TH1D("h1_ring_radius_6m","h1_ring_radius_6m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_7m = new TH1D("h1_ring_radius_7m","h1_ring_radius_7m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_8m = new TH1D("h1_ring_radius_8m","h1_ring_radius_8m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_9m = new TH1D("h1_ring_radius_9m","h1_ring_radius_9m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_10m = new TH1D("h1_ring_radius_10m","h1_ring_radius_10m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_11m = new TH1D("h1_ring_radius_11m","h1_ring_radius_11m", 1000, 0.0, 2.0);
  TH1D *h1_ring_radius_12m = new TH1D("h1_ring_radius_12m","h1_ring_radius_12m", 1000, 0.0, 2.0);
  //
  TH1D *h1_ring_size_3m = new TH1D("h1_ring_size_3m","h1_ring_size_3m", 1000, -100, 20000);
  TH1D *h1_ring_size_8m = new TH1D("h1_ring_size_8m","h1_ring_size_8m", 1000, -100, 20000);
  //  
  TH1D *h1_ring_width = new TH1D("h1_ring_width","h1_ring_width", 1000, 0.0, 0.5);
  //
  TH1D *h1_muon_efficiency = new TH1D("h1_muon_efficiency","h1_muon_efficiency", 1000, -0.1, 1.1);
  TH1D *h1_ring_containment = new TH1D("h1_ring_containment","h1_ring_containment", 1000, -0.1, 1.1);
  TH1D *h1_ring_completeness = new TH1D("h1_ring_completeness","h1_ring_completeness", 1000, -0.1, 1.1);
  TH1D *h1_impact_parameter = new TH1D("h1_impact_parameter","h1_impact_parameter", 1000, -0.1, 10.1);
  TH1D *h1_impact_x_array = new TH1D("h1_impact_x_array","h1_impact_x_array", 1000, -10.1, 10.1);
  TH1D *h1_impact_y_array = new TH1D("h1_impact_y_array","h1_impact_y_array", 1000, -10.1, 10.1);

  TH1D *h1_impact_r_array = new TH1D("h1_impact_r_array","h1_impact_r_array", 400, 0.0, 10.0);
  TH1D *h1_impact_r_array_w = new TH1D("h1_impact_r_array_w","h1_impact_r_array_w", 400, 0.0, 10.0);
  TH1D *h1_impact_r_array_norm = new TH1D("h1_impact_r_array_norm","h1_impact_r_array_norm", 400, 0.0, 10.0);

  TH1D *h1_radial_stdev = new TH1D("h1_radial_stdev","h1_radial_stdev", 1000, -10.1, 10.1);
  TH1D *h1_radial_skewness = new TH1D("h1_radial_skewness","h1_radial_skewness", 1000, -2.0, 2.0);
  TH1D *h1_radial_excess_kurtosis = new TH1D("h1_radial_excess_kurtosis","h1_radial_excess_kurtosis", 1000, -3.0, 3.0);
  TH1D *h1_num_pixels_in_ring = new TH1D("h1_num_pixels_in_ring","h1_num_pixels_in_ring", 1000, -10, 2000.0);
  TH1D *h1_mean_pixel_charge_around_ring = new TH1D("h1_mean_pixel_charge_around_ring","h1_mean_pixel_charge_around_ring", 300, -5.0, 5.0);  
  //
  //
  TH2D *h2_ring_size_vs_ut = new TH2D("h2_ring_size_vs_ut","h2_ring_size_vs_ut",  (Int_t)_dUT/10000.0, 0, _dUT, 30,0,3000);
  TProfile *pr_ring_size_vs_ut = new TProfile("pr_ring_size_vs_ut","pr_ring_size_vs_ut",  (Int_t)_dUT/1000.0, 0, _dUT);
  TProfile *pr_gauss_test_vs_ut = new TProfile("pr_gauss_test_vs_ut","pr_gauss_test_vs_ut",  (Int_t)_dUT/1000.0, 0, _dUT);
  //
  TProfile *pr_ring_width_vs_impact_r = new TProfile("pr_ring_width_vs_impact_r","pr_ring_width_vs_impact_r", 400, 0.0, 10.0);
  TProfile *pr_ring_width_vs_ring_radius_all = new TProfile("pr_ring_width_vs_ring_radius_all","pr_ring_width_vs_ring_radius_all", 400, 0.7, 1.4); 
  TProfile *pr_ring_width_vs_ring_radius = new TProfile("pr_ring_width_vs_ring_radius","pr_ring_width_vs_ring_radius", 400, 0.7, 1.4);
  //
  //  
  TH2D *h2_ring_radius_vs_ut = new TH2D("h2_ring_radius_vs_ut","h2_ring_radius_vs_ut",   (Int_t)_dUT/10000.0, 0, _dUT, 30,0.8,1.3);
  TH2D *h2_ring_radius_vs_ut_all = new TH2D("h2_ring_radius_vs_ut_all","h2_ring_radius_vs_ut_all",   (Int_t)_dUT/100000.0, 0, _dUT, 40,0.7,1.3);
  //
  TH2D *h2_ring_radius_vs_ring_size = new TH2D("h2_ring_radius_vs_ring_size","h2_ring_radius_vs_ring_size", 200, 800, 3000, 200, 0.8, 1.3);
  //
  TH2D *h2_ring_center_x_vs_y = new TH2D("h2_ring_center_x_vs_y","h2_ring_center_x_vs_y", 300, -3.0, 3.0, 300, -3.0, 3.0);
  TH2D *h2_impact_x_vs_y = new TH2D("h2_impact_x_vs_y","h2_impact_x_vs_y", 200, -13.0, 13.0, 200, -13.0, 13.0);
  TH2D *h2_impact_x_vs_y_all = new TH2D("h2_impact_x_vs_y_all","h2_impact_x_vs_y_all", 200, -13.0, 13.0, 200, -13.0, 13.0);
  TH2D *h2_impact_x_vs_y_w = new TH2D("h2_impact_x_vs_y_w","h2_impact_x_vs_y_w", 200, -13.0, 13.0, 200, -13.0, 13.0);
  TH2D *h2_impact_x_vs_y_norm = new TH2D("h2_impact_x_vs_y_norm","h2_impact_x_vs_y_norm", 200, -13.0, 13.0, 200, -13.0, 13.0);
  //
  TH1D *h1_ring_center_r_all = new TH1D("h1_ring_center_r_all","h1_ring_center_r_all", 300, 0.0, 3.0);  
  TH1D *h1_ring_center_r = new TH1D("h1_ring_center_r","h1_ring_center_r", 300, 0.0, 3.0);  
  //
  TH1D *h1_run_time_s = new TH1D("h1_run_time_s", "h1_run_time_s", 1000, 0.0, 10000.0);
  TGraph *gr_run_time_s_vs_UT = new TGraph();
  gr_run_time_s_vs_UT->SetNameTitle("gr_run_time_s_vs_UT","gr_run_time_s_vs_UT");
  //
  TGraph *gr_event_id_vs_ut = new TGraph();
  gr_event_id_vs_ut->SetNameTitle("gr_event_id_vs_ut","gr_event_id_vs_ut");
  //
  //
  TH1D *h1_nSubRun_per_run = new TH1D("h1_nSubRun_per_run", "h1_nSubRun_per_run", 1000, 0, 2000);
  TH1D *h1_nmuons_per_run = new TH1D("h1_nmuons_per_run", "h1_nmuons_per_run", 1000, 0, 25000);
  TH1D *h1_nmuons_per_run_9v = new TH1D("h1_nmuons_per_run_9v", "h1_nmuons_per_run_9v", 1000, 0, 25000);
  TH1D *h1_nmuons_per_run_10v = new TH1D("h1_nmuons_per_run_10v", "h1_nmuons_per_run_10v", 1000, 0, 25000);
  //  
  //
  //
  //
  TH1D *h1_runSelection_run_time_s = new TH1D("h1_runSelection_run_time_s", "h1_runSelection_run_time_s", 1000, 0.0, 10000.0);
  TH1D *h1_runSelection_nSubRun_per_run = new TH1D("h1_runSelection_nSubRun_per_run", "h1_runSelection_nSubRun_per_run", 1000, 0, 2000);
  TH1D *h1_runSelection_nmuons_per_run = new TH1D("h1_runSelection_nmuons_per_run", "h1_runSelection_nmuons_per_run", 1000, 0, 25000);
  TH1D *h1_runSelection_run_time_s_cut = new TH1D("h1_runSelection_run_time_s_cut", "h1_runSelection_run_time_s_cut", 1000, 0.0, 10000.0);
  TH1D *h1_runSelection_nSubRun_per_run_cut = new TH1D("h1_runSelection_nSubRun_per_run_cut", "h1_runSelection_nSubRun_per_run_cut", 1000, 0, 2000);
  TH1D *h1_runSelection_nmuons_per_run_cut = new TH1D("h1_runSelection_nmuons_per_run_cut", "h1_runSelection_nmuons_per_run_cut", 1000, 0, 25000);
  //
  //
  //
  //
  Int_t runID_max = 0;
  const Int_t runID_nn = 25000;
  Int_t run_ID_is_OK[runID_nn];
  Double_t run_time_start[runID_nn];
  Double_t run_time_stop[runID_nn];
  Int_t nmuons_per_run[runID_nn];
  Int_t nmuons_per_run_9v[runID_nn];
  Int_t nmuons_per_run_10v[runID_nn];
  Int_t nSubRun_per_run[runID_nn];
  Int_t run_ana_ver[runID_nn];
  Int_t run_year[runID_nn];
  Double_t run_times_list[runID_nn];
  for(Int_t i = 0;i<runID_nn;i++){
    run_time_start[i] = 0.0;
    run_time_stop[i] = 0.0;
    nmuons_per_run[i] = -1;
    nmuons_per_run_9v[i] = -1;
    nmuons_per_run_10v[i] = -1;
    nSubRun_per_run[i] = -1;
    run_ID_is_OK[i] = 1;
    run_ana_ver[i] = -1;
    run_year[i] = 0;
  }
  load_good_runs(runID_nn, run_ID_is_OK);
  //
  //
  load_run_time(runID_nn, run_times_list);
  //
  //
  Int_t mucounter = 0;
  //
  //
  Double_t impact_r_array;
  Double_t ring_center_r;
  //
  Long64_t nentries = fChain->GetEntriesFast();
  cout<<"nentries = "<<nentries<<endl;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    //if(jentry>1000000)
    //break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    //
    if(jentry%10000000 == 0)
      cout<<jentry<<endl;
    //
    impact_r_array = TMath::Sqrt(impact_x_array*impact_x_array + impact_y_array*impact_y_array);
    ring_center_r = TMath::Sqrt(ring_center_x*ring_center_x + ring_center_y*ring_center_y);
    //
    h1_rate_all->Fill(event_time,1.0/1000.0);
    //
    if(good_ring == 1){
      //
      if(year == 2025){
	if(month == 2){
	  if(day == 4){
	    h1_ring_radius_24year_11month_29day->Fill(ring_radius);
	    h2_ring_radius_24year_11month_29day->Fill(mucounter,ring_radius);
	    mucounter++;
	  }
	}
      }
      //
      h1_runSelection_run_time_s->Fill(run_times_list[run_id]);
      if(nSubRun_per_run[run_id] == -1){
	nSubRun_per_run[run_id] = nSubRun;
      }
      //
      if(nmuons_per_run[run_id] == -1){
	nmuons_per_run[run_id] = nMuonsPerRun;
	if(ver==0)
	  nmuons_per_run_9v[run_id] = nMuonsPerRun;
	if(ver==1)
	  nmuons_per_run_10v[run_id] = nMuonsPerRun;
      }
      //
      if(run_time_start[run_id] == 0.0){
	run_time_start[run_id] = event_time;
      }
      else{
	if(run_time_start[run_id]>event_time)
	  run_time_start[run_id] = event_time;
      }
      //
      if(run_time_stop[run_id] == 0.0){
	run_time_stop[run_id] = event_time;
      }
      else{
	if(run_time_stop[run_id]<event_time)
	  run_time_stop[run_id] = event_time;
      }
      //
      if(run_ana_ver[run_id] == -1){
	if(ver==0)
	  run_ana_ver[run_id] = 0;
	if(ver==1)
	  run_ana_ver[run_id] = 1;
      }
      if(run_year[run_id] == 0)
	run_year[run_id] = year;      
      //
      //
      //
      if(runID_max < run_id)
	runID_max = run_id;
      h1_run_id->Fill(run_id);
      //h1_rate->Fill(event_time - _UT_start,1.0/1000.0);
      h1_rate->Fill(event_time,1.0/1000.0);
      h2_impact_x_vs_y_all->Fill(impact_x_array,impact_y_array);
      h1_ring_radius_all->Fill(ring_radius);
      h1_ring_center_r_all->Fill(ring_center_r);
      //
      //
      if(ver==0)
	h1_rate_v9->Fill(event_time,1.0/1000.0);
      if(ver==1)
	h1_rate_v10->Fill(event_time,1.0/1000.0);
      //
      //
      h1_ring_size_all->Fill(ring_size);
      h1_size_outside_all->Fill(size_outside);
      h1_muon_efficiency_all->Fill(muon_efficiency);
      h1_ring_containment_all->Fill(ring_containment);
      h1_ring_completeness_all->Fill(ring_completeness);
      h1_ring_width_all->Fill(ring_width);
      h2_ring_radius_vs_ut_all->Fill(event_time - _UT_start,ring_radius);
      pr_ring_radius_vs_ut_all->Fill(event_time,ring_radius);
      pr_ring_width_vs_ring_radius_all->Fill(ring_radius,ring_width);
      //
      //
      //
      h1_runSelection_nSubRun_per_run->Fill(nSubRun);
      h1_runSelection_nmuons_per_run->Fill(nMuonsPerRun);
      //
      //
      if(run_ID_is_OK[run_id] == 1){
	h1_runSelection_nSubRun_per_run_cut->Fill(nSubRun);
	h1_runSelection_nmuons_per_run_cut->Fill(nMuonsPerRun);
	h1_runSelection_run_time_s_cut->Fill(run_times_list[run_id]);
	if(impact_y_array > 0.1 || impact_y_array < -0.1){
	  //if(true){
	  if(impact_r_array > 5.6 || impact_r_array < 5.4){
	    //if(true){
	    if(ring_center_r<1.1){
	      //if(true){
	      //if(ring_radius>1.02 && ring_radius<1.26){
	      //if(ring_radius>0.7 && ring_radius<1.3){
	       if(true){
		if(size_outside < 2.0){
		//if(true){
		  if(ring_size > 1000.0 && ring_size< 3200.0 ){
		    //if(true){
		    if(ring_completeness>0.7){
		      //if(true){
		      if(ring_containment>0.95){
			//if(true){
			//if(ring_width>0.02 && ring_width<0.13){
			if(true){
			  //if(muon_efficiency<0.45){
			  if(true){
			    //
			    //
			    h1_ring_center_r->Fill(ring_center_r);
			    gr_event_id_vs_ut->SetPoint(gr_event_id_vs_ut->GetN(),event_time,event_id);
			    //
			    //h1_rate_cut->Fill(event_time - _UT_start,1.0/1000.0);
			    h1_rate_cut->Fill(event_time,1.0/1000.0);
			    h1_rate_cut_v9->Fill(event_time,1.0/1000.0);
			    h1_rate_cut_v10->Fill(event_time,1.0/1000.0);
			    //
			    h1_year->Fill(year);
			    h1_month->Fill(month);
			    h1_day->Fill(day);
			    h1_ver->Fill(ver);
			    h1_nSubRun->Fill(nSubRun);
			    h1_nMuonsPerRun->Fill(nMuonsPerRun);
			    //
			    if(ver == 0)
			      h1_rate_9v->Fill(event_time - _UT_start);
			    if(ver == 1)
			      h1_rate_10v->Fill(event_time - _UT_start);
			    //      
			    h1_good_ring->Fill(good_ring);
			    //
			    //
			    h1_ring_size->Fill(ring_size);
			    h1_size_outside->Fill(size_outside);
			    h1_ring_center_x->Fill(ring_center_x);
			    h1_ring_center_y->Fill(ring_center_y);
			    h1_ring_radius->Fill(ring_radius);
			    //
			    if(month == 12 || month == 1 || month == 2)
			      h1_ring_radius_winter->Fill(ring_radius);
			    if(month == 6 || month == 7 || month == 8)
			      h1_ring_radius_summer->Fill(ring_radius);
			    //
			    if(month == 1)
			      h1_ring_radius_1m->Fill(ring_radius);
			    if(month == 2)
			      h1_ring_radius_2m->Fill(ring_radius);
			    if(month == 3){
			      h1_ring_radius_3m->Fill(ring_radius, 1.0/470796.0);
			      //if(year==2021)
			      h1_ring_size_3m->Fill(ring_size);
			    }
			    if(month == 4)
			      h1_ring_radius_4m->Fill(ring_radius);
			    if(month == 5)
			      h1_ring_radius_5m->Fill(ring_radius);
			    if(month == 6)
			      h1_ring_radius_6m->Fill(ring_radius);
			    if(month == 7)
			      h1_ring_radius_7m->Fill(ring_radius);
			    if(month == 8){
			      h1_ring_radius_8m->Fill(ring_radius, 1.0/312478.0);
			      //if(year==2021)
			      h1_ring_size_8m->Fill(ring_size);
			    }
			    if(month == 9)
			      h1_ring_radius_9m->Fill(ring_radius);
			    if(month == 10)
			      h1_ring_radius_10m->Fill(ring_radius);
			    if(month == 11)
			      h1_ring_radius_11m->Fill(ring_radius);
			    if(month == 12)
			      h1_ring_radius_12m->Fill(ring_radius);		  
			    //
			    h1_ring_width->Fill(ring_width);
			    //
			    h1_muon_efficiency->Fill(muon_efficiency);
			    h1_ring_containment->Fill(ring_containment);
			    h1_ring_completeness->Fill(ring_completeness);
			    h1_impact_parameter->Fill(impact_parameter);
			    h1_impact_x_array->Fill(impact_x_array);
			    h1_impact_y_array->Fill(impact_y_array);
			    h1_radial_stdev->Fill(radial_stdev);
			    h1_radial_skewness->Fill(radial_skewness);
			    h1_radial_excess_kurtosis->Fill(radial_excess_kurtosis);
			    h1_num_pixels_in_ring->Fill(num_pixels_in_ring);
			    h1_mean_pixel_charge_around_ring->Fill(mean_pixel_charge_around_ring);
			    //
			    h2_ring_size_vs_ut->Fill(event_time - _UT_start,ring_size);
			    pr_ring_size_vs_ut->Fill(event_time - _UT_start,ring_size);
			    pr_gauss_test_vs_ut->Fill(event_time - _UT_start,_rnd->Gaus(2200.0,200.0));
			    h2_ring_radius_vs_ut->Fill(event_time - _UT_start,ring_radius);
			    //
			    h2_ring_radius_vs_ring_size->Fill(ring_size, ring_radius);
			    //
			    h2_ring_center_x_vs_y->Fill(ring_center_x,ring_center_y);
			    h2_impact_x_vs_y->Fill(impact_x_array,impact_y_array);
			    //h2_impact_x_vs_y_w->Fill(impact_x_array,impact_y_array,ring_size);
			    //h2_impact_x_vs_y_w->Fill(impact_x_array,impact_y_array,ring_width);
			    h2_impact_x_vs_y_w->Fill(impact_x_array,impact_y_array, muon_efficiency);
			    //
			    //
			    h1_impact_r_array->Fill(impact_r_array);
			    h1_impact_r_array_w->Fill(impact_r_array, ring_width);
			    pr_ring_width_vs_impact_r->Fill(impact_r_array, ring_width);
			    //
			    //
			    pr_ring_radius_vs_ut->Fill(event_time - _UT_start,ring_radius);
			    pr_ring_width_vs_ut->Fill(event_time - _UT_start,ring_width);
			    pr_muon_efficiency_vs_ut->Fill(event_time - _UT_start,muon_efficiency);
			    pr_muon_efficiency_vs_ring_width->Fill(ring_width,muon_efficiency);
			    pr_muon_efficiency_vs_ring_radius->Fill(ring_radius,muon_efficiency);
			    //
			    pr_ring_width_vs_ring_radius->Fill(ring_radius,ring_width);
			    //
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	  //
	}
      }
    }
  }
  ///////////
  TGraph *gr_month_vs_ring_radius = new TGraph();
  gr_month_vs_ring_radius->SetNameTitle("gr_month_vs_ring_radius","gr_month_vs_ring_radius");
  if(h1_ring_radius_1m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 1.0, h1_ring_radius_1m->GetBinCenter(h1_ring_radius_1m->GetMaximumBin()));
  if(h1_ring_radius_2m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 2.0, h1_ring_radius_2m->GetBinCenter(h1_ring_radius_2m->GetMaximumBin()));
  if(h1_ring_radius_3m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 3.0, h1_ring_radius_3m->GetBinCenter(h1_ring_radius_3m->GetMaximumBin()));
  if(h1_ring_radius_4m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 4.0, h1_ring_radius_4m->GetBinCenter(h1_ring_radius_4m->GetMaximumBin()));
  if(h1_ring_radius_5m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 5.0, h1_ring_radius_5m->GetBinCenter(h1_ring_radius_5m->GetMaximumBin()));
  if(h1_ring_radius_6m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 6.0, h1_ring_radius_6m->GetBinCenter(h1_ring_radius_6m->GetMaximumBin()));
  if(h1_ring_radius_7m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 7.0, h1_ring_radius_7m->GetBinCenter(h1_ring_radius_7m->GetMaximumBin()));
  if(h1_ring_radius_8m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 8.0, h1_ring_radius_8m->GetBinCenter(h1_ring_radius_8m->GetMaximumBin()));
  if(h1_ring_radius_9m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 9.0, h1_ring_radius_9m->GetBinCenter(h1_ring_radius_9m->GetMaximumBin()));
  if(h1_ring_radius_10m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 10.0, h1_ring_radius_10m->GetBinCenter(h1_ring_radius_10m->GetMaximumBin()));
  if(h1_ring_radius_11m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 11.0, h1_ring_radius_11m->GetBinCenter(h1_ring_radius_11m->GetMaximumBin()));
  if(h1_ring_radius_12m->GetEntries()>10000)
    gr_month_vs_ring_radius->SetPoint( gr_month_vs_ring_radius->GetN(), 12.0, h1_ring_radius_12m->GetBinCenter(h1_ring_radius_12m->GetMaximumBin()));  
  ///////////
  //
  //
  TH1D *h1_mean_pr_gauss_test_vs_ut = new TH1D("h1_mean_pr_gauss_test_vs_ut","h1_mean_pr_gauss_test_vs_ut",1000,1000,3000);
  TH1D *h1_error_pr_gauss_test_vs_ut = new TH1D("h1_error_pr_gauss_test_vs_ut","h1_error_pr_gauss_test_vs_ut",1000,0,300);
  TH1D *h1_nen_pr_gauss_test_vs_ut = new TH1D("h1_nen_pr_gauss_test_vs_ut","h1_nen_pr_gauss_test_vs_ut",2000,0,10000);
  TGraphErrors *gr_pr_gauss_test_vs_ut = new TGraphErrors();
  gr_pr_gauss_test_vs_ut->SetNameTitle("gr_pr_gauss_test_vs_ut","gr_pr_gauss_test_vs_ut");
  analize_TProfile(pr_gauss_test_vs_ut, h1_mean_pr_gauss_test_vs_ut, h1_error_pr_gauss_test_vs_ut, h1_nen_pr_gauss_test_vs_ut, gr_pr_gauss_test_vs_ut,
		   200, 6.0, 10.0);
  //
  //
  TH1D *h1_mean_pr_ring_size_vs_ut = new TH1D("h1_mean_pr_ring_size_vs_ut","h1_mean_pr_ring_size_vs_ut",1000,1000,3000);
  TH1D *h1_error_pr_ring_size_vs_ut = new TH1D("h1_error_pr_ring_size_vs_ut","h1_error_pr_ring_size_vs_ut",1000,0,300);
  TH1D *h1_nen_pr_ring_size_vs_ut = new TH1D("h1_nen_pr_ring_size_vs_ut","h1_nen_pr_ring_size_vs_ut",2000,0,10000);
  TGraphErrors *gr_pr_ring_size_vs_ut = new TGraphErrors();
  gr_pr_ring_size_vs_ut->SetNameTitle("gr_pr_ring_size_vs_ut","gr_pr_ring_size_vs_ut");
  analize_TProfile( pr_ring_size_vs_ut, h1_mean_pr_ring_size_vs_ut, h1_error_pr_ring_size_vs_ut, h1_nen_pr_ring_size_vs_ut, gr_pr_ring_size_vs_ut,
		    200, 6.0, 10.0);
  //
  //
  TH1D *h1_mean_pr_ring_radius_vs_ut = new TH1D("h1_mean_pr_ring_radius_vs_ut","h1_mean_pr_ring_radius_vs_ut",1000,1.0,1.2);
  TH1D *h1_error_pr_ring_radius_vs_ut = new TH1D("h1_error_pr_ring_radius_vs_ut","h1_error_pr_ring_radius_vs_ut",1000,0,0.002);
  TH1D *h1_nen_pr_ring_radius_vs_ut = new TH1D("h1_nen_pr_ring_radius_vs_ut","h1_nen_pr_ring_radius_vs_ut",1000,0,200000.0);
  TGraphErrors *gr_pr_ring_radius_vs_ut = new TGraphErrors();
  gr_pr_ring_radius_vs_ut->SetNameTitle("gr_pr_ring_radius_vs_ut","gr_pr_ring_radius_vs_ut");
  analize_TProfile( pr_ring_radius_vs_ut, h1_mean_pr_ring_radius_vs_ut, h1_error_pr_ring_radius_vs_ut, h1_nen_pr_ring_radius_vs_ut, gr_pr_ring_radius_vs_ut,
		    1300, 0.0002, 0.0012);
  //
  TH1D *h1_mean_pr_muon_efficiency_vs_ut = new TH1D("h1_mean_pr_muon_efficiency_vs_ut","h1_mean_pr_muon_efficiency_vs_ut",1000,0,0.2);
  TH1D *h1_error_pr_muon_efficiency_vs_ut = new TH1D("h1_error_pr_muon_efficiency_vs_ut","h1_error_pr_muon_efficiency_vs_ut",1000,0,0.02);
  TH1D *h1_nen_pr_muon_efficiency_vs_ut = new TH1D("h1_nen_pr_muon_efficiency_vs_ut","h1_nen_pr_muon_efficiency_vs_ut",1000,0,2000.0);
  TGraphErrors *gr_pr_muon_efficiency_vs_ut = new TGraphErrors();
  gr_pr_muon_efficiency_vs_ut->SetNameTitle("gr_pr_muon_efficiency_vs_ut","gr_pr_muon_efficiency_vs_ut");
  analize_TProfile( pr_muon_efficiency_vs_ut, h1_mean_pr_muon_efficiency_vs_ut, h1_error_pr_muon_efficiency_vs_ut, h1_nen_pr_muon_efficiency_vs_ut, gr_pr_muon_efficiency_vs_ut,
		    200, 0.0002, 0.004);  
  //
  //
  TH1D *h1_mean_h1_rate = new TH1D("h1_mean_h1_rate","h1_mean_h1_rate",1000,0,20);
  TH1D *h1_error_h1_rate = new TH1D("h1_error_h1_rate","h1_error_h1_rate",1000,0,0.2);
  TH1D *h1_nen_h1_rate = new TH1D("h1_nen_h1_rate","h1_nen_h1_rate",1000,0,2000.0);
  TGraphErrors *gr_h1_rate = new TGraphErrors();
  gr_h1_rate->SetNameTitle("gr_h1_rate","gr_h1_rate");
  analize_TH1D(h1_rate, h1_mean_h1_rate, h1_error_h1_rate, h1_nen_h1_rate, gr_h1_rate, 1000, 100, 0.0, 0.12);
  //
  TH1D *h1_mean_h1_rate_cut = new TH1D("h1_mean_h1_rate_cut","h1_mean_h1_rate_cut",1000,0,20);
  TH1D *h1_error_h1_rate_cut = new TH1D("h1_error_h1_rate_cut","h1_error_h1_rate_cut",1000,0,0.2);
  TH1D *h1_nen_h1_rate_cut = new TH1D("h1_nen_h1_rate_cut","h1_nen_h1_rate_cut",1000,0,2000.0);
  TGraphErrors *gr_h1_rate_cut = new TGraphErrors();
  gr_h1_rate_cut->SetNameTitle("gr_h1_rate_cut","gr_h1_rate_cut");
  analize_TH1D(h1_rate_cut, h1_mean_h1_rate_cut, h1_error_h1_rate_cut, h1_nen_h1_rate_cut, gr_h1_rate_cut, 1000, 100, 0.0, 0.12);
  //
  TH1D *h1_mean_h1_rate_v9 = new TH1D("h1_mean_h1_rate_v9","h1_mean_h1_rate_v9",1000,0,20);
  TH1D *h1_error_h1_rate_v9 = new TH1D("h1_error_h1_rate_v9","h1_error_h1_rate_v9",1000,0,0.2);
  TH1D *h1_nen_h1_rate_v9 = new TH1D("h1_nen_h1_rate_v9","h1_nen_h1_rate_v9",1000,0,2000.0);
  TGraphErrors *gr_h1_rate_v9 = new TGraphErrors();
  gr_h1_rate_v9->SetNameTitle("gr_h1_rate_v9","gr_h1_rate_v9");
  analize_TH1D(h1_rate_v9, h1_mean_h1_rate_v9, h1_error_h1_rate_v9, h1_nen_h1_rate_v9, gr_h1_rate_v9, 1000, 100, 0.0, 0.12);
  //
  TH1D *h1_mean_h1_rate_v10 = new TH1D("h1_mean_h1_rate_v10","h1_mean_h1_rate_v10",1000,0,20);
  TH1D *h1_error_h1_rate_v10 = new TH1D("h1_error_h1_rate_v10","h1_error_h1_rate_v10",1000,0,0.2);
  TH1D *h1_nen_h1_rate_v10 = new TH1D("h1_nen_h1_rate_v10","h1_nen_h1_rate_v10",1000,0,2000.0);
  TGraphErrors *gr_h1_rate_v10 = new TGraphErrors();
  gr_h1_rate_v10->SetNameTitle("gr_h1_rate_v10","gr_h1_rate_v10");
  analize_TH1D(h1_rate_v10, h1_mean_h1_rate_v10, h1_error_h1_rate_v10, h1_nen_h1_rate_v10, gr_h1_rate_v10, 1000, 100, 0.0, 0.12);
  //
  //
  ///////////
  //
  TH2D_divide( h2_impact_x_vs_y_w, h2_impact_x_vs_y, h2_impact_x_vs_y_norm);
  TH1D_divide( h1_impact_r_array_w, h1_impact_r_array, h1_impact_r_array_norm);
  //
  ///////////
  ///////////
  //
  for(Int_t i = 0;i<runID_nn;i++){
    if(nSubRun_per_run[i]>-1){
      h1_nSubRun_per_run->Fill(nSubRun_per_run[i]);
      h1_nmuons_per_run->Fill(nmuons_per_run[i]);
      h1_nmuons_per_run_9v->Fill(nmuons_per_run_9v[i]);
      h1_nmuons_per_run_10v->Fill(nmuons_per_run_10v[i]);
    }
    if((run_time_start[i] != 0.0) && (run_time_stop[i] != 0.0)){
      h1_run_time_s->Fill(run_time_stop[i] - run_time_start[i]);
      gr_run_time_s_vs_UT->SetPoint(gr_run_time_s_vs_UT->GetN(),run_time_start[i],run_time_stop[i] - run_time_start[i]);
    }
  } 
  //
  save_good_runs_IDs( runID_nn, run_ID_is_OK,
		      run_time_start, run_time_stop,
		      nSubRun_per_run, nmuons_per_run, run_ana_ver, run_year);
  save_run_time( runID_nn, run_ID_is_OK, run_time_start, run_time_stop);
  //
  ///////////
  TFile* rootFile = new TFile(histOut.Data(), "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<histOut.Data()<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<histOut.Data()<<endl;
  //
  h1_year->Write();
  h1_month->Write();
  h1_day->Write();
  h1_ver->Write();
  h1_nSubRun->Write();
  h1_nMuonsPerRun->Write();
  //
  h1_good_ring->Write();
  //
  //
  h1_rate->Write();
  h1_rate_all->Write();
  h1_mean_h1_rate->Write();
  h1_error_h1_rate->Write();
  h1_nen_h1_rate->Write();
  gr_h1_rate->Write();
  //
  h1_rate_cut->Write();
  h1_mean_h1_rate_cut->Write();
  h1_error_h1_rate_cut->Write();
  h1_nen_h1_rate_cut->Write();
  gr_h1_rate_cut->Write();
  //
  //
  //
  h1_rate_9v->Write();
  h1_rate_10v->Write();
  //
  h1_ring_size->Write();
  h1_ring_size_3m->Write();
  h1_ring_size_8m->Write();
  h1_size_outside->Write();
  h1_ring_center_x->Write();
  h1_ring_center_y->Write();
  h1_ring_radius->Write();
  h1_ring_radius_all->Write();
  h1_ring_radius_winter->Write();
  h1_ring_radius_summer->Write();
  //
  h1_ring_radius_1m->Write();
  h1_ring_radius_2m->Write();
  h1_ring_radius_3m->Write();
  h1_ring_radius_4m->Write();
  h1_ring_radius_5m->Write();
  h1_ring_radius_6m->Write();
  h1_ring_radius_7m->Write();
  h1_ring_radius_8m->Write();
  h1_ring_radius_9m->Write();
  h1_ring_radius_10m->Write();
  h1_ring_radius_11m->Write();
  h1_ring_radius_12m->Write();
  //  
  h1_ring_width->Write();
  //
  h1_muon_efficiency->Write();
  h1_ring_containment->Write();
  h1_ring_completeness->Write();
  h1_impact_parameter->Write();
  h1_impact_x_array->Write();
  h1_impact_y_array->Write();
  h1_radial_stdev->Write();
  h1_radial_skewness->Write();
  h1_radial_excess_kurtosis->Write();
  h1_num_pixels_in_ring->Write();
  h1_mean_pixel_charge_around_ring->Write();
  //
  h2_ring_size_vs_ut->Write();
  //
  pr_ring_size_vs_ut->Write();
  h1_mean_pr_ring_size_vs_ut->Write();
  h1_error_pr_ring_size_vs_ut->Write();
  h1_nen_pr_ring_size_vs_ut->Write();
  gr_pr_ring_size_vs_ut->Write();
  //
  pr_gauss_test_vs_ut->Write();
  h1_mean_pr_gauss_test_vs_ut->Write();
  h1_error_pr_gauss_test_vs_ut->Write();
  h1_nen_pr_gauss_test_vs_ut->Write();
  gr_pr_gauss_test_vs_ut->Write();
  //
  h2_ring_radius_vs_ut->Write();
  //
  h2_ring_radius_vs_ring_size->Write();
  h2_ring_center_x_vs_y->Write();
  h2_impact_x_vs_y->Write();
  h2_impact_x_vs_y_all->Write();
  h2_impact_x_vs_y_w->Write();
  h2_impact_x_vs_y_norm->Write();
  //
  gr_month_vs_ring_radius->Write();
  //
  pr_ring_width_vs_ut->Write();
  pr_muon_efficiency_vs_ut->Write();
  //
  h1_mean_pr_muon_efficiency_vs_ut->Write();
  h1_error_pr_muon_efficiency_vs_ut->Write();
  h1_nen_pr_muon_efficiency_vs_ut->Write();
  gr_pr_muon_efficiency_vs_ut->Write();
  //
  //
  pr_ring_radius_vs_ut->Write();
  h1_mean_pr_ring_radius_vs_ut->Write();
  h1_error_pr_ring_radius_vs_ut->Write();
  h1_nen_pr_ring_radius_vs_ut->Write();
  gr_pr_ring_radius_vs_ut->Write();
  //
  h1_impact_r_array->Write();
  h1_impact_r_array_w->Write();
  h1_impact_r_array_norm->Write();
  pr_ring_width_vs_impact_r->Write();
  pr_muon_efficiency_vs_ring_width->Write();
  //
  pr_muon_efficiency_vs_ring_radius->Write();
  gr_event_id_vs_ut->Write();
  //
  h1_ring_size_all->Write();
  h1_size_outside_all->Write();
  h1_muon_efficiency_all->Write();
  h1_ring_containment_all->Write();
  h1_ring_completeness_all->Write();
  h1_ring_width_all->Write();
  h2_ring_radius_vs_ut_all->Write();
  //
  h1_ring_center_r_all->Write();
  h1_ring_center_r->Write();
  //
  pr_ring_radius_vs_ut_all->Write();
  //
  h1_rate_v9->Write();
  h1_mean_h1_rate_v9->Write();
  h1_error_h1_rate_v9->Write();
  h1_nen_h1_rate_v9->Write();
  gr_h1_rate_v9->Write();
  //
  h1_rate_v10->Write();
  h1_mean_h1_rate_v10->Write();
  h1_error_h1_rate_v10->Write();
  h1_nen_h1_rate_v10->Write();
  gr_h1_rate_v10->Write();
  //
  //  
  //
  h1_run_id->Write();
  h1_run_time_s->Write();
  gr_run_time_s_vs_UT->Write();
  h1_nSubRun_per_run->Write();
  h1_nmuons_per_run->Write();
  h1_nmuons_per_run_9v->Write();
  h1_nmuons_per_run_10v->Write();
  //
  h1_runSelection_nSubRun_per_run->Write();
  h1_runSelection_nmuons_per_run->Write();
  h1_runSelection_nSubRun_per_run_cut->Write();
  h1_runSelection_nmuons_per_run_cut->Write();
  h1_runSelection_run_time_s->Write();
  h1_runSelection_run_time_s_cut->Write();
  //
  h1_ring_radius_24year_11month_29day->Write();
  h2_ring_radius_24year_11month_29day->Write();
  //
  pr_ring_width_vs_ring_radius->Write();
  pr_ring_width_vs_ring_radius_all->Write();  
  //
  cout<<"runID_max = "<<runID_max<<endl;
  //
  rootFile->Close();
}

void ana::analize_TProfile(TProfile *pr, TH1D *h1_mean, TH1D *h1_error, TH1D *h1_nen, TGraphErrors *gr, Int_t nMinEntries, Double_t error_min, Double_t error_max){
  Double_t xval;
  Double_t yval;
  Double_t xval_err;
  Double_t yval_err;
  Int_t counter = 0;
  for(Int_t i = 0;i<pr->GetNbinsX();i++){
    if(pr->GetBinEntries(i)>0){
      h1_mean->Fill(pr->GetBinContent(i));
      h1_error->Fill(pr->GetBinError(i));
      h1_nen->Fill(pr->GetBinEntries(i));
      if( pr->GetBinEntries(i) > nMinEntries){
	if( pr->GetBinError(i) > error_min && pr->GetBinError(i) < error_max){
	  //
	  xval = pr->GetBinCenter(i);
	  yval = pr->GetBinContent(i);
	  xval_err = 0.0;
	  yval_err = pr->GetBinError(i);
	  //
	  gr->SetPoint(counter, xval, yval);
	  gr->SetPointError(counter, xval_err, yval_err);
	  counter++;
	}
      }
    }
  }  
}

void ana::analize_TH1D(TH1D *h1, TH1D *h1_mean, TH1D *h1_error, TH1D *h1_nen, TGraphErrors *gr, Double_t nsec, Int_t nMinEntries, Double_t error_min, Double_t error_max){
  Double_t xval;
  Double_t yval;
  Double_t xval_err;
  Double_t yval_err;
  Int_t counter = 0;
  for(Int_t i = 0;i<h1->GetNbinsX();i++){
    if(h1->GetBinContent(i)>0){
      h1_mean->Fill(h1->GetBinContent(i));
      h1_error->Fill(h1->GetBinError(i));
      h1_nen->Fill(h1->GetBinContent(i)*nsec);
      if( h1->GetBinContent(i)*nsec > nMinEntries){
	if( h1->GetBinError(i) > error_min && h1->GetBinError(i) < error_max){
	  //
	  xval = h1->GetBinCenter(i);
	  yval = h1->GetBinContent(i);
	  xval_err = 0.0;
	  yval_err = h1->GetBinError(i);
	  //
	  gr->SetPoint(counter, xval, yval);
	  gr->SetPointError(counter, xval_err, yval_err);
	  counter++;
	}
      }
    }
  }  
}

void ana::load_good_runs(Int_t runID_nn, Int_t *run_ID_is_OK){
  //
  ifstream fFile(_good_runs_file.Data());
  Int_t runID_is_ok;  
  //
  if(fFile.is_open()){
    //
    for(Int_t i = 0;i<runID_nn;i++)
      run_ID_is_OK[i] = 0;
    //
    cout<<"_good_runs_file = "<<_good_runs_file<<std::endl;
    while(fFile>>runID_is_ok){
      if(runID_is_ok>0 && runID_is_ok<runID_nn)
	run_ID_is_OK[runID_is_ok] = 1;
    }
    fFile.close();
  }
  else{
    for(Int_t i = 0;i<runID_nn;i++)
      run_ID_is_OK[i] = 1;
  }
  //
}

void ana::save_good_runs_IDs(Int_t runID_nn, Int_t *run_ID_is_OK,
			     Double_t *run_time_start, Double_t *run_time_stop,
			     Int_t *nSubRun_per_run, Int_t *nmuons_per_run,
			     Int_t *run_ana_ver, Int_t *run_year){
  ofstream outfile;
  outfile.open(_good_runs_file.Data());
  Double_t run_time_tot = 0.0;
  for(Int_t i = 0;i<runID_nn;i++){
    if((run_time_start[i] != 0.0) && (run_time_stop[i] != 0.0)){
      run_time_tot = run_time_stop[i] - run_time_start[i];
      //if(run_time_tot>600 && run_time_tot<1400){
      //if(nSubRun_per_run[i]>50 && nSubRun_per_run[i]<200){
      //if(nmuons_per_run[i]>2000 && nmuons_per_run[i]<11500){
      //if(run_ana_ver[i] == 1){
      //if(run_year[i] > 2023){
      outfile<<i<<endl;
      //}
      //}
      //}
      //}
      //}
    }
  }
  //
  outfile.close();
}
 
void ana::save_run_time(Int_t runID_nn, Int_t *run_ID_is_OK,
			Double_t *run_time_start, Double_t *run_time_stop){
  ofstream outfile;
  outfile.open(_run_time_file.Data());
  Double_t run_time_tot = 0.0;
  for(Int_t i = 0;i<runID_nn;i++){
    if((run_time_start[i] != 0.0) && (run_time_stop[i] != 0.0)){
      run_time_tot = run_time_stop[i] - run_time_start[i];
      outfile<<run_time_tot<<endl;
    }
    else{
      run_time_tot = 0.0;
      outfile<<run_time_tot<<endl;
    }
  }
  //
  outfile.close();
}

void ana::load_run_time(Int_t runID_nn, Double_t *run_times_list){
  ifstream fFile(_run_time_file.Data());
  Double_t run_time_tot = 0.0;
  //
  if(fFile.is_open()){
    for(Int_t i = 0;i<runID_nn;i++){
      fFile>>run_time_tot;
      run_times_list[i] = run_time_tot;
    }
    fFile.close();
  }
  else{
    for(Int_t i = 0;i<runID_nn;i++)
      run_times_list[i] = 0.0;
  }
  //
}
