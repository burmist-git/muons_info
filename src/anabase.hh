#ifndef anabase_hh
#define anabase_hh

#include <TROOT.h>

class TChain;
class TFile;
class TTree;
class TString;
class TBranch;
class TGraph;
class TH1D;
class TH2D;
class TProfile;

class anabase {

public :
  anabase(TString fileList);
  anabase(TString inFileName, Int_t keyID);
  ~anabase();
  Int_t GetEntry(Long64_t entry);
  Long64_t LoadTree(Long64_t entry);
  void Init(TTree *tree);
  void Loop(TString histOut);
  Bool_t Notify();
  void Show(Long64_t entry = -1);
  Int_t Cut(Long64_t entry);

protected :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  //
  Int_t           run_id;
  Int_t           year;
  Int_t           month;
  Int_t           day;
  Int_t           ver;
  Int_t           nSubRun;
  Int_t           event_id;
  Double_t        event_time;
  Float_t         mc_energy;
  Float_t         ring_size;
  Float_t         size_outside;
  Float_t         ring_center_x;
  Float_t         ring_center_y;
  Float_t         ring_radius;
  Float_t         ring_width;
  Int_t           good_ring;
  Float_t         muon_efficiency;
  Float_t         ring_containment;
  Float_t         ring_completeness;
  Float_t         impact_parameter;
  Float_t         impact_x_array;
  Float_t         impact_y_array;
  Float_t         radial_stdev;
  Float_t         radial_skewness;
  Float_t         radial_excess_kurtosis;
  Float_t         num_pixels_in_ring;
  Float_t         mean_pixel_charge_around_ring;
  Float_t         hg_peak_sample;
  Float_t         lg_peak_sample;
  //
  //---------------------------------------------------
  // ADD HERE :
  //Tree name
  //const TString treeName = "arich";
  const TString treeName = "T";
  static const Int_t nChannels = 10;
  
  //---------------------------------------------------
  
  // List of branches
  //TBranch        *b_evt;
  //TBranch        *b_run;
  //TBranch        *b_pValue;
  //...
  //...
  //
  //---------------------------------------------------
  // ADD HERE :
   TBranch        *b_run_id;   //!
   TBranch        *b_year;   //!
   TBranch        *b_month;   //!
   TBranch        *b_day;   //!
   TBranch        *b_ver;   //!
   TBranch        *b_nSubRun;   //!
   TBranch        *b_event_id;   //!
   TBranch        *b_event_time;   //!
   TBranch        *b_mc_energy;   //!
   TBranch        *b_ring_size;   //!
   TBranch        *b_size_outside;   //!
   TBranch        *b_ring_center_x;   //!
   TBranch        *b_ring_center_y;   //!
   TBranch        *b_ring_radius;   //!
   TBranch        *b_ring_width;   //!
   TBranch        *b_good_ring;   //!
   TBranch        *b_muon_efficiency;   //!
   TBranch        *b_ring_containment;   //!
   TBranch        *b_ring_completeness;   //!
   TBranch        *b_impact_parameter;   //!
   TBranch        *b_impact_x_array;   //!
   TBranch        *b_impact_y_array;   //!
   TBranch        *b_radial_stdev;   //!
   TBranch        *b_radial_skewness;   //!
   TBranch        *b_radial_excess_kurtosis;   //!
   TBranch        *b_num_pixels_in_ring;   //!
   TBranch        *b_mean_pixel_charge_around_ring;   //!
   TBranch        *b_hg_peak_sample;   //!
   TBranch        *b_lg_peak_sampley;   //!
  //---------------------------------------------------
  void tGraphInit(TGraph *gr[nChannels], TString grName, TString grTitle);
  void h1D1Init(TH1D *h1D1[nChannels],TString h1name, TString h1Title,
		Int_t Nbin, Float_t Vmin, Float_t Vmax);
  void h2D2Init(TH2D *h2D1[nChannels],TString h2name, TString h2Title,
                Int_t Nbin1, Float_t Vmin1, Float_t Vmax1,
                Int_t Nbin2, Float_t Vmin2, Float_t Vmax2);
  void tProfInit(TProfile *tprof[nChannels],TString prname, TString prTitle,
                 Int_t Nbin, Float_t Vmin, Float_t Vmax);
  double getUnixTimeFromTime(double d_year, double d_month, double d_day, double d_hour, double d_min, double d_sec);  
  //
  
};

#endif
