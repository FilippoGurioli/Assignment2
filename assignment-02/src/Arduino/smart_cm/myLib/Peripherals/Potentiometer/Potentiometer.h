#ifndef POTENTIOMETER
#define POTENTIOMETER

#include "IPotentiometer.h"
#include "Arduino.h"

class Potentiometer: public IPotentiometer {

    private:
        int pin;

    public:
        Potentiometer(int pin) {
            this->pin = pin;
            pinMode(this->pin, INPUT);
        }

        int getValue() {
            return analogRead(this->pin);
        }
};

#endif