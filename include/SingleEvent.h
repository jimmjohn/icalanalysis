#ifndef SINGEVT_H
#define SINGEVT_H

#include "TDatime.h"
#include "TMath.h"
#include "TString.h"
#include "TTimeStamp.h"
#include "TBits.h"

#include <iostream>
#include <cmath>


using namespace std;

class SingleEvent
{

public:
  SingleEvent();
  ~SingleEvent();
  // Declaration of data structure
  static SingleEvent* SiPointer;
  Int_t           splitter;
  Int_t           evt_no;
  Int_t           ENum[12];
  Int_t           REnum[12];
  ULong64_t       CEnum;
  TTimeStamp     *EveTS[12];
  TBits          *xLayer[12];
  TBits          *yLayer[12];

  Int_t           tdc_ref_l[12];
  Int_t           tdc_ref_t[12];
  Int_t           trigCntDiff[12];
  Int_t         xtdchit_l[12][8];
  Int_t         ytdchit_l[12][8];
  UInt_t          xtdc_l[12][8][256];   //[xtdchit_l_0_0]
  UInt_t          ytdc_l[12][8][256];   //[ytdchit_l_0_0]
  UChar_t         xtdchit_t[12][8];
  UChar_t         ytdchit_t[12][8];
  UInt_t          xtdc_t[12][8][256];   //[xtdchit_t_0_0]
  UInt_t          ytdc_t[12][8][256];   //[ytdchit_t_0_0]



private:


};

#endif
