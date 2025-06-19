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
  
void read_file(TString file_name);
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

void load_file_list( std::vector<TString> &fileList_v, TString inFileList){
  //
  Int_t verbosity = 1;
  std::ifstream fFile(inFileList.Data());
  if(verbosity>0)
    std::cout<<" inFileList --> "<<inFileList<<std::endl;
  //
  //
  TString the_file;
  //
  if(fFile.is_open()){
    while(fFile>>the_file){
      fileList_v.push_back(the_file);
      if(verbosity>1)
	std::cout<<the_file<<endl;
    }
    fFile.close();
  }
}

void convert2root(const std::vector<TString> &fileList_v, TString outputRootFile){
  for(unsigned int i = 0; i < fileList_v.size(); i++)
    read_file(fileList_v.at(i));
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
  for( unsigned int k = 0; k<_muonfileStr_vec.size(); k++){
    muobstr = _muonfileStr_vec.at(k);
    tree->Fill();
  }
  hfile = tree->GetCurrentFile();
  hfile->Write();
  hfile->Close();
}

void read_file(TString file_name){
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

/*


  //
  std::ifstream fFile(file_name.Data());
  std::cout<<file_name<<std::endl;
  //
  std::string mot;     //0
  Float_t event_id;    //1
  Float_t energy;      //2
  Float_t azimuth;     //3
  Float_t altitude;    //4
  Float_t h_first_int; //5
  Float_t xmax;        //6
  Float_t hmax;        //7
  Float_t emax;        //8
  Float_t cmax;        //9
  Float_t xcore;       //10
  Float_t ycore;       //11
  Float_t ev_time;     //12
  Float_t nphotons;    //13
  Float_t n_pe;        //14
  Float_t n_pixels;    //15
  //
  //0 0
  //1 38608.0
  //2 7.01853084564209
  //3 7.01853084564209
  //4 3.2043185234069824
  //5 1.07183837890625
  //6 19472.216796875
  //7 392.4561462402344
  //8 7753.76318359375
  //9 392.52252197265625
  //10 394.76361083984375
  //11 618.92919921875
  //12 -27.958635330200195
  //13 -1012.3057250976562
  //14 6657.0
  //15 158.0
  //
  //
  // 157 38608.0 7934.0 -968.3527221679688
  // 158 42404.0    5.0 -358.64276123046875
  //
  if(fFile.is_open()){
    while(fFile>>mot>>
	  event_id>>
	  energy>>
	  azimuth>>
	  altitude>>
	  h_first_int>>
	  xmax>>
	  hmax>>
	  emax>>
	  cmax>>
	  xcore>>
	  ycore>>
	  ev_time>>
	  nphotons>>
	  n_pe>>
	  n_pixels){
      wfheaderStr tmp;      
      tmp.event_id=event_id;
      tmp.energy=energy;
      tmp.azimuth=azimuth;
      tmp.altitude=altitude;
      tmp.h_first_int=h_first_int;
      tmp.xmax=xmax;
      tmp.hmax=hmax;
      tmp.emax=emax;
      tmp.cmax=cmax;
      tmp.xcore=xcore;
      tmp.ycore=ycore;
      tmp.ev_time=ev_time;
      tmp.nphotons=nphotons;
      tmp.n_pe=n_pe;
      tmp.n_pixels=n_pixels;
      //std::cout<<tmp.event_id<<std::endl;
      //assert(0);
      header_vec.push_back(tmp);
    }
    fFile.close();
  }  
}

void read_pe_info(TString file_name){
  //
  std::ifstream fFile(file_name.Data());
  std::cout<<file_name<<std::endl;
  //
  Int_t verbosity = 0;
  //
  Int_t id;
  Float_t event_id;
  Float_t ch_id;
  Float_t pe_time;
  //
  if(fFile.is_open()){
    for(unsigned int i = 0; i < header_vec.size(); i++){
      pe_info_str pe_info;
      pe_info.event_id = header_vec.at(i).event_id;
      for(unsigned int j = 0; j < (unsigned int)header_vec.at(i).n_pe; j++){
	fFile>>id>>event_id>>ch_id>>pe_time;
	//std::cout<<std::setw(10)<<"id       "<<std::setw(10)<<id
	//	 <<std::setw(10)<<"event_id "<<std::setw(10)<<event_id
	//	 <<std::setw(10)<<"ch_id    "<<std::setw(10)<<ch_id
	//	 <<std::setw(10)<<"pe_time  "<<std::setw(10)<<pe_time<<std::endl;
	if(verbosity>1){
	  if(j%1000000==0)
	    std::cout<<std::setw(10)<<"id       "<<std::setw(10)<<id
		     <<std::setw(10)<<"event_id "<<std::setw(10)<<event_id
		     <<std::setw(10)<<"ch_id    "<<std::setw(10)<<ch_id
		     <<std::setw(10)<<"pe_time  "<<std::setw(10)<<pe_time<<std::endl;
	}
	//else if (verbosity>2){
	//std::cout<<std::setw(10)<<"id       "<<std::setw(10)<<id
	//	   <<std::setw(10)<<"event_id "<<std::setw(10)<<event_id
	//	   <<std::setw(10)<<"ch_id    "<<std::setw(10)<<ch_id
	//	   <<std::setw(10)<<"pe_time  "<<std::setw(10)<<pe_time<<std::endl;
	//}
	if((Int_t)event_id != header_vec.at(i).event_id){
	  std::cout<<" ERROR ---> (Int_t)event_id != header_vec.at(i).event_id "<<std::endl
		   <<"            (Int_t)event_id "<<(Int_t)event_id<<std::endl
		   <<"  header_vec.at(i).event_id "<<header_vec.at(i).event_id<<std::endl
		   <<"  header_vec.at(0).event_id "<<header_vec.at(0).event_id<<std::endl;
	  //std::cout<<std::setw(10)<<"id       "<<std::setw(10)<<id
	  //	   <<std::setw(10)<<"event_id "<<std::setw(10)<<event_id
	  //	   <<std::setw(10)<<"ch_id    "<<std::setw(10)<<ch_id
	  //	   <<std::setw(10)<<"pe_time  "<<std::setw(10)<<pe_time<<std::endl;
	  assert(0);
	}
	pe_info.chID.push_back((Int_t)ch_id);
	pe_info.time.push_back(pe_time);
      }
      pe_info_vec.push_back(pe_info);
    }
    fFile.close();
  }
}

void read_wf(TString wf_file_list){
  std::ifstream indataList;
  std::ifstream indataFile;
  indataList.open(wf_file_list.Data());
  std::string mot;
  TString inputDataFile;
  Int_t nEv = 0;
  Int_t vVal;
  //
  while (indataList >> mot >> nEv ){
    inputDataFile = mot;
    std::cout<<" ---> Conversion of "<<inputDataFile<<std::endl;
    indataFile.open(inputDataFile.Data());
    for( Int_t i_ev = 0; i_ev < nEv; i_ev++){
      wf_str wf;
      for(Int_t i_ch = 0;i_ch<nn_PMT_channels; i_ch++){
	//indataFile>>vVal;
	for(Int_t i_adc = 0;i_adc<nn_fadc_point; i_adc++){
	  indataFile>>vVal;
	  wf.wf[i_ch][i_adc] = vVal;
	}
      }
      wf_str_vec.push_back(wf);
    }
    indataFile.close();
  }
  indataList.close();
}

void convert2root(const std::vector<TString> &header_file_v, const std::vector<TString> &pe_info_file_v, TString outputRootFile) {
  //
  ////////////////
  //
  ///////////////////Root file with data/////////////////
  //
  Int_t event_id;
  Float_t energy;
  Float_t azimuth;
  Float_t altitude;
  Float_t h_first_int;
  Float_t xmax;
  Float_t hmax;
  Float_t emax;
  Float_t cmax;
  Float_t xcore;
  Float_t ycore;
  Float_t ev_time;
  //
  Int_t nphotons;
  Int_t n_pe;
  Int_t n_pixels;
  //
  Int_t pe_chID[nn_max];
  Float_t pe_time[nn_max];
  //
  //Event////////////////////////////////////////////////
  tree->Branch("event_id",&event_id, "event_id/I");
  tree->Branch("energy",&energy, "energy/F");
  tree->Branch("azimuth",&azimuth, "azimuth/F");
  tree->Branch("altitude",&altitude, "altitude/F");
  tree->Branch("h_first_int",&h_first_int, "h_first_int/F");
  tree->Branch("xmax",&xmax, "xmax/F");
  tree->Branch("hmax",&hmax, "hmax/F");
  tree->Branch("emax",&emax, "emax/F");
  tree->Branch("cmax",&cmax, "cmax/F");
  tree->Branch("xcore", &xcore, "xcore/F");
  tree->Branch("ycore", &ycore, "ycore/F");
  tree->Branch("ev_time",&ev_time, "ev_time/F");
  tree->Branch("nphotons",&nphotons, "nphotons/I");
  tree->Branch("n_pe",&n_pe, "n_pe/I");
  tree->Branch("n_pixels",&n_pixels, "n_pixels/I");
  //
  tree->Branch("pe_chID",pe_chID, "pe_chID[n_pe]/I");
  tree->Branch("pe_time",pe_time, "pe_time[n_pe]/F");
  //
  ///////////////////////////////////////////////////////
  //
  ////////////////
  for(unsigned int j = 0; j<header_file_v.size();j++){
    //
    header_vec.clear();
    pe_info_vec.clear();
    //
    std::cout<<std::endl
	     <<"header_file    "<<header_file_v.at(j)<<std::endl
	     <<"pe_info_file   "<<pe_info_file_v.at(j)<<std::endl;
    //
    read_header(header_file_v.at(j));
    read_pe_info(pe_info_file_v.at(j));
    //    
    std::cout<<"header_vec.size()  "<<header_vec.size()<<std::endl
	     <<"pe_info_vec.size() "<<pe_info_vec.size()<<std::endl;
    if(header_vec.size() != pe_info_vec.size()){
      std::cout<<" --> ERROR : header_vec.size() != pe_info_vec.size() "<<std::endl
	       <<"             header_vec.size()  = "<<header_vec.size()<<std::endl;
      assert(0);
    }     
    //
    for(unsigned int i = 0; i < header_vec.size(); i++){
      if(i%10000 == 0)
	std::cout<<i<<std::endl;
      //
      event_id = header_vec.at(i).event_id;
      energy = header_vec.at(i).energy;
      azimuth = header_vec.at(i).azimuth;
      altitude = header_vec.at(i).altitude;
      h_first_int = header_vec.at(i).h_first_int;
      xmax = header_vec.at(i).xmax;
      hmax = header_vec.at(i).hmax;
      emax = header_vec.at(i).emax;
      cmax = header_vec.at(i).cmax;
      xcore = header_vec.at(i).xcore;
      ycore = header_vec.at(i).ycore;
      ev_time = header_vec.at(i).ev_time;
      nphotons = header_vec.at(i).nphotons;
      n_pe = header_vec.at(i).n_pe;
      n_pixels = header_vec.at(i).n_pixels;
      //
      if(pe_info_vec.at(i).event_id != event_id){
	std::cout<<" --> ERROR : pe_info_vec.at(i).event_id != event_id "<<std::endl
		 <<"             pe_info_vec.at(i).event_id  = "<<pe_info_vec.at(i).event_id<<std::endl
		 <<"                               event_id  = "<<event_id<<std::endl;
	assert(0);
      }
      //
      if(pe_info_vec.at(i).chID.size() != (unsigned int)n_pe ||
	 pe_info_vec.at(i).time.size() != (unsigned int)n_pe){
	std::cout<<" --> ERROR : pe_info_vec.at(i).chID.size() != (unsigned int)n_pe || "<<std::endl
		 <<"             pe_info_vec.at(i).time.size() != (unsigned int)n_pe"<<std::endl
		 <<"             pe_info_vec.at(i).chID.size()  = "<<pe_info_vec.at(i).chID.size()<<std::endl
		 <<"             pe_info_vec.at(i).time.size()  = "<<pe_info_vec.at(i).time.size()<<std::endl
		 <<"                                      n_pe  = "<<n_pe<<std::endl;
	assert(0);
      }
      for(int j = 0; j < nn_max; j++){
	pe_chID[j] = 0;
	pe_time[j] = 0.0;
      }
      ////////////////////
      if(n_pe<nn_max){
	for(unsigned int j = 0; j < pe_info_vec.at(i).chID.size(); j++){
	  pe_chID[j] = pe_info_vec.at(i).chID.at(j);
	  pe_time[j] = pe_info_vec.at(i).time.at(j);
	}
	//
	tree->Fill();
      }
    }
  }
  hfile = tree->GetCurrentFile();
  hfile->Write();
  hfile->Close();
}

void read_list( std::vector<TString> &header_file_v, std::vector<TString> &pe_info_file_v, TString inDir, TString list_file){
}
*/
