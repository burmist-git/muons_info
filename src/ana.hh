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


class ana: public anabase {
public:
  ana(TString fileList) : anabase(fileList)
  {
  }

  ana(TString file, Int_t key) : anabase(file, key)
  {
  }

  void Loop(TString histOut);

};

#endif
