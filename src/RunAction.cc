
#include "TPostScript.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "RunAction.h"
#include "SingleEvent.h"
#include "EventAction.h"

#include <algorithm>

SingleEvent *sEvt = new SingleEvent();

RunAction::RunAction()
{//In case if you wan to pass some details from input file
//theRunActMessenger = new Ical0RunActionMessenger(this);

}
RunAction::~RunAction() {
//  delete theRunActMessenger; theRunActMessenger=0;
}

void RunAction::BeginOfRunAction() {
  RootFileStruct *pAnalysis = RootFileStruct::AnPointer;
  EventAction *eAct = new EventAction();
  //Opening data files one by one
  sprintf(rootfiles, "data.log");
	file_db.open(rootfiles);
  while(!(file_db.eof())) {
	  file_db >> datafile;           //Each root file name
	  if (strstr(datafile,"#")) continue;
	  if(file_db.eof()) break;

    int len = strlen(datafile);
    strncpy(outfilx, datafile, len-4);
    outfilx[len-4]='\0';
    sprintf(outfile, "%s.root", outfilx);
    len = strlen(outfile);
    outfile[len]='\0';
    //pAnalysis->InputOutput=InputOutput;
    pAnalysis->OpenRootfiles(outfile);

    sprintf(outfile, "%s.ps", outfilx);
    TPostScript ps(outfile,111);
    ps.Range(20,30); //ps.Range(10,20);
    TCanvas *c1=new TCanvas ("c1","Muon and Pressure Plot",500,700);
    c1->Divide(1,2);

    cout<<"FileNo:"<<fileno<<"------"<<datafile<<endl;
    fileno++;
    //__________________________________________________________________________
    //Tree reading and Each event is readed
    sprintf(infile, "data/%s",datafile);
    TFile *fileIn = new TFile(infile, "read");
    TTree *event_tree=(TTree*)fileIn->Get("evetree");
    evetree *event = new evetree(event_tree);
    //__________________________________________________________________________
    //event->Loop();
    nentry = event_tree->GetEntries();
    for(iev=0;iev<nentry;iev++) {
	    event_tree->GetEntry(iev);
      sEvt->evt_no=iev;
      copy(begin(event->ENum), end(event->ENum), begin(sEvt->ENum));
      copy(begin(event->REnum), end(event->REnum), begin(sEvt->REnum));
      sEvt->CEnum=event->CEnum;
      copy(begin(event->EveTS), end(event->EveTS), begin(sEvt->EveTS));
      copy(begin(event->xLayer), end(event->xLayer), begin(sEvt->xLayer));
      copy(begin(event->yLayer), end(event->yLayer), begin(sEvt->yLayer));
      copy(begin(event->tdc_ref_l), end(event->tdc_ref_l), begin(sEvt->tdc_ref_l));
      copy(begin(event->tdc_ref_t), end(event->tdc_ref_t), begin(sEvt->tdc_ref_t));
      copy(begin(event->trigCntDiff), end(event->trigCntDiff), begin(sEvt->trigCntDiff));
      copy(&event->xtdchit_l[0][0], &event->xtdchit_l[0][0]+12*8,&sEvt->xtdchit_l[0][0]);
      copy(&event->ytdchit_l[0][0], &event->ytdchit_l[0][0]+12*8,&sEvt->ytdchit_l[0][0]);
      copy(&event->xtdc_l[0][0][0], &event->xtdc_l[0][0][0]+12*8*256,&sEvt->xtdc_l[0][0][0]);
      copy(&event->ytdc_l[0][0][0], &event->ytdc_l[0][0][0]+12*8*256,&sEvt->ytdc_l[0][0][0]);
      copy(&event->xtdchit_t[0][0], &event->xtdchit_t[0][0]+12*8,&sEvt->xtdchit_t[0][0]);
      copy(&event->ytdchit_t[0][0], &event->ytdchit_t[0][0]+12*8,&sEvt->ytdchit_t[0][0]);
      copy(&event->xtdc_t[0][0][0], &event->xtdc_t[0][0][0]+12*8*256,&sEvt->xtdc_t[0][0][0]);
      copy(&event->ytdc_t[0][0][0], &event->ytdc_t[0][0][0]+12*8*256,&sEvt->ytdc_t[0][0][0]);

      if(iev>0)
      {
      SplitDataInSecs();
      SplitDataInMins();
      }
      noiseratemin++;
      noiseratesec++;

      eAct->BeginOfEventAction();




    }

    ps.NewPage();
    gStyle->SetOptStat(0);
    gStyle->SetPadBottomMargin(0.11);
    gStyle->SetPadTopMargin(0.07);
    gStyle->SetPadLeftMargin(0.10);
    gStyle->SetPadRightMargin(0.11);
    gStyle->SetOptTitle(1);
    muonRate->SetMarkerColor(2);
    muonRate->GetXaxis()->SetTitle("Time");
    muonRate->GetYaxis()->SetTitle("Muon Rate in sec");
    muonRate->GetXaxis()->CenterTitle();
    muonRate->GetYaxis()->CenterTitle();
    //grxextlocouttwin->GetXaxis()->SetTitleSize(0.055);
    //grxextlocouttwin->GetYaxis()->SetLabelSize(0.065);
    muonRate->GetXaxis()->SetTitleOffset(1.4);
    muonRate->GetXaxis()->SetTitleFont(62);
    muonRate->GetYaxis()->SetTitleFont(62);
    muonRate->GetXaxis()->SetLabelFont(62);
    muonRate->GetYaxis()->SetLabelFont(62);
    muonRate->GetXaxis()->SetTitleOffset(1.25);
    muonRate->GetXaxis()->SetTickLength(0.05);
    muonRate->GetYaxis()->SetTickLength(0.03);
    muonRate->GetXaxis()->SetLabelOffset(0.002);
    muonRate->GetYaxis()->SetLabelOffset(0.01);
    muonRate->SetTitle();
    c1->cd(1);
    muonRate->Draw("AP");
    c1->Update();
    ps.Close();
  }


}

