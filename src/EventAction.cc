
#include "EventAction.h"
#include "SingleEvent.h"
#include "StraightLineFit.h"

#include <iomanip>
#include <utility>

//#include "vect_manager.h"

#include "TMath.h"

EventAction::EventAction() {
}

EventAction::~EventAction() {
}

void EventAction::BeginOfEventAction() {
RootFileStruct *pAnalysis = RootFileStruct::AnPointer;
SingleEvent *sEvt = SingleEvent::SiPointer;
pAnalysis->counter[0]++;
//Reading from Main root file.
//Reading Position Information(saving to xptsall and yptsall. xptsalltdc will tell the channel number)
//This will create variables for fitting
for(int jk=0;jk<nlayer;jk++) {
  xpts[jk].clear(); ypts[jk].clear();
  for (int kl=0; kl<nTDCpLayer; kl++) {
    xptsalltdc[jk][kl].clear();  yptsalltdc[jk][kl].clear();
  }
  for(int kl=0; kl<nstrip; kl++) {
    if(sEvt->xLayer[jk]->TestBitNumber(kl)) {
      xpts[jk].push_back(kl);
      xptsalltdc[jk][kl%8].push_back(kl);
    }
    if(sEvt->yLayer[jk]->TestBitNumber(kl)) {
      ypts[jk].push_back(kl);
      yptsalltdc[jk][kl%8].push_back(kl);
    }
  }
  if(jk==0 && xpts[jk].size()>0){pAnalysis->counter[1]++;}
  for (int ix=0; ix<xpts[jk].size(); ix++) {
    pAnalysis->xlayer_occu[jk]->Fill(xpts[jk][ix]);
    if(jk==0){pAnalysis->counter[2]++;}
  }
  for (int iy=0; iy<ypts[jk].size(); iy++) {
    pAnalysis->ylayer_occu[jk]->Fill(ypts[jk][iy]);
  }
  pAnalysis->xlayer_mult[jk]->Fill(xpts[jk].size());
  pAnalysis->ylayer_mult[jk]->Fill(ypts[jk].size());
  pAnalysis->rawhits_corr_xymul[jk]->Fill(xpts[jk].size(), ypts[jk].size());
  for (int ix=0; ix<xpts[jk].size(); ix++) {
    for (int iy=0; iy<ypts[jk].size(); iy++) {
      pAnalysis->raw_occu[jk]->Fill(xpts[jk][ix], ypts[jk][iy]);
    }
  }
  for (int ij=jk+1; ij<nlayer; ij++) {
    pAnalysis->rawhits_xlay_corr_mul[jk][ij]->Fill(xpts[jk].size(), xpts[ij].size());
    pAnalysis->rawhits_ylay_corr_mul[jk][ij]->Fill(ypts[jk].size(), ypts[ij].size());
  }
  pAnalysis->xhits[jk] = xpts[jk].size();
  pAnalysis->yhits[jk] = ypts[jk].size();
  pAnalysis->xdev[jk] = 100; pAnalysis->xpos[jk]=0.0;
  pAnalysis->ydev[jk] = 100; pAnalysis->ypos[jk]=0.0;
  //X-Side
  if (pAnalysis->xhits[jk]<=0 || pAnalysis->xhits[jk]>nmxhits) {
    pAnalysis->xpos[jk]= -100;
    if(jk==0){pAnalysis->counter[3]++;}
  } else {
    for (int ix=0; ix<pAnalysis->xhits[jk]; ix++) {
      //Come back here and check. Only first cluster will be used....I think this is little wron and can be modified
      if (ix<pAnalysis->xhits[jk]-1 && abs(xpts[jk][ix]-xpts[jk][ix+1])>1) { if(jk==0){pAnalysis->counter[4]++;}pAnalysis->xpos[jk]=-100; break;if(jk==0){pAnalysis->counter[5]++;}}
      pAnalysis->xpos[jk] +=xpts[jk][ix];
    }
  }
  pAnalysis->xxerr[jk] = errxco[jk]*errxco[jk];
  if (pAnalysis->xpos[jk]>=0.0) {
    if(jk==0){pAnalysis->counter[6]++;}
    pAnalysis->xpos[jk]  = pAnalysis->xpos[jk]/pAnalysis->xhits[jk] + 0.5;
    //Aligmnent Correction
    pAnalysis->xpos[jk] -= cal_slope2(pAnalysis->xpos[jk], &align_xstr_xdev[jk][0]);
    pAnalysis->xxerr[jk] = xposerrsq[pAnalysis->xhits[jk]-1][jk];
  }
  //Y-Side
  if (pAnalysis->yhits[jk]<=0 || pAnalysis->yhits[jk]>nmxhits) {
    pAnalysis->ypos[jk]= -100;
  } else {
    for (int ix=0; ix<pAnalysis->yhits[jk]; ix++) {
      //Come back here and check. Only first cluster will be used....
      if (ix<pAnalysis->yhits[jk]-1 && abs(ypts[jk][ix]-ypts[jk][ix+1])>1) { pAnalysis->ypos[jk]=-100; break;}
      pAnalysis->ypos[jk] +=ypts[jk][ix];
    }
  }
  pAnalysis->yyerr[jk] = errxco[jk]*errxco[jk];
  if (pAnalysis->ypos[jk]>=0.0) {
    pAnalysis->ypos[jk]  = pAnalysis->ypos[jk]/pAnalysis->yhits[jk] + 0.5;
    //Aligmnent Correction
    pAnalysis->ypos[jk] -= cal_slope2(pAnalysis->ypos[jk], &align_ystr_ydev[jk][0]);
    pAnalysis->yyerr[jk] = yposerrsq[pAnalysis->yhits[jk]-1][jk];
  }
  //Sort out hits, which can be used for fit
  pAnalysis->xusedpos[jk] = (pAnalysis->xpos[jk]>-100 && pAnalysis->xhits[jk]<=nmxhits) ? true : false;
  pAnalysis->yusedpos[jk] = (pAnalysis->ypos[jk]>-100 && pAnalysis->yhits[jk]<=nmxhits) ? true : false;
  ////////////////////////////////////////////////////////////////////////////////////////////////
  if(pAnalysis->xusedpos[jk]==true && jk==0){pAnalysis->counter[7]++;}
  ////////////////////////////////////////////////////////////////////////////////////////////////
}//Filled everything for fitting

//StraightLineFit
double zval[nlayer];
for (int ix=0; ix<nlayer; ix++) {
  zval[ix]=layerzpos[ix];
  pAnalysis->xext[ix]= pAnalysis->xextloc[ix] = pAnalysis->xexter[ix] =pAnalysis->xposinstr[ix] =  100;
  pAnalysis->yext[ix]= pAnalysis->yextloc[ix] = pAnalysis->yexter[ix] =pAnalysis->yposinstr[ix] =  100;
}

for(int occulyr=0;occulyr<=12;occulyr++)
{
//X-Side fit
StraightLineFit xposfit(1, zval, pAnalysis->xpos,  pAnalysis->xxerr, pAnalysis->xusedpos, occulyr, occulyr, layfirst, laylast, xyPosDev);
xposfit.GetParameters(pAnalysis->xfitfailed, pAnalysis->xintersect, pAnalysis->xslope);
xposfit.GetFitValues(pAnalysis->xext, pAnalysis->xdev, pAnalysis->xexter);
//Y-Side fit
StraightLineFit yposfit(1, zval, pAnalysis->ypos,  pAnalysis->yyerr, pAnalysis->yusedpos, occulyr, occulyr, layfirst, laylast, xyPosDev);
yposfit.GetParameters(pAnalysis->yfitfailed, pAnalysis->yintersect, pAnalysis->yslope);
yposfit.GetFitValues(pAnalysis->yext, pAnalysis->ydev, pAnalysis->yexter);
////////////////////////////////////////////////////////////////////////////////////////////////
if(occulyr==0){pAnalysis->counter[8]++;}
if(pAnalysis->xfitfailed==false && occulyr==0){pAnalysis->counter[9]++;}
if(pAnalysis->xfitfailed==true && occulyr==0){pAnalysis->counter[10]++;}
////////////////////////////////////////////////////////////////////////////////////////////////
for (int ix=0; ix<nlayer; ix++) {
  //if (pAnalysis->xpos[ix]>=0.0) {
    pAnalysis->xpos[ix] -=cal_slope2(pAnalysis->yext[ix], &align_ystr_xdev[ix][0]);
  //}
  //if (pAnalysis->ypos[ix]>=0.0) {
    pAnalysis->ypos[ix] -=cal_slope2(pAnalysis->xext[ix], &align_xstr_ydev[ix][0]);
  //}
}

//X-Side fit
xposfit = StraightLineFit(1, zval, pAnalysis->xpos,  pAnalysis->xxerr, pAnalysis->xusedpos, occulyr, occulyr, layfirst, laylast, xyPosDev);
xposfit.GetParameters(pAnalysis->xfitfailed, pAnalysis->xintersect, pAnalysis->xslope);
xposfit.GetFitValues(pAnalysis->xext, pAnalysis->xdev, pAnalysis->xexter);
xposfit.GetChisqure(pAnalysis->xndof,pAnalysis->xchisquare);
GetPosInStrip(0, pAnalysis->xext, pAnalysis->yext, pAnalysis->xposinstr, pAnalysis->xextloc);
//Y-Side fit
yposfit = StraightLineFit(1, zval, pAnalysis->ypos,  pAnalysis->yyerr, pAnalysis->yusedpos, occulyr, occulyr, layfirst, laylast, xyPosDev);
yposfit.GetParameters(pAnalysis->yfitfailed, pAnalysis->yintersect, pAnalysis->yslope);
yposfit.GetFitValues(pAnalysis->yext, pAnalysis->ydev, pAnalysis->yexter);
yposfit.GetChisqure(pAnalysis->yndof,pAnalysis->ychisquare);
GetPosInStrip(1, pAnalysis->yext, pAnalysis->xext, pAnalysis->yposinstr, pAnalysis->yextloc);

////////////////////////////////////////////////////////////////////////////////////////////////
if(occulyr==0){pAnalysis->counter[11]++;}
if(pAnalysis->xfitfailed==false && occulyr==0){pAnalysis->counter[12]++;}
if(pAnalysis->xfitfailed==true && occulyr==0){pAnalysis->counter[13]++;}
////////////////////////////////////////////////////////////////////////////////////////////////

if(occulyr<nlayer)
{
/*
if(occulyr==0){pAnalysis->counter[14]++;}
if (abs(pAnalysis->xdev[occulyr])<6.0 && pAnalysis->xusedpos[occulyr] && pAnalysis->xndof>=nmnhits && pAnalysis->xchisquare/(pAnalysis->xndof-2)<mxchisq&& pAnalysis->xfitfailed==false) {
  pAnalysis->xlayer_reso[occulyr]->Fill(pAnalysis->xdev[occulyr]);
  if(occulyr==0){pAnalysis->counter[15]++;}
}
if (abs(pAnalysis->ydev[occulyr])<6.0 && pAnalysis->yusedpos[occulyr] && pAnalysis->yndof>=nmnhits && pAnalysis->ychisquare/(pAnalysis->yndof-2)<mxchisq &&pAnalysis->yfitfailed==false) {
  pAnalysis->ylayer_reso[occulyr]->Fill(pAnalysis->ydev[occulyr]);
}
pAnalysis->totalentry[occulyr]->Fill(pAnalysis->xextloc[occulyr],pAnalysis->yextloc[occulyr]);
*/
}//less than occulyr=nlayer
else{

  for(int jk=0;jk<nlayer;jk++)
  {
    if(jk==0){pAnalysis->counter[14]++;}
    if (abs(pAnalysis->xdev[jk])<6.0 && pAnalysis->xusedpos[jk] && pAnalysis->xndof>=nmnhits && pAnalysis->xchisquare/(pAnalysis->xndof-2)<mxchisq&& pAnalysis->xfitfailed==false) {
      pAnalysis->xlayer_reso[jk]->Fill(pAnalysis->xdev[jk]);
      if(jk==0){pAnalysis->counter[15]++;}
    }
    if (abs(pAnalysis->ydev[jk])<6.0 && pAnalysis->yusedpos[jk] && pAnalysis->yndof>=nmnhits && pAnalysis->ychisquare/(pAnalysis->yndof-2)<mxchisq &&pAnalysis->yfitfailed==false) {
      pAnalysis->ylayer_reso[jk]->Fill(pAnalysis->ydev[jk]);
    }
    pAnalysis->totalentry[jk]->Fill(pAnalysis->xextloc[jk],pAnalysis->yextloc[jk]);
  }

} //occulyr = nlayer

}//occulyr loop end





























}

