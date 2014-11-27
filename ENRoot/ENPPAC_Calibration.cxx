#include "ENPPAC_Calibration.h"

ENPPAC_Calibration::ENPPAC_Calibration()
{
  F2distance=482;F3distance=500;
  char fn[20];
  sprintf(fn,"ppac.prm");
  flagprm = ReadParameters(fn);
}
ENPPAC_Calibration::ENPPAC_Calibration(char* filename)
{
  F2distance=482;F3distance=500;
  flagprm = ReadParameters(filename);
}
// ***********************************************************************
ENPPAC_Calibration::~ENPPAC_Calibration(){}
// ***********************************************************************
void   ENPPAC_Calibration::SetPosition(int ppacNo, int Left,int Right,int Down,int Up ){
  if (flagprm<0) printf("  Khong doc dc prm file\n");
  traw[ppacNo][0]=Left;
  traw[ppacNo][1]=Down;
  traw[ppacNo][2]=Right;
  traw[ppacNo][3]=Up;
  for (int i=0;i<4;i++) tcal[ppacNo][i]=traw[ppacNo][i]*ch2ns[ppacNo][i];
  if (traw[ppacNo][0]>0 && traw[ppacNo][2]>0) {
       posXns[ppacNo] = tcal[ppacNo][0] - tcal[ppacNo][2];
       posXmm[ppacNo] = posXns[ppacNo]*ns2mm[ppacNo][0] -offset[ppacNo][0];
  }else{ 
       posXns[ppacNo]=-1000;
       posXmm[ppacNo]=-1000;
  }  
  if (traw[ppacNo][1]>0 && traw[ppacNo][3]>0) {
       posYns[ppacNo] = tcal[ppacNo][1] - tcal[ppacNo][3];
       posYmm[ppacNo] = posYns[ppacNo]*ns2mm[ppacNo][1] -offset[ppacNo][1];
  }else{ 
       posYns[ppacNo]=-1000;
       posYmm[ppacNo]=-1000;
  }
}
// ***********************************************************************
void   ENPPAC_Calibration::SetPosition(int ppacNo, int start, int* rawin){
  for (int i=0;i<5;i++){
    traw[ppacNo][i] = rawin[start+i];
    traw[ppacNo+1][i] = rawin[start+5+i];
  }
  for (int i=0;i<2;i++)
    for (int j=0;j<5;j++){
      tcal[ppacNo+i][j] = traw[ppacNo+i][j]*ch2ns[ppacNo+i][j];
    }
  for (int i=0;i<2;i++){
    if (traw[ppacNo+i][0]>0 && traw[ppacNo+i][2]>0){ 
       posXns[ppacNo+i] = tcal[ppacNo+i][0] - tcal[ppacNo+i][2];
       posXmm[ppacNo+i] = posXns[ppacNo+i]*ns2mm[ppacNo+i][0] -offset[ppacNo+i][0];
    }else{
       posXns[ppacNo+i]=-1000;
       posXmm[ppacNo+i]=-1000;
    }
    if (traw[ppacNo+i][1]>0 && traw[ppacNo+i][3]>0){ 
       posYns[ppacNo+i] = tcal[ppacNo+i][1] - tcal[ppacNo+i][3];
       posYmm[ppacNo+i] = posYns[ppacNo+i]*ns2mm[ppacNo+i][1] -offset[ppacNo+i][1];
    }else{
       posYns[ppacNo+i]=-1000;
       posYmm[ppacNo+i]=-1000;
    }
  }
}
// ***********************************************************************
void   ENPPAC_Calibration::SetPosition(int start1, int* rawin1, int start2, int* rawin2){
  for (int i=0;i<5;i++){
    traw[1][i] = rawin1[start1+i];
    traw[2][i] = rawin1[start1+5+i];
    traw[3][i] = rawin2[start2+i];
    traw[4][i] = rawin2[start2+5+i];
  }
  for (int i=0;i<5;i++)
    for (int j=0;j<5;j++){
      tcal[i][j] = traw[i][j]*ch2ns[i][j];
    }
  for (int i=1;i<5;i++){
    if (traw[i][0]>0 && traw[i][2]>0){ 
       posXns[i] = tcal[i][0] - tcal[i][2];
       posXmm[i] = posXns[i]*ns2mm[i][0] -offset[i][0];
    }else{
       posXns[i]=-1000;
       posXmm[i]=-1000;
    }
    if (traw[i][1]>0 && traw[i][3]>0){ 
       posYns[i] = tcal[i][1] - tcal[i][3];
       posYmm[i] = posYns[i]*ns2mm[i][1] -offset[i][1];
    }else{
       posYns[i]=-1000;
       posYmm[i]=-1000;
    }
  }
}
// ***********************************************************************
double ENPPAC_Calibration::GetF2_aX_mrad(){
   double exX;
   if (abs(posXmm[1])<50 && abs(posXmm[2])<50)
      exX =  atan2(posXmm[2] - posXmm[1],F2distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double ENPPAC_Calibration::GetF2_aY_mrad(){
   double exX;
   if (abs(posYmm[1])<50 && abs(posYmm[2])<50)
      exX =  atan2(posYmm[2] - posYmm[1],F2distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double ENPPAC_Calibration::GetF3_aX_mrad(){
  double exX;
   if (abs(posXmm[3])<50 && abs(posXmm[4])<50)
      exX =  atan2(posXmm[4] - posXmm[3],F3distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double ENPPAC_Calibration::GetF3_aY_mrad(){
   double exX;
   if (abs(posYmm[3])<50 && abs(posYmm[4])<50)
      exX =  atan2(posYmm[4] - posYmm[3],F3distance);
   else exX = -10;
   return exX*1000;
}
// ***********************************************************************
double ENPPAC_Calibration::GetF2ExtrapolationX(double atZ){
   double exX;
   if (abs(posXmm[1])<50 && abs(posXmm[2])<50)
      exX =  posXmm[1] + (posXmm[2] - posXmm[1])*atZ/F2distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double ENPPAC_Calibration::GetF2ExtrapolationY(double atZ){
  double exX;
   if (abs(posYmm[1])<50 && abs(posYmm[2])<50)
      exX =  posYmm[1] + (posYmm[2] - posYmm[1])*atZ/F2distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double ENPPAC_Calibration::GetF3ExtrapolationX(double atZ){
  double exX;
   if (abs(posXmm[3])<50 && abs(posXmm[2])<50)
      exX =  posXmm[3] + (posXmm[4] - posXmm[3])*atZ/F3distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
double ENPPAC_Calibration::GetF3ExtrapolationY(double atZ){
   double exX;
   if (abs(posYmm[3])<50 && abs(posYmm[4])<50)
      exX =  posYmm[3] + (posYmm[4] - posYmm[3])*atZ/F3distance;
   else exX = -1000;
   return exX;
}
// ***********************************************************************
int ENPPAC_Calibration::ReadParameters(char* filename){
   fi.open(filename,ios::in);
  if (fi.is_open()){
    double valread[5];
    int ch2nsflag;
    char* buff;
    //read ch2ns 
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,5) == -1) goto l20;
         for (int j=0;j<5;j++) ch2ns[i][j]=valread[j];
       }else for (int j=0;j<5;j++) ch2ns[i][j]=1.;
     }
    //read qdc
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,5) == -1) goto l20;
         for (int j=0;j<5;j++) ch2qdc[i][j]=valread[j];
       }else for (int j=0;j<5;j++) ch2qdc[i][j]=1.;
     }
     //read qdc ped
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,5) == -1) goto l20;
         for (int j=0;j<5;j++) qdcped[i][j]=valread[j];
       }else for (int j=0;j<5;j++) qdcped[i][j]=0;
     }

   //  ns2mm
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,2) == -1) goto l20;
         for (int j=0;j<2;j++) ns2mm[i][j]=valread[j];
       }else for (int j=0;j<2;j++) ns2mm[i][j]=1.;
     }
     //  in off set
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,2) == -1) goto l20;
         for (int j=0;j<2;j++) in_offset[i][j]=valread[j];
       }else for (int j=0;j<2;j++) in_offset[i][j]=0.;
     }
    //  out off set
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,2) == -1) goto l20;
         for (int j=0;j<2;j++) out_offset[i][j]=valread[j];
       }else for (int j=0;j<2;j++) out_offset[i][j]=0.;
     }
      //  geometry off set
    buff = GetNextLine('c');if (buff ==NULL) goto l20;
    ch2nsflag = atoi(buff);
    for (int i=0;i<5;i++){
       buff = GetNextLine('c');if (buff ==NULL) goto l20;
       if (ch2nsflag==1){
         if (Put2Array(buff,valread,2) == -1) goto l20;
         for (int j=0;j<2;j++) geo_offset[i][j]=valread[j];
       }else for (int j=0;j<2;j++) geo_offset[i][j]=0.;
     }
     for (int i=0;i<5;i++){
       for (int j=0;j<2;j++) offset[i][j]= in_offset[i][j]+out_offset[i][j]+geo_offset[i][j];
     }

     fi.close();
     printf("ENPPAC_Calibration: Parameters file :\"%s\" |--> LOADED!!!.\n",filename); 
     return 0;
  }else{
     printf("ENPPAC_Calibration: Parameters file :\"%s\" cannot open |--> NOT load!!!\n",filename);
     goto def;
  }
