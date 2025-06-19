//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include <TStyle.h>
#include <TString.h>
#include <TCanvas.h>
#include <TTree.h>

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <vector>

//    event_id         event_time mc_energy ring_size size_outside      ring_center_x         ring_center_y        ring_radius           ring_width good_ring
//  0     2233 1616043367.4801488        -1 1313.6748          0.0 1.7631084714391794 -0.029207557241448762 1.1406419693006173 0.049938869309114356      True
//
//     muon_efficiency   ring_containment  ring_completeness  impact_parameter     impact_x_array     impact_y_array        radial_stdev     radial_skewness radial_excess_kurtosis
//   0.18003822137448863 0.5574888519065161 0.4666666666666667 6.394059947440662 3.0075574514486862 5.6425704060915685 0.05169791240472212 0.25072495213055473   -0.11526503923818998
//
// num_pixels_in_ring  mean_pixel_charge_around_ring hg_peak_sample lg_peak_sample
//                270            0.13006921416347467             17              0

struct muonfileStr {
  //
  Int_t run_id;
  Int_t year;
  Int_t month;
  Int_t day;
  Int_t ver;
  Int_t nSubRun;
  //
  Int_t event_id;
  Double_t event_time;
  Float_t mc_energy;
  Float_t ring_size;
  Float_t size_outside;
  Float_t ring_center_x;
  Float_t ring_center_y;
  Float_t ring_radius;
  Float_t ring_width;
  Int_t good_ring;
  Float_t muon_efficiency;
  Float_t ring_containment;
  Float_t ring_completeness;
  Float_t impact_parameter;
  Float_t impact_x_array;
  Float_t impact_y_array;
  Float_t radial_stdev;
  Float_t radial_skewness;
  Float_t radial_excess_kurtosis;
  Float_t num_pixels_in_ring;
  Float_t mean_pixel_charge_around_ring;
  Float_t hg_peak_sample;
  Float_t lg_peak_sample;
};
std::vector<muonfileStr> _muonfileStr_vec;


//run_id year month day ver outputcsv nlines_csv nSubRun
//0 1615 2019 11 23 v0.9 /home/burmist/home2/work/CTA/muons_DL1_tar_gz/20191123/v0.9/muons_LST-1.Run01615.csv 13911 61
//1 1616 2019 11 23 v0.9 /home/burmist/home2/work/CTA/muons_DL1_tar_gz/20191123/v0.9/muons_LST-1.Run01616.csv 14321 62
//2 1617 2019 11 23 v0.9 /home/burmist/home2/work/CTA/muons_DL1_tar_gz/20191123/v0.9/muons_LST-1.Run01617.csv 7725 35
struct muonfileListStr {
  Int_t run_id;
  Int_t year;
  Int_t month;
  Int_t day;
  Int_t ver;
  Int_t nSubRun;
};
std::vector<muonfileListStr> _muonfileListStr_vec;

void read_file(TString file_name, Int_t run_id,  Int_t year,  Int_t month,  Int_t day,  Int_t ver,  Int_t nSubRun);
void convert2root(const std::vector<TString> &fileList_v, TString outputRootFile);
void load_file_list( std::vector<TString> &fileList_v, TString inFileList);

using namespace std;

int main(int argc, char *argv[]){
  //
  clock_t start, finish;
  start = clock();
  //
  if(argc == 4 && atoi(argv[1]) == 0){
    //
    TString fileList_file = argv[2];
    TString outputRootFile = argv[3];
    std::cout<<std::endl
	     <<"fileList_file    "<<fileList_file<<std::endl
	     <<"outputRootFile   "<<outputRootFile<<std::endl;
    //
    std::vector<TString> fileList_v;
    load_file_list(fileList_v, fileList_file);
    convert2root(fileList_v, outputRootFile);
    //
  }
  else{
    std::cout<<"  runID [1] = 0        "<<std::endl
	     <<"        [2] - fileList_file  "<<std::endl
	     <<"        [3] - outputRootFile "<<std::endl;
  }  //
  finish = clock();
  std::cout<<"-------------------------"<<std::endl
  	   <<"Working time : "<<((finish - start)/CLOCKS_PER_SEC)<<" (sec)"<<std::endl
  	   <<"-------------------------"<<std::endl;
  //
  return 0;
}

