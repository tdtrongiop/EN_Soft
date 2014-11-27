#ifndef ENFiberCal_H
#define ENFiberCal_H

#include <TH1.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSystem.h>
#include <vector>
//#include "TArtEventStore.hh"
#include "segidlist.h"

using namespace std;

class ENFiberCal{
 private:
   int traw[128];
   int trawt[128];
   double tcal[128][2];
   double ch2ns[128];
   double threshold_t;
   double threshold_Y;
   double ns2mm[2];
   double offset[2];
   double posY[305];
   double weiY[305];
   double posX,posY1,width;

   int flagprm;
   char* GetNextLine(char s ='#' );
   int Put2Array(char*, int*,int);
   int Put2Array(char*, double*,int);
   char* ltrim(char*);
   char* rtrim(char*);
   char* trim(char*);
   ifstream fi;
 public:
  ENFiberCal();
  ENFiberCal(char* filename);
  ~ENFiberCal();  
  void SetLeading(int ch, int val){traw[ch] = val;};
  void SetTrailing(int ch, int val){trawt[ch] = val;}; 
  void Reset(int val = 0){
       memset(traw ,val,sizeof(traw));
       memset(trawt,val,sizeof(trawt));};
  int ReadParameters(char* filename);
  void SetPosition();
  void SetPosition(int,int* );
  double GetX_Position(){return posX;};
  double GetY_Position(){return posY1;};
  double GetY_Position(int no){return posY[no];};
  double Get_Width(){return width;};
  int segid;
  int detid;
  int modid;
};
#endif
