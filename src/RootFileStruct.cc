//////////////////////////////////////////////////////////////////////////////
//  Event class for event information and store in root file as
//  tuple and/or histograms
////////////////////////////////////////////////////////////////////////////////

#include "RootFileStruct.h"
#include "Constants.h"

RootFileStruct *RootFileStruct::AnPointer;

RootFileStruct::RootFileStruct(){
  AnPointer = this;
  pRootFile	=0;
}

void RootFileStruct::OpenRootfiles(char *outfile) {
//  printf("%s\n",outfile );
  pRootFile = new TFile(outfile, "recreate");
  pEventTree = new TTree("AnlTree", "AnalysisTree");

  pEventTree->Branch("irun",&irun,"irun/I");
  pEventTree->Branch("ievt",&ievt,"ievt/I");
  pEventTree->Branch("splitval",&splitval,"ngent/I");
  //X-side
  pEventTree->Branch("xfitfailed",&xfitfailed,"xfitfailed/I");
  pEventTree->Branch("xintersect",&xintersect,"xintersect/D");
  pEventTree->Branch("xslope",&xslope,"xslope/D");
  pEventTree->Branch("xerrinter",&xerrinter,"xerrinter/D");
  pEventTree->Branch("xerrslope",&xerrslope,"xerrslope/D");
  pEventTree->Branch("xerrcovar",&xerrcovar,"xerrcovar/D");
  pEventTree->Branch("xndof",&xndof,"xndof/I");
  pEventTree->Branch("xchisquare",&xchisquare,"xchisquare/D");
  pEventTree->Branch("xext",xext,"xext[12]/D");
  pEventTree->Branch("xdev",xdev,"xdev[12]/D");
  pEventTree->Branch("xexter",xexter,"xexter[12]/D");
  //Y-side
  pEventTree->Branch("yfitfailed",&yfitfailed,"yfitfailed/I");
  pEventTree->Branch("yintersect",&yintersect,"yintersect/D");
  pEventTree->Branch("yslope",&yslope,"yslope/D");
  pEventTree->Branch("yerrinter",&yerrinter,"yerrinter/D");
  pEventTree->Branch("yerrslope",&yerrslope,"yerrslope/D");
  pEventTree->Branch("yerrcovar",&yerrcovar,"yerrcovar/D");
  pEventTree->Branch("yndof",&yndof,"yndof/I");
  pEventTree->Branch("ychisquare",&ychisquare,"ychisquare/D");
  pEventTree->Branch("yext",yext,"yext[12]/D");
  pEventTree->Branch("ydev",ydev,"ydev[12]/D");
  pEventTree->Branch("yexter",yexter,"yexter[12]/D");
  //X-time
  pEventTree->Branch("xtfitfailed",&xtfitfailed,"xtfitfailed/I");
  pEventTree->Branch("xtintersect",&xtintersect,"xtintersect/D");
  pEventTree->Branch("xtslope",&xtslope,"xtslope/D");
  pEventTree->Branch("xterrinter",&xterrinter,"xterrinter/D");
  pEventTree->Branch("xterrslope",&xterrslope,"xterrslope/D");
  pEventTree->Branch("xterrcovar",&xterrcovar,"xterrcovar/D");
  pEventTree->Branch("xtndof",&xtndof,"xtndof/I");
  pEventTree->Branch("xtchisquare",&xtchisquare,"xtchisquare/D");
  pEventTree->Branch("xtext",xtext,"xtext[12]/D");
  pEventTree->Branch("xtdev",xtdev,"xtdev[12]/D");
  pEventTree->Branch("xtexter",xtexter,"xtexter[12]/D");
  //Y-time
  pEventTree->Branch("ytfitfailed",&ytfitfailed,"ytfitfailed/I");
  pEventTree->Branch("ytintersect",&ytintersect,"ytintersect/D");
  pEventTree->Branch("ytslope",&ytslope,"ytslope/D");
  pEventTree->Branch("yterrinter",&yterrinter,"yterrinter/D");
  pEventTree->Branch("yterrslope",&yterrslope,"yterrslope/D");
  pEventTree->Branch("yterrcovar",&yterrcovar,"yterrcovar/D");
  pEventTree->Branch("ytndof",&ytndof,"ytndof/I");
  pEventTree->Branch("ytchisquare",&ytchisquare,"ytchisquare/D");
  pEventTree->Branch("ytext",ytext,"ytext[12]/D");
  pEventTree->Branch("ytdev",ytdev,"ytdev[12]/D");
  pEventTree->Branch("ytexter",ytexter,"ytexter[12]/D");

  //Histograms
  char title[100];
  for (int ij=0; ij<nlayer; ij++) {
    sprintf(title, "xlayer_occu_l%i", ij);
    xlayer_occu[ij] = new TH1F(title, title, nstrip, -0.5, nstrip-0.5);
    sprintf(title, "ylayer_occu_l%i", ij);
    ylayer_occu[ij] = new TH1F(title, title, nstrip, -0.5, nstrip-0.5);
    sprintf(title, "xlayer_mult_l%i", ij);
    xlayer_mult[ij] = new TH1F(title, title, nstrip+1, -0.5, nstrip+0.5);
    sprintf(title, "ylayer_mult_l%i", ij);
    ylayer_mult[ij] = new TH1F(title, title, nstrip+1, -0.5, nstrip+0.5);
    sprintf(title, "rawhits_corr_xymul_l%i", ij);
    rawhits_corr_xymul[ij] = new TH2F(title, title, nstrip+1, -0.5, nstrip+0.5,  nstrip+1, -0.5, nstrip+0.5);
    sprintf(title, "raw_occu_l%i", ij);
    raw_occu[ij] = new TH2F(title, title, nstrip, -0.5, nstrip-0.5, nstrip, -0.5, nstrip-0.5);
    for (int jk=ij+1; jk<nlayer; jk++) {
      sprintf(title, "rawhits_xlay_corr_mul_l%i_l%i", ij, jk);
      rawhits_xlay_corr_mul[ij][jk] = new TH2F(title, title, nstrip+1, -0.5, nstrip+0.5,  nstrip+1, -0.5, nstrip+0.5);
      sprintf(title, "rawhits_ylay_corr_mul_l%i_l%i", ij, jk);
      rawhits_ylay_corr_mul[ij][jk] = new TH2F(title, title, nstrip+1, -0.5, nstrip+0.5,  nstrip+1, -0.5, nstrip+0.5);
    }
    double xposmx = 6.0;
    sprintf(title, "xlayer_reso_l%i", ij);
    xlayer_reso[ij] = new TH1F(title, title, 150, -xposmx, xposmx);
    sprintf(title, "ylayer_reso_l%i", ij);
    ylayer_reso[ij] = new TH1F(title, title, 150, -xposmx, xposmx);
    sprintf(title, "totalentry_l%i", ij);
    totalentry[ij]=new TH2D(title, title, nstrip, -0.5, nstrip-0.5, nstrip, -0.5, nstrip-0.5);

  }


}

void RootFileStruct::CloseRootfiles() {
  if (pRootFile) {
    pRootFile->cd();
    //Histograms has to divide and plot here
    pRootFile->Write();
    cout << "Histogram file writen !" << endl;

    if (pEventTree) { delete pEventTree; pEventTree=0;}
    pRootFile->Close();
    delete pRootFile; pRootFile=0;
    cout << "Histogram file  made !" << endl;
  } else {
    cout << "Histogram file not made !" << endl;
  }
}

RootFileStruct::~RootFileStruct() {
}
//Functions to pass values
void RootFileStruct::SetValue1(double val) {
  setval1 = val;
}
void RootFileStruct::SetValue2(double val) {
  setval2 = val;
}
