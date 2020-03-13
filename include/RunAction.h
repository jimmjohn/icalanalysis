
#ifndef RunAction_h
#define RunAction_h 1

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TString.h"

#include "RootFileStruct.h"
#include "evetree.h"          //Contains root file format
#include "Constants.h"

#include "iostream"
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

class RunAction
{
  public:
    RunAction();
   ~RunAction();
    void BeginOfRunAction();
    void EndOfRunAction();
    void SetRunID(int run_id);
    UInt_t iev;
    TGraph *muonRate  = new TGraph();
    TGraph *pressRate = new TGraph();

    private:
    void SplitDataInMins();
    void SplitDataInSecs();
    int run_no;
    int run_ID;
    int fileno=1;
    double mintimebin=15.0*60.0;  //Fifteen Minutes
    double sectimebin=1.0;        //1 Second
    int splittermin=0;
    int splittersec=0;
    int noiseratemin=0;
    int noiseratesec=0;
    char rootfiles[100];
    char datafile[100];
    char infile[100];
    char outfile[100];
    char outfilx[100];
    time_t current_time=0;
    time_t start_time_min=0;
    time_t start_time_sec=0;
    //time_t sec=0;
    ifstream file_db;
    UInt_t nentry;

};

#endif
