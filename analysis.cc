#include <iostream>
#include <functional>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <new>
#include <climits>
#include <vector>

//Root Header Files
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TDatime.h"
#include "TStyle.h"
#include "TAttFill.h"
#include "TPaveStats.h"
#include "TMinuit.h"
#include "TPostScript.h"
#include "TFitResult.h"
#include "TFitResultPtr.h"
#include "TRandom.h"
#include "TPaletteAxis.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TMath.h"

//Custom made classes
#include "StraightLineFit.h"  // For fitting with a straight line
#include "Constants.h"        // All the constants are put inside this file
#include "RunAction.h"
#include "RootFileStruct.h"

using namespace std;

int main() {
  [out=std::ref(std::cout << "Pressure")](){out.get() << " Coefficient Project\n"; }();
  RootFileStruct *pAnalysis = new RootFileStruct();
  RunAction *runAct = new RunAction();
  runAct->BeginOfRunAction();
  runAct->EndOfRunAction();
  return 0;
}
