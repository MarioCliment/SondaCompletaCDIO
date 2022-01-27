// Inclusion de librerias
#include "Acelerometro.h"
// Declarar global que controla la interrupcion.
        volatile bool flag;
// Declarar la funcion de lectura a traves del I2C (I2Cread)

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();

  Wire.requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (Wire.available())
    Data[index++] = Wire.read();
}
// Declarar la funcion de escritura a traves del I2C (I2CwirteByte)

void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

// Declarar la funcion que maneja la interrupcion (handleInterrupt)

void ICACHE_RAM_ATTR handleInterrupt()
{
 // Declarar aqui las instrucciones de la interrupcion
  flag = 1;
}

Acelerometro::Acelerometro()
{
  // Inicializar la comunicación por el bus I2C
  Wire.begin();
  
  // Inicializar la comunicación por la UART (Monitor serie)
  Serial.begin(9600);
  Serial.println("Inicializando...");
  
  // Configurar acelerometro 
  Serial.println("Configurando acelerónetro...");
  I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);

   // ---  Lectura acelerometro --- 
   uint8_t Buf[14];
   int FS_ACC = 16;
   float offset_x = -0.08;
   float offset_y = -0.04;
   float offset_z = 0.08;

   I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

  // Convertir registros acelerometro
   float ax = (Buf[0] << 8 | Buf[1]);
   float ay = (Buf[2] << 8 | Buf[3]);
   float az = (Buf[4] << 8 | Buf[5]);

   ax = (ax*FS_ACC/32768)+ offset_x ;
   ay = (ay*FS_ACC/32768)+ offset_y ;
   az = (az*FS_ACC/32768)+ offset_z ;
  
  // Configurar el modo Wake on Motion
  I2CwriteByte(0x68,0x6B,0x00); // PWR_MGMT 1
  
  I2CwriteByte(0x68,0x6C,0x07); // PWR_MGMT 2
  
  I2CwriteByte(0x68,0x1D,0x09); // ACCEL_CONFIG 2

  I2CwriteByte(MPU9250_ADDRESS,0X37,0X80); //INT_PIN_CFG
  
  I2CwriteByte(0x68,0x38,0x40); // INT_ENABLE
  
  I2CwriteByte(0x68,0x69,0xC0); // MOT_DETECT_CTRL
  
  I2CwriteByte(0x68,0x1F,0x05); // WOM_THR
  
  I2CwriteByte(0x68,0x1E,0x01); // LP_ACCEL_ODR
  
  I2CwriteByte(0x68,0x6B,0x20); // PWR_MGMT 1
  
  // Configurar el pin por el que introduciremos la interrupcion+
  pinMode(interruptPin, INPUT);
  
  // Asociar la interrupcion a la funcion que la maneja
  attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

}


int Acelerometro::devuelveFlag()
{ 
 // Si se da la interrupción poner un mensaje en el monitor serie
  if( flag == 1 ){
    return flag;
    flag=0;
    }
   return flag;
 }