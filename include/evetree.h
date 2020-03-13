//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar  9 03:36:31 2019 by ROOT version 5.34/36
// from TTree evetree/event tree
// found on file: RPCv4t_evtraw-24082017-094530.rre
//////////////////////////////////////////////////////////

#ifndef evetree_h
#define evetree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "TString.h"
#include "TTimeStamp.h"
#include "TBits.h"

class evetree {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  // Declaration of leaf types
  Int_t           ENum[12];
  Int_t           REnum[12];
  ULong64_t       CEnum;
  TTimeStamp *EveTS[12];
  TBits *xLayer[12];
  TBits *yLayer[12];

  Int_t           tdc_ref_l[12];
  Int_t           tdc_ref_t[12];
  Int_t           trigCntDiff[12];
  UChar_t         xtdchit_l[12][8];
  UChar_t         ytdchit_l[12][8];
  UInt_t          xtdc_l[12][8][256];   //[xtdchit_l_0_0]
  UInt_t          ytdc_l[12][8][256];   //[ytdchit_l_0_0]
  UChar_t         xtdchit_t[12][8];
  UChar_t         ytdchit_t[12][8];
  UInt_t          xtdc_t[12][8][256];   //[xtdchit_t_0_0]
  UInt_t          ytdc_t[12][8][256];   //[ytdchit_t_0_0]

  // List of branches
  TBranch        *b_ENum;   //!
  TBranch        *b_REnum;   //!
  TBranch        *b_CEnum;   //!
  TBranch        *b_Evetime[12];   //!
  TBranch        *b_xstriphitsL[12];   //!
  TBranch        *b_ystriphitsL[12];   //!

  TBranch        *b_tdc_ref_l;   //!
  TBranch        *b_tdc_ref_t;   //!
  TBranch        *b_trigCntDiff;   //!
  TBranch        *b_xtdchit_l[12][8];   //!
  TBranch        *b_ytdchit_l[12][8];   //!
  TBranch        *b_xtdc_l[12][8];   //!
  TBranch        *b_ytdc_l[12][8];   //!
  TBranch        *b_xtdchit_t[12][8];   //!
  TBranch        *b_ytdchit_t[12][8];   //!
  TBranch        *b_xtdc_t[12][8];   //!
  TBranch        *b_ytdc_t[12][8];   //!

  evetree(TTree *tree=0);
  virtual ~evetree();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef evetree_cxx
evetree::evetree(TTree *tree) : fChain(0)
{
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("RPCv4t_evtraw-24082017-094530.rre");
    if (!f || !f->IsOpen()) {
      f = new TFile("RPCv4t_evtraw-24082017-094530.rre");
    }
    f->GetObject("evetree",tree);

  }
  Init(tree);
}

evetree::~evetree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t evetree::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t evetree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void evetree::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer

  const char *sideMark[2] = {"x","y"};

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("ENum", ENum, &b_ENum);
  fChain->SetBranchAddress("REnum", REnum, &b_REnum);
  fChain->SetBranchAddress("CEnum", &CEnum, &b_CEnum);

  fChain->SetBranchAddress("tdc_ref_l", tdc_ref_l, &b_tdc_ref_l);
  fChain->SetBranchAddress("tdc_ref_t", tdc_ref_t, &b_tdc_ref_t);
  fChain->SetBranchAddress("trigCntDiff", trigCntDiff, &b_trigCntDiff);
  for(int ij=0;ij<12;ij++) {
    EveTS[ij] = 0;
    xLayer[ij] = 0;
    yLayer[ij] = 0;
    fChain->SetBranchAddress(TString::Format("Evetime_%i",ij), &EveTS[ij], &b_Evetime[ij]);
    fChain->SetBranchAddress(TString::Format("xstriphitsL%i",ij), &xLayer[ij], &b_xstriphitsL[ij]);
    fChain->SetBranchAddress(TString::Format("ystriphitsL%i",ij), &yLayer[ij], &b_ystriphitsL[ij]);
    for(int jk=0;jk<8;jk++) {
      fChain->SetBranchAddress(TString::Format("xtdchit_l_%i_%i",ij,jk), &xtdchit_l[ij][jk], &b_xtdchit_l[ij][jk]);
      fChain->SetBranchAddress(TString::Format("ytdchit_l_%i_%i",ij,jk), &ytdchit_l[ij][jk], &b_ytdchit_l[ij][jk]);
      fChain->SetBranchAddress(TString::Format("xtdc_l_%i_%i",ij,jk), xtdc_l[ij][jk], &b_xtdc_l[ij][jk]);
      fChain->SetBranchAddress(TString::Format("ytdc_l_%i_%i",ij,jk), ytdc_l[ij][jk], &b_ytdc_l[ij][jk]);

      fChain->SetBranchAddress(TString::Format("xtdchit_t_%i_%i",ij,jk), &xtdchit_t[ij][jk], &b_xtdchit_t[ij][jk]);
      fChain->SetBranchAddress(TString::Format("ytdchit_t_%i_%i",ij,jk), &ytdchit_t[ij][jk], &b_ytdchit_t[ij][jk]);
      fChain->SetBranchAddress(TString::Format("xtdc_t_%i_%i",ij,jk), xtdc_t[ij][jk], &b_xtdc_t[ij][jk]);
      fChain->SetBranchAddress(TString::Format("ytdc_t_%i_%i",ij,jk), ytdc_t[ij][jk], &b_ytdc_t[ij][jk]);
    }
  }

  Notify();
}

Bool_t evetree::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void evetree::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t evetree::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef evetree_cxx
