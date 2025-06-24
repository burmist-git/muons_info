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
  ana(TString fileList) : anabase(fileList)
  {
  }

  ana(TString file, Int_t key) : anabase(file, key)
  {
  }

  void Loop(TString histOut);

  void get_UT_first_and_last();
  void analize_TProfile(TProfile *pr, TH1D *h1_mean, TH1D *h1_error, TH1D *h1_nen, TGraphErrors *gr, Int_t nMinEntries, Double_t error_min, Double_t error_max);
  void analize_TH1D(TH1D *h1, TH1D *h1_mean, TH1D *h1_error, TH1D *h1_nen, TGraphErrors *gr, Double_t nsec, Int_t nMinEntries, Double_t error_min, Double_t error_max);
  
  Double_t _UT_start;
  Double_t _UT_stop;
  Double_t _dUT;

  TRandom3 *_rnd;
  
};

#endif
