#ifndef Constants_h
#define Constants_h

const double cval = 29.979; // velocity of light in cm/ns
static const unsigned int  nlayer =12; //Maximum RPC layers
const int  nstrip = 64; // Strips in RPC chamber
const int  nusedstrip =64; // Strips connected with Amplifier/ADC in RPC chamber
const int  lastXstrip =64; // last strip in X
const int  lastYstrip =64; // last strip in Y
const double  mxchisq =2.0;//15;//2.0;   //Maximum value of Normalised chi^2 (position fit);
const double  mxtimechisq=2.0; // Maximum value of Normalised chi^2 (time fit);
const double  accprng =1.0; //Acceptance region with respect tot strip centre
const double  effirng =0.25;//0.25;//0.25; //Additional region for efficeincy calculation
                           //Extrapolation error < 0.2 of strip width
const double pival=acos(-1);
const double stripwidth = 3.0; // cm
const double stripgap = 0.2; // cm
const double layergap = 16.0; // cm
const int  nTDCpLayer=8;
const int nmxhits=4;
const int nmnhits =4;//Minimum number of layers required for position and time measurements
const int nmxusedhits=3;
const int nmxtimehit=4;
const int nmxusedtimehit=3;
const int nPosAlignPar=3;
//Used for fitting
const double layerzpos[nlayer] = {0.0, 17.80, 34.40, 51.10, 68.10, 85.10, 101.50, 118.30, 135.30, 151.9, 169.0, 185.50};
const int  layfirst =0;  //Used first layer in track fitting
const int  laylast =11;  //Used last layer in track fitting
const float xyPosDev = 3.0; // seven sigma 2.0; //maximum deviation of points from fit line

//Trigger layers
const int trigly1 =2;
const int trigly2 =4;
const int trigly3 =7;
const int trigly4 =9;



#endif