//run_id year month day ver outputcsv nlines_csv nSubRun
//0 1615 2019 11 23 v0.9 /home/burmist/home2/work/CTA/muons_DL1_tar_gz/20191123/v0.9/muons_LST-1.Run01615.csv 13911 61
//1 1616 2019 11 23 v0.9 /home/burmist/home2/work/CTA/muons_DL1_tar_gz/20191123/v0.9/muons_LST-1.Run01616.csv 14321 62
//2 1617 2019 11 23 v0.9 /home/burmist/home2/work/CTA/muons_DL1_tar_gz/20191123/v0.9/muons_LST-1.Run01617.csv 7725 35
void load_file_list( std::vector<TString> &fileList_v, TString inFileList){
  //
  Int_t verbosity = 1;
  std::ifstream fFile(inFileList.Data());
  if(verbosity>0)
    std::cout<<" inFileList --> "<<inFileList<<std::endl;
  //
  //
  TString mot;
  Int_t run_id;
  Int_t year;
  Int_t month;
  Int_t day;
  TString ver;
  TString the_file;
  Int_t nlines_csv;
  Int_t nSubRun;
  //
  if(fFile.is_open()){
    for(Int_t i = 0;i<8;i++)
      fFile>>mot;
    while(fFile>>
	  mot>>
	  run_id>>
	  year>>
	  month>>
	  day>>
	  ver>>
	  the_file>>
	  nlines_csv>>
	  nSubRun){
      //
      fileList_v.push_back(the_file);
      //
      muonfileListStr mfl;
      mfl.run_id = run_id;
      mfl.year = year;
      mfl.month = month;
      mfl.day = day;
      if(ver == "v0.9")
	mfl.ver = 0;
      else if(ver == "v0.10")
	mfl.ver = 1;
      else
	mfl.ver = -1;
      mfl.nSubRun = nSubRun;
      _muonfileListStr_vec.push_back(mfl);
      //
      if(verbosity>1)
	std::cout<<run_id<<" "<<year<<" "<<the_file<<endl;
    }
    fFile.close();
  }
}

void convert2root(const std::vector<TString> &fileList_v, TString outputRootFile){
  for(unsigned int i = 0; i < fileList_v.size(); i++)
    read_file(fileList_v.at(i),
	      _muonfileListStr_vec.at(i).run_id,
	      _muonfileListStr_vec.at(i).year,
	      _muonfileListStr_vec.at(i).month,
	      _muonfileListStr_vec.at(i).day,
	      _muonfileListStr_vec.at(i).ver,
	      _muonfileListStr_vec.at(i).nSubRun);
  //
  //
  TFile *hfile = new TFile(outputRootFile, "RECREATE", "Simtel log data", 1);
  if (hfile->IsZombie()) {
    std::cout<<" ---> ERROR : PROBLEM with the initialization of the output ROOT file : "<<std::endl
	     <<outputRootFile
	     <<std::endl;
    assert(0);
  }
  TTree *tree = new TTree("T", "data");
  hfile->SetCompressionLevel(2);
  tree->SetAutoSave(1000000);  
  // Create new event
  TTree::SetBranchStyle(0);
  ///////////////////////////////////////////////////////
  muonfileStr muobstr;
  //
  tree->Branch("run_id", &muobstr.run_id, "run_id/I");
  tree->Branch("year", &muobstr.year, "year/I");
  tree->Branch("month", &muobstr.month, "month/I");
  tree->Branch("day", &muobstr.day, "day/I");
  tree->Branch("ver", &muobstr.ver, "ver/I");
  tree->Branch("nSubRun", &muobstr.nSubRun, "nSubRun/I");
  //
  tree->Branch("event_id", &muobstr.event_id, "event_id/I");
  tree->Branch("event_time",  &muobstr.event_time, "event_time/D");
  tree->Branch("mc_energy",   &muobstr.mc_energy, "mc_energy/F");
  tree->Branch("ring_size",  &muobstr.ring_size, "ring_size/F");
  tree->Branch("size_outside",  &muobstr.size_outside, "size_outside/F");
  tree->Branch("ring_center_x",  &muobstr.ring_center_x, "ring_center_x/F");
  tree->Branch("ring_center_y",  &muobstr.ring_center_y, "ring_center_y/F");
  tree->Branch("ring_radius",  &muobstr.ring_radius, "ring_radius/F");
  tree->Branch("ring_width",  &muobstr.ring_width, "ring_width/F");
  tree->Branch("good_ring",  &muobstr.good_ring, "good_ring/I");
  tree->Branch("muon_efficiency",  &muobstr.muon_efficiency, "muon_efficiency/F");
  tree->Branch("ring_containment",  &muobstr.ring_containment, "ring_containment/F");
  tree->Branch("ring_completeness",  &muobstr.ring_completeness, "ring_completeness/F");
  tree->Branch("impact_parameter",  &muobstr.impact_parameter, "impact_parameter/F");
  tree->Branch("impact_x_array",  &muobstr.impact_x_array, "impact_x_array/F");
  tree->Branch("impact_y_array",  &muobstr.impact_y_array, "impact_y_array/F");
  tree->Branch("radial_stdev",  &muobstr.radial_stdev, "radial_stdev/F");
  tree->Branch("radial_skewness",  &muobstr.radial_skewness, "radial_skewness/F");
  tree->Branch("radial_excess_kurtosis",  &muobstr.radial_excess_kurtosis, "radial_excess_kurtosis/F");
  tree->Branch("num_pixels_in_ring",  &muobstr.num_pixels_in_ring, "num_pixels_in_ring/F");
  tree->Branch("mean_pixel_charge_around_ring",  &muobstr.mean_pixel_charge_around_ring, "mean_pixel_charge_around_ring/F");
  tree->Branch("hg_peak_sample",  &muobstr.hg_peak_sample, "hg_peak_sample/F");
  tree->Branch("lg_peak_sample",  &muobstr.lg_peak_sample, "lg_peak_sampley/F");
  //
  cout<<"Total number of muons : "<<_muonfileStr_vec.size()<<endl;  
  //
  for( unsigned int k = 0; k<_muonfileStr_vec.size(); k++){
    if(k%10000000 == 0)
      cout<<k<<endl;
    muobstr = _muonfileStr_vec.at(k);
    tree->Fill();
  }
  hfile = tree->GetCurrentFile();
  hfile->Write();
  hfile->Close();
}