void EventAction::EndOfEventAction() {



}


Double_t EventAction::cal_slope2(Double_t x, Double_t* par) {
  if (x<nstrip/2. -0.5) {
    return par[0] + par[1]*(x - nstrip/4. +0.5);
  } else {
    double par3 = (par[2]-par[0]-par[1]*nstrip/4.)/(nstrip/4.);
    return par[2] + par3*(x - 3*nstrip/4. +0.5);
  }
}


void EventAction::GetPosInStrip(int ixy, double* ext, double* otherext, double* pos, double* local) {
  for (int ij=0; ij<nlayer; ij++) {
    local[ij] = ext[ij];
    if (ixy==0) {
      local[ij] +=cal_slope2(otherext[ij], &align_ystr_xdev[ij][0]);
      local[ij] +=cal_slope2(local[ij], &align_xstr_xdev[ij][0]);
    } else {
      local[ij] +=cal_slope2(otherext[ij], &align_xstr_ydev[ij][0]);
      local[ij] +=cal_slope2(local[ij], &align_ystr_ydev[ij][0]);
    }
    int istr = int(local[ij]);
    if (local[ij]<0.0) {
      pos[ij] = local[ij] - istr + 0.5;
    } else {
      pos[ij] = local[ij] - istr - 0.5;
    }
    local[ij] -= 0.5;
  }
}
