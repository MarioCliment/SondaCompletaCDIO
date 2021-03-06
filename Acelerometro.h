#ifndef ACELEROMETRO_YA_INCLUIDO
#define ACELEROMETRO_YA_INCLUIDO
#include <Wire.h> // Librería para usar el BUS I2C 
// ---------------------------------------------------
// ---------------------------------------------------
class Acelerometro {
    
    private:
    // Definicion de parametros de configuracion del acelerometro
      #define    MPU9250_ADDRESS            0x68
      #define    MAG_ADDRESS                0x0C
      
      #define    GYRO_FULL_SCALE_250_DPS    0x00
      #define    GYRO_FULL_SCALE_500_DPS    0x08
      #define    GYRO_FULL_SCALE_1000_DPS   0x10
      #define    GYRO_FULL_SCALE_2000_DPS   0x18
      
      #define    ACC_FULL_SCALE_2_G        0x00
      #define    ACC_FULL_SCALE_4_G        0x08
      #define    ACC_FULL_SCALE_8_G        0x10
      #define    ACC_FULL_SCALE_16_G       0x18
    // Definicion del pin de interrupcion
      #define interruptPin  4

	public:
        Acelerometro();
        int devuelveFlag();
}; // class
// ---------------------------------------------------
#endif
