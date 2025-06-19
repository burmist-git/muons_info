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

Int_t plot_subRunlist(){
  //
  //
  UInt_t rdt;
  UInt_t rdt_START = TDatime(2019,11,23,0,0,0).Convert(); //20191123
  UInt_t rdt_STOP  = TDatime(2025, 2,28,0,0,0).Convert(); //20250228
  UInt_t cumbre_Vieja_volcanic_eruption_START = TDatime(2021, 9,19,0,0,0).Convert();
  UInt_t cumbre_Vieja_volcanic_eruption_STOP  = TDatime(2021,12,13,0,0,0).Convert();  
  UInt_t covid_START = TDatime(2020,3,2,0,0,0).Convert();
  UInt_t covid_STOP  = TDatime(2020,6,7,0,0,0).Convert();  
  UInt_t struct_START = TDatime(2022,7,1,0,0,0).Convert();
  UInt_t struct_STOP  = TDatime(2022,9,15,0,0,0).Convert();  
  Double_t rdt_START_d = (Double_t)rdt_START;
  Double_t rdt_STOP_d  = (Double_t)rdt_STOP;
  Double_t cumbre_Vieja_volcanic_eruption_START_d = (Double_t)cumbre_Vieja_volcanic_eruption_START;
  Double_t cumbre_Vieja_volcanic_eruption_STOP_d  = (Double_t)cumbre_Vieja_volcanic_eruption_STOP;
  Double_t covid_START_d = (Double_t)covid_START;
  Double_t covid_STOP_d  = (Double_t)covid_STOP;
  Double_t struct_START_d = (Double_t)struct_START;
  Double_t struct_STOP_d  = (Double_t)struct_STOP;
  //
  cout<<"Unix Time START                "<<rdt_START<<endl
      <<"Unix Time STOP                 "<<rdt_STOP<<endl;
  cout<<"Unix Time Vieja volcanic START "<<cumbre_Vieja_volcanic_eruption_START<<endl
      <<"Unix Time Vieja volcanic STOP  "<<cumbre_Vieja_volcanic_eruption_STOP<<endl;
  //
  //  
  //
  Int_t entry_ID;
  TString subRunlist;
  TString date;
  TString year;
  TString month;
  TString day;
  TString ver;
  TString name;
  TString runID;
  TString subRunID;
  Int_t date_int;
  Int_t year_int;
  Int_t month_int;
  Int_t day_int;
  Int_t runID_int;
  Int_t subRunID_int; 
  string mot;
  Int_t counter = 0;
  //  
  ifstream csvfFile("subRunlist_for_root.csv");
  Int_t i = 0;
  for(i = 0;i<15;i++)
    csvfFile>>mot;
  //
  TGraph *gr_entry_ID = new TGraph();
  gr_entry_ID->SetNameTitle("gr_entry_ID","gr_entry_ID");
  TGraph *gr_date_int = new TGraph();
  gr_date_int->SetNameTitle("gr_date_int","gr_date_int");
  TGraph *gr_year_int = new TGraph();
  gr_year_int->SetNameTitle("gr_year_int","gr_year_int");
  TGraph *gr_month_int = new TGraph();
  gr_month_int->SetNameTitle("gr_month_int","gr_month_int");
  TGraph *gr_day_int = new TGraph();
  gr_day_int->SetNameTitle("gr_day_int","gr_day_int");
  TGraph *gr_runID_int = new TGraph();
  gr_runID_int->SetNameTitle("gr_runID_int","gr_runID_int");
  TGraph *gr_runID_int_ver9 = new TGraph();
  gr_runID_int_ver9->SetNameTitle("gr_runID_int_ver9","gr_runID_int_ver9");
  TGraph *gr_runID_int_ver10 = new TGraph();
  gr_runID_int_ver10->SetNameTitle("gr_runID_int_ver10","gr_runID_int_ver10");
  TGraph *gr_subRunID_int = new TGraph();
  gr_subRunID_int->SetNameTitle("gr_subRunID_int","gr_subRunID_int");
  //
  TH1D *h1_subRun_tot = new TH1D("h1_subRun_tot","h1_subRun_tot",2000, rdt_START_d-5*3600*24.0, rdt_STOP_d+5*3600*24.0);
  TH1D *h1_subRun_tot_v9 = new TH1D("h1_subRun_tot_v9","h1_subRun_tot_v9",2000, rdt_START_d-5*3600*24.0, rdt_STOP_d+5*3600*24.0);
  TH1D *h1_subRun_tot_v10 = new TH1D("h1_subRun_tot_v10","h1_subRun_tot_v10",2000, rdt_START_d-5*3600*24.0, rdt_STOP_d+5*3600*24.0);
  TH1D *h1_Cumbre_Vieja_volcanic_eruption_tot = new TH1D("h1_Cumbre_Vieja_volcanic_eruption_tot","h1_Cumbre_Vieja_volcanic_eruption_tot",2000, rdt_START_d-5*3600*24.0, rdt_STOP_d+5*3600*24.0);
  TH1D *h1_covid_tot = new TH1D("h1_covid_tot","h1_covid_tot",2000, rdt_START_d-5*3600*24.0, rdt_STOP_d+5*3600*24.0);
  TH1D *h1_struct_tot = new TH1D("h1_struct_tot","h1_struct_tot",2000, rdt_START_d-5*3600*24.0, rdt_STOP_d+5*3600*24.0);
  //
  while(csvfFile>>
	entry_ID>>
	subRunlist>>
	date>>
	year>>
	month>>
	day>>
	ver>>
	name>>
	runID>>
	subRunID>>
	date_int>>
	year_int>>
	month_int>>
	day_int>>
	runID_int>>
	subRunID_int){
    //
    rdt = TDatime(year_int,month_int,day_int,0,0,0).Convert();
    //
    gr_entry_ID->SetPoint(gr_entry_ID->GetN(),counter,entry_ID);
    gr_date_int->SetPoint(gr_date_int->GetN(),counter,date_int);
    gr_year_int->SetPoint(gr_year_int->GetN(),counter,year_int);
    gr_month_int->SetPoint(gr_month_int->GetN(),counter,month_int);
    gr_day_int->SetPoint(gr_day_int->GetN(),counter,day_int);
    gr_runID_int->SetPoint(gr_runID_int->GetN(),counter,runID_int);
    gr_subRunID_int->SetPoint(gr_subRunID_int->GetN(),counter,subRunID_int);
    //    
    h1_subRun_tot->Fill(rdt);
    //
    if(ver == "v0.9"){
      gr_runID_int_ver9->SetPoint(gr_runID_int_ver9->GetN(),counter,runID_int);
      h1_subRun_tot_v9->Fill(rdt);
    }
    if(ver == "v0.10"){
      gr_runID_int_ver10->SetPoint(gr_runID_int_ver10->GetN(),counter,runID_int);    
      h1_subRun_tot_v10->Fill(rdt);
    }
    //
    //
    counter++;
  }
  //
  //
  for(Int_t jj = 1; jj<=h1_Cumbre_Vieja_volcanic_eruption_tot->GetNbinsX();jj++){
    Double_t ut_time = h1_Cumbre_Vieja_volcanic_eruption_tot->GetBinCenter(jj);
    if(ut_time>=cumbre_Vieja_volcanic_eruption_START_d && ut_time<=cumbre_Vieja_volcanic_eruption_STOP_d)
      h1_Cumbre_Vieja_volcanic_eruption_tot->SetBinContent(jj,8000);
    if(ut_time>=covid_START_d && ut_time<=covid_STOP_d)
      h1_covid_tot->SetBinContent(jj,8000);
    if(ut_time>=struct_START_d && ut_time<=struct_STOP_d)
      h1_struct_tot->SetBinContent(jj,8000);
  }
  //  
  //
  //
  //
  //----------------------
  TFile* rootFile = new TFile("hist_subRunlist_for_root.root", "RECREATE", " Histograms", 1);
  rootFile->cd();
  if (rootFile->IsZombie()){
    cout<<"  ERROR ---> file "<<"hist_subRunlist_for_root.root"<<" is zombi"<<endl;
    assert(0);
  }
  else
    cout<<"  Output Histos file ---> "<<"hist_subRunlist_for_root.root"<<endl;
  //----------------------
  //
  //
  gr_entry_ID->Write();
  gr_date_int->Write();
  gr_year_int->Write();
  gr_month_int->Write();
  gr_day_int->Write();
  gr_runID_int->Write();
  gr_subRunID_int->Write();
  //
  gr_runID_int_ver9->Write();
  gr_runID_int_ver10->Write();
  //
  h1_subRun_tot->Write();
  h1_subRun_tot_v9->Write();
  h1_subRun_tot_v10->Write();
  h1_Cumbre_Vieja_volcanic_eruption_tot->Write();
  h1_covid_tot->Write();
  h1_struct_tot->Write();
  //
  rootFile->Close();
  //
  //gr_entry_ID->Draw("AL");  
  //
  //
  return 0;
}


