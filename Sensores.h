#ifndef SENSORES_YA_INCLUIDO
#define SENSORES_YA_INCLUIDO
#include <Wire.h> // Librería para usar el BUS I2C 
#include <Adafruit_ADS1X15.h> // Librería del ADS1115 
// ---------------------------------------------------
// ---------------------------------------------------
class Sensores {

    private:
        Adafruit_ADS1115* ads1115;
        //--->  Incluir las variables de calibración del sensor de salinidad 
        const int valorSin = 16300;  
        const int valorSal = 24800;   
        const int power_pin = 5;

        //--->  Incluir las variables de calibración del sensor de humedad 
        const int AirValue = 30218; 
        const int WaterValue = 17850; 

        // ---> Incluimos las variables del calculo de la temperatura.
        const float b = 0.79;
        const float m = 0.035;

        // --> Setup del deepSleep
        const int sleepTimeS = 30;
        int cont=0;

        // ---> Incluimos los valores de medición de luminosidad
        const double LumMax = 3.72;
        const double LumMin = 0.0005;

	public:
        
        Sensores();
        int funcionSalinidad();
        int16_t funcionHumedad();
        float funcionTemperatura();
        float funcionLuminosidad();
        void sleep();
	    

}; // class
// ---------------------------------------------------
#endif
