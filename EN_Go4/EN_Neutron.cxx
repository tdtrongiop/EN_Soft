#include "EN_Neutron.h"

EN_Neutron::EN_Neutron()
{
  analyser=5;
   printf("EN_Neutron:   Initializing - %d\n", analyser); 
}
EN_Neutron::EN_Neutron(char* filename)
{
  analyser=5;
   printf("EN_Neutron:   Initializing - %d\n", analyser); 
}
// ***********************************************************************
EN_Neutron::~EN_Neutron(){}
// ***********************************************************************
void   EN_Neutron::ENcode(int raw[10][10][256], double val[10][10][256], int nval ){

   for (int i=0;i<8;i++){
	qraw[i] = raw[analyser][1][i];
	qraw[i+8] = raw[analyser][3][i];
        traw[i] = raw[analyser][2][i];
        traw[i+8] = raw[analyser][4][i];
   }
   for (int i=0;i<16;i++){
	val[analyser][1][i+1] = qraw[i];
        val[analyser][2][i+1] = traw[i];
   }
}

// ***********************************************************************
int EN_Neutron::ReadParameters(char* filename){
   
  return -1;
}

// ***********************************************************************
char* EN_Neutron::ltrim (char s[])
{
    while (*s == 32) s++;
    return s;
}
// *********************************************************************** 
char* EN_Neutron::rtrim (char s[])
{
    int i = 0;
    while (s[i]) i++ ;
    while (s[i-1]==32) i--;
    s[i] = 0 ;
    return s;  
}
// ***********************************************************************
char * EN_Neutron::trim (char s[])
{
    return ltrim(rtrim(s));  
}
// ***********************************************************************
int EN_Neutron::Put2Array(char*s,double* val,int nval){
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
int EN_Neutron::Put2Array(char* s,int* val,int nval){
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
char* EN_Neutron::GetNextLine(char s){
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
