#ifndef GPS_YA_INCLUIDO
#define GPS_YA_INCLUIDO
#include <SoftwareSerial.h>
#include "TinyGPS++.h"
// ---------------------------------------------------
// ---------------------------------------------------
class GPS {
    
    private:
      char* dato;
      
    public:
      GPS();
      double devuelveAltitud();
      double devuelveLatitud();
      
}; // class
// ---------------------------------------------------
#endif