//
//struct tm tm;
//tm.tm_year = 1970;
//tm.tm_mon = 1;
//tm.tm_mday = 1;
//tm.tm_hour = 0;
//tm.tm_min = 0;
//tm.tm_sec = 0;

//time_t epoch;
//if (strptime(timestamp, "%Y-%m-%d %H:%M:%S", &tm) != NULL )
//epoch = mktime(&tm);
//cout<<epoch<<endl;

//struct tm*t1(getdate("2018-03-31 14:35:46"));
//cout<<mktime(struct tm*t1(getdate("2018-03-31 14:35:46")))<<endl;

//Int_t ut = time();
//UInt_t rdt = TDatime("2025-03-12 14:04:00").Convert();
//1574463600
//1574463600
//auto t=new TTimeStamp();
//Int_t tts = t->GetSec();20191123

//cout<<"TDatime     ut "<<ut<<endl;
//cout<<"Unix Time  rdt "<<rdt<<endl;
//cout      <<"TTimeStamp tts "<<tts<<endl;

//1763989440
//  1741784420
//1741784428

//time_t timer;
//struct tm y2k = {0};
//double seconds;
//y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
//y2k.tm_year = 1970; y2k.tm_mon = 0; y2k.tm_mday = 1;
//time(&timer);  /* get current time; same as: timer = time(NULL)  */
//seconds = difftime(timer,mktime(&y2k));
//seconds = mktime(&y2k);
//printf ("%.f seconds since January 1, 2000 in the current timezone", seconds);

//struct tm tm;
//tm.tm_year = 2000;
//tm.tm_mon = 1;
//tm.tm_mday = 1;  
//tm.tm_hour = 0;
//tm.tm_min = 0;
//tm.tm_sec = 0;
//Double_t seconds = mktime(&tm);
//cout<<seconds<<endl;