void RunAction::EndOfRunAction() {
  RootFileStruct *pAnalysis = RootFileStruct::AnPointer;
  cout<<"Counter 0 = "<<pAnalysis->counter[0]<<endl;
  cout<<"Counter 1 = "<<pAnalysis->counter[1]<<endl;
  cout<<"Counter 2 = "<<pAnalysis->counter[2]<<endl;
  cout<<"Counter 3 = "<<pAnalysis->counter[3]<<endl;
  cout<<"Counter 4 = "<<pAnalysis->counter[4]<<endl;
  cout<<"Counter 5 = "<<pAnalysis->counter[5]<<endl;
  cout<<"Counter 6 = "<<pAnalysis->counter[6]<<endl;
  cout<<"Counter 7 = "<<pAnalysis->counter[7]<<endl;
  cout<<"Counter 8 = "<<pAnalysis->counter[8]<<endl;
  cout<<"Counter 9 = "<<pAnalysis->counter[9]<<endl;
  cout<<"Counter 10 = "<<pAnalysis->counter[10]<<endl;
  cout<<"Counter 11 = "<<pAnalysis->counter[11]<<endl;
  cout<<"Counter 12 = "<<pAnalysis->counter[12]<<endl;
  cout<<"Counter 13 = "<<pAnalysis->counter[13]<<endl;
  cout<<"Counter 14 = "<<pAnalysis->counter[14]<<endl;
  cout<<"Counter 15 = "<<pAnalysis->counter[15]<<endl;
  cout<<"Counter 16 = "<<pAnalysis->counter[16]<<endl;
  cout<<"Counter 17 = "<<pAnalysis->counter[17]<<endl;

  pAnalysis->CloseRootfiles();
}


void RunAction::SplitDataInMins()
{
  current_time=sEvt->EveTS[0]->GetSec();
  if(current_time==0){return;}
  if(difftime(current_time,start_time_min)>=mintimebin)
  {
    start_time_min=current_time;
    cout<<"Fifteen Minutes Passed, Counts="<<noiseratemin/mintimebin<<endl;
    sEvt->splitter=splittermin;
    splittermin++;
    noiseratemin=0;
  }
}
void RunAction::SplitDataInSecs()
{
  current_time=sEvt->EveTS[0]->GetSec();
  if(current_time==0){return;}
  if(difftime(current_time,start_time_sec)>=sectimebin)
  {
    start_time_sec=current_time;
    muonRate->SetPoint(splittersec,splittersec/(60.0*60.0),noiseratesec/sectimebin);
    noiseratesec=0;
    splittersec++;
  }
}



void RunAction::SetRunID(int run_id) {
  run_ID = run_id ;
}
