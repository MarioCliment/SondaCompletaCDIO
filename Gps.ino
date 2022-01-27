#include "Gps.h"

  GPS::GPS(){
    SoftwareSerial gps(12, 13);
    gps.begin(9600);
  }
  
  double GPS::devuelveAltitud(){
    int num=29;
    double resultado=0;
    for(int i=0;i<7;i++){
      num=num+i;
      resultado=dato[num];
      resultado=resultado*1000*pow(10,i);
    } 
    if(dato[38]=='E'){
    return resultado;  
    }
    return resultado*-1;
  }
  double GPS::devuelveLatitud(){
    int num=19;
    double resultado=0;
    for(int i=0;i<6;i++){
      num=num+i;
      resultado=dato[num];
      resultado=resultado*1000*pow(10,i);
    } 
    if(dato[27]=='N'){
    return resultado;  
    }
    return resultado*-1;
  }
