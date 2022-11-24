#ifndef PIR
#define PIR

#include "IPir.h"
#include "Arduino.h"

class Pir: public IPir {

    private:
        int pin;
    
    public:
        Pir(int pin) {
            this->pin = pin;
            pinMode(pin, INPUT);
        }

        bool getPresence() {
            return digitalRead(this->pin);
        }
        
};

#endif