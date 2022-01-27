#include "Sensores.h"
//---------------------------------------------------------------
//
//   Constructor
//
//---------------------------------------------------------------
Sensores::Sensores(){
  ads1115->begin();
  ads1115->setGain(GAIN_ONE); 
}
//---------------------------------------------------------------
//
//  funciónSalinidad() --> R
//
//---------------------------------------------------------------
int Sensores::funcionSalinidad (){ 

// Configurar power_pin como pin de salida (Para sensor de salinidad) 
  pinMode(power_pin, OUTPUT);
//--->  Variables del programa 
  int16_t salinidad; 
  int16_t adc1; 
  salinidad = 0;
//---> Poner power_pin a nivel alto 
  digitalWrite(power_pin, HIGH); 
  
  adc1 = ads1115->readADC_SingleEnded(1); //Asignar el valor leido por el micro a una variable.
//--->  Esperar 100ms 
  delay(100); 
  
//--->  Poner power_pin a nivel bajo 
  digitalWrite(power_pin,LOW); 
  

  salinidad = 100*valorSin/(valorSin-valorSal)-adc1*100/(valorSin-valorSal); 
  
  if (salinidad>=100){ // Limitador de porcentajes.

    salinidad=100; 
  } 

  if (salinidad<=0){  

    salinidad=0; 
  } 
Serial.print(analogRead( power_pin));
return salinidad; 

} 

//---------------------------------------------------------------------  
//
// funciónHumedad() --> R
//
//---------------------------------------------------------------------
int16_t Sensores::funcionHumedad (){ 

//--->  Variables del programa 
  int16_t adc0; 
  int16_t humedad; 
  
  adc0 = ads1115->readADC_SingleEnded(0); //Asignar el valor leido por el micro a una variable.
  
  humedad = 100*AirValue/(AirValue-WaterValue)-adc0*100/(AirValue-WaterValue);   

  if (humedad>=100){ // Limitador de porcentajes.

    humedad=100; 
  } 

  if (humedad<=0){  

    humedad=0; 
  } 

return humedad; 

} 

//---------------------------------------------------------------------  
//
//  funciónTemperatura() --> R
//
//---------------------------------------------------------------------
float Sensores::funcionTemperatura(){

//--->  Variables del programa 
  int16_t adc2;
  float voltios, temperatura;
  
  adc2=ads1115->readADC_SingleEnded(2);  //Asignar el valor leido por el micro a una variable.
  
  voltios = 4.096*adc2/(pow(2,15)-1); 
  temperatura = (voltios - b)/m;

  return temperatura;
}

//---------------------------------------------------------------------  
//
//  funciónLuminosidad() --> R
//
//---------------------------------------------------------------------
float Sensores::funcionLuminosidad(){

//--->  Variables del programa 
  int16_t adc3;
  float luminosidad, volts;

  adc3=ads1115->readADC_SingleEnded(3);  //Asignar el valor leido por el micro a una variable.
  
  volts = 4.096*adc3/(pow(2,15)-1); 
  luminosidad = (volts - LumMin)/LumMax;

  luminosidad = 100*LumMin/(LumMin-LumMax)-volts*100/(LumMin-LumMax);

  if (luminosidad>=100){  // Limitador de porcentajes.

    luminosidad=100; 
  } 

  if (luminosidad<=0){  

    luminosidad=0; 
  } 
  
  return luminosidad;
}

//------------------------------------------------------------------------------
//
//  Sleep()
//
//-------------------------------------------------------------------------------
/*void Sensores::sleep(){
  
  if (cont<20){
    cont++;
    delay(1000);
  }
  else{
    Serial.println("ESP8266 in sleep mode");
  }   
  ESP.deepSleep(sleepTimeS * 1000000);
  }
*/
