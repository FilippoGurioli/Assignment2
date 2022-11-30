#ifndef LED
#define LED

#include "ILed.h"
#include "Arduino.h"

class Led: public ILed {

    private:
        int pin;
        bool state;

    public:
        Led(int pin) {
            this->pin = pin;
            this->state = false;
            pinMode(pin, OUTPUT);
        }

        void switchOn() {
            digitalWrite(pin, HIGH);
            state = true;
        }
        
        void switchOff() {
            digitalWrite(pin, LOW);
            state = false;
        }

        bool isOn() {
            return state;
        }
        
};

#endif