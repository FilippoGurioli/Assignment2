#ifndef PHOTORESISTOR
#define PHOTORESISTOR

#include "IPhotoresistor.h"
#include "Arduino.h"

class Photoresistor: public IPhotoresistor {

    private:
        int pin;
        int value;

    public:
        Photoresistor(int pin) {
            this->pin = pin;
            this->value = 0;
            pinMode(pin, INPUT);
        }
        
        int getLightLevel() {
            return analogRead(this->pin);
        }
};

#endif