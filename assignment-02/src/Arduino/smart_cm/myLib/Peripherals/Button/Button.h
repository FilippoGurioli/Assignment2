#ifndef BUTTON
#define BUTTON

#include "IButton.h"
#include "Arduino.h"

class Button: public IButton {

    private:
        int pin;
        bool on;
        bool changed;

    public:
        Button(int pin) {
            this->pin = pin;
            pinMode(this->pin, INPUT);
            on = false;
            changed = false;
        }

        void listen() {
            bool var = digitalRead(this->pin);
            if (var && !changed) {
                this->on = !this->on;
                changed = true;
            } else if (!var) {
                changed = false;
            }
        }

        bool isOn() {
            return on;
        }
};

#endif