void read_file(TString file_name, Int_t run_id,  Int_t year,  Int_t month,  Int_t day,  Int_t ver,  Int_t nSubRun){
  ifstream fFile(file_name.Data());
  cout<<file_name<<std::endl;
  //
  string mot;
  Int_t event_id;
  Double_t event_time;
  Float_t mc_energy;
  Float_t ring_size;
  Float_t size_outside;
  Float_t ring_center_x;
  Float_t ring_center_y;
  Float_t ring_radius;
  Float_t ring_width;
  Int_t good_ring;
  Float_t muon_efficiency;
  Float_t ring_containment;
  Float_t ring_completeness;
  Float_t impact_parameter;
  Float_t impact_x_array;
  Float_t impact_y_array;
  Float_t radial_stdev;
  Float_t radial_skewness;
  Float_t radial_excess_kurtosis;
  Float_t num_pixels_in_ring;
  Float_t mean_pixel_charge_around_ring;
  Float_t hg_peak_sample;
  Float_t lg_peak_sample;
  //
  if(fFile.is_open()){
    for(Int_t i = 0;i<23;i++)
      fFile>>mot;
    while(fFile>>
	  mot>>
	  event_id>>
	  event_time>>
	  mc_energy>>
	  ring_size>>
	  size_outside>>
	  ring_center_x>>
	  ring_center_y>>
	  ring_radius>>
	  ring_width>>
	  mot>>
	  muon_efficiency>>
	  ring_containment>>
	  ring_completeness>>
	  impact_parameter>>
	  impact_x_array>>
	  impact_y_array>>
	  radial_stdev>>
	  radial_skewness>>
	  radial_excess_kurtosis>>
	  num_pixels_in_ring>>
	  mean_pixel_charge_around_ring>>
	  hg_peak_sample>>
	  lg_peak_sample){
      //cout<<mot<<endl;
      if (mot == "True") 
	good_ring = 1;
      else
	good_ring = 0;
      muonfileStr tmp;
      //
      tmp.run_id=run_id;
      tmp.year=year;
      tmp.month=month;
      tmp.day=day;
      tmp.ver=ver;
      tmp.nSubRun=nSubRun;
      //
      tmp.event_id=event_id;
      tmp.event_time=event_time;
      tmp.mc_energy=mc_energy;
      tmp.ring_size=ring_size;
      tmp.size_outside=size_outside;
      tmp.ring_center_x=ring_center_x;
      tmp.ring_center_y=ring_center_y;
      tmp.ring_radius=ring_radius;
      tmp.ring_width=ring_width;
      tmp.good_ring=good_ring;
      tmp.muon_efficiency=muon_efficiency;
      tmp.ring_containment=ring_containment;
      tmp.ring_completeness=ring_completeness;
      tmp.impact_parameter=impact_parameter;
      tmp.impact_x_array=impact_x_array;
      tmp.impact_y_array=impact_y_array;
      tmp.radial_stdev=radial_stdev;
      tmp.radial_skewness=radial_skewness;
      tmp.radial_excess_kurtosis=radial_excess_kurtosis;
      tmp.num_pixels_in_ring=num_pixels_in_ring;
      tmp.mean_pixel_charge_around_ring=mean_pixel_charge_around_ring;
      tmp.hg_peak_sample=hg_peak_sample;
      tmp.lg_peak_sample=lg_peak_sample;
      //
      //cout<<event_id<<endl;
      _muonfileStr_vec.push_back(tmp);
    }
    fFile.close();
  }
}
