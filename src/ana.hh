#ifndef ana_hh
#define ana_hh

//My
#include "anabase.hh"

//root
#include <TROOT.h>

class TChain;
class TFile;
class TTree;
class TString;
class TBranch;
class TRandom3;
class TGraphErrors;

class ana: public anabase {
public:
  ana(TString fileList) : anabase(fileList), _good_runs_file("good_runs.list"), _run_time_file("run_time.list")
  {
  }

  ana(TString file, Int_t key) : anabase(file, key), _good_runs_file("good_runs.list"), _run_time_file("run_time.list")
  {
  }

  void Loop(TString histOut);

  void get_UT_first_and_last();
  void analize_TProfile(TProfile *pr, TH1D *h1_mean, TH1D *h1_error, TH1D *h1_nen, TGraphErrors *gr, Int_t nMinEntries, Double_t error_min, Double_t error_max);
  void analize_TH1D(TH1D *h1, TH1D *h1_mean, TH1D *h1_error, TH1D *h1_nen, TGraphErrors *gr, Double_t nsec, Int_t nMinEntries, Double_t error_min, Double_t error_max);
  void load_good_runs(Int_t runID_nn, Int_t *run_ID_is_OK);

  void save_good_runs_IDs(Int_t runID_nn, Int_t *run_ID_is_OK,
			  Double_t *run_time_start, Double_t *run_time_stop,
			  Int_t *nSubRun_per_run, Int_t *nmuons_per_run,
			  Int_t *run_ana_ver, Int_t *run_year);
  void save_run_time(Int_t runID_nn, Int_t *run_ID_is_OK,
		     Double_t *run_time_start, Double_t *run_time_stop);
  void load_run_time(Int_t runID_nn, Double_t *run_times_list);
  
  Double_t _UT_start;
  Double_t _UT_stop;
  Double_t _dUT;

  TRandom3 *_rnd;

  TString _good_runs_file;
  TString _run_time_file;
  
};

#endif