l20:  printf("ENPPAC_Calibration: Parameters file :\"%s\" not true format |--> NOT load!!!\n",filename);
def:;
  for (int i=0;i<5;i++){
     for (int j=0;j<5;j++){
        ch2ns[i][j]= 1;
        ch2qdc[i][j] =1;
        qdcped[i][j] =0;
     }
  }
  for (int i=0;i<5;i++){
     for (int j=0;j<2;j++){
        ns2mm[i][j] = 1;
   	in_offset[i][j] = 0;
   	out_offset[i][j] = 0;
   	geo_offset[i][j] = 0;
        offset[i][j]= in_offset[i][j]+out_offset[i][j]+geo_offset[i][j];
     }
  }
  return -1;
}

// ***********************************************************************
char* ENPPAC_Calibration::ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
// *********************************************************************** 
char* ENPPAC_Calibration::rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
// ***********************************************************************
char * ENPPAC_Calibration::trim (char s[])
{
    return ltrim(rtrim(s));  
}
// ***********************************************************************
int ENPPAC_Calibration::Put2Array(char*s,double* val,int nval){
  int nf =0;
  s = trim(s);
  char * pch;
  pch = strtok (s," 	");
  while (pch != NULL && nf<nval)
  {
    val[nf] = atof(pch);
    pch = strtok (NULL, " 	");
    nf++;
  }
  if (pch != NULL) strcpy(s,pch);
  if (nf<nval) return -1;
  return 0;
}
// ***********************************************************************
int ENPPAC_Calibration::Put2Array(char* s,int* val,int nval){
  int nf =0;
  s = trim(s);
  char * pch;
  pch = strtok (s," 	");
  while (pch != NULL && nf<nval)
  {
    val[nf] = atoi(pch);
    pch = strtok (NULL, " 	");
    nf++;
  }
  if (pch != NULL) strcpy(s,pch);
  if (nf<nval) return -1;
  return 0;
}
// ***********************************************************************
char* ENPPAC_Calibration::GetNextLine(char s){
   char buffer[1000];
   char* buff; 
//   ifstream fi;
    while (1)
    {
        if (fi.eof()) return NULL;
        buffer[0] = '\0';
        fi.getline(buffer, 1000, '\n');
        buff=trim(buffer);
        if (strlen(buff) > 0)
        {
            if (buff[0] != s)
            {
                return buff;
            }
        }
    }
    return NULL; 
}
// ***********************************************************************
