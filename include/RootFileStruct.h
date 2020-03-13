////////////////////////////////////////////////////////////////////////////////
//  Event class for event information and store in root file as
//  tuple and/or histograms
////////////////////////////////////////////////////////////////////////////////


#ifndef RootFileStruct_H
#define RootFileStruct_H
#include <iostream>
#include <functional>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <new>
#include <climits>
#include <vector>

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraph2D.h"
#include "TGraph2DErrors.h"
#include "TTree.h"
#include "TFile.h"
#include "TProfile.h"
#include "TString.h"
#include "Constants.h"

using namespace std;
using std::vector;

class RootFileStruct
{
  public:
  RootFileStruct();
  void OpenRootfiles(char *outfile);
  void CloseRootfiles();
  void SetValue1(double val);
  void SetValue2(double val);
   ~RootFileStruct();
  double setval1;
  double setval2;
  public:
    static RootFileStruct* AnPointer;
    TFile *pRootFile;
    TTree *pEventTree;
    TH1F* xlayer_occu[nlayer];
    TH1F* ylayer_occu[nlayer];
    TH1F* xlayer_mult[nlayer];
    TH1F* ylayer_mult[nlayer];
    TH2F* rawhits_corr_xymul[nlayer];
    TH2F* raw_occu[nlayer];
    TH2F* rawhits_xlay_corr_mul[nlayer][nlayer];
    TH2F* rawhits_ylay_corr_mul[nlayer][nlayer];
    TH1F* xlayer_reso[nlayer];
    TH1F* ylayer_reso[nlayer];
    TH2D* totalentry[nlayer];

    int    irun;
    int    ievt;
    int    splitval;
    //X-side
    int    xhits[nlayer];
    double xpos[nlayer];
    double xxerr[nlayer];
    bool   xusedpos[nlayer];
    int    xfitfailed;
    double xintersect;
    double xslope;
    double xerrinter;
    double xerrslope;
    double xerrcovar;
    int    xndof;
    double xchisquare;
    double xext[nlayer];
    double xdev[nlayer];
    double xexter[nlayer];
    double xextloc[nlayer];
    double xposinstr[nlayer];
    //Y-side
    int    yhits[nlayer];
    double ypos[nlayer];
    double yyerr[nlayer];
    bool   yusedpos[nlayer];
    int    yfitfailed;
    double yintersect;
    double yslope;
    double yerrinter;
    double yerrslope;
    double yerrcovar;
    int    yndof;
    double ychisquare;
    double yext[nlayer];
    double ydev[nlayer];
    double yexter[nlayer];
    double yextloc[nlayer];
    double yposinstr[nlayer];
    //X-time
    int    xtfitfailed;
    double xtintersect;
    double xtslope;
    double xterrinter;
    double xterrslope;
    double xterrcovar;
    int    xtndof;
    double xtchisquare;
    double xtext[nlayer];
    double xtdev[nlayer];
    double xtexter[nlayer];
    //Y-time
    int    ytfitfailed;
    double ytintersect;
    double ytslope;
    double yterrinter;
    double yterrslope;
    double yterrcovar;
    int    ytndof;
    double ytchisquare;
    double ytext[nlayer];
    double ytdev[nlayer];
    double ytexter[nlayer];


    int counter[50]={0};






private:


};

#endif
