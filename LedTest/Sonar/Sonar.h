#ifndef SONAR
#define SONAR

#include "ISonar.h"
#include "Arduino.h"

class Sonar: public ISonar {

    private:
        int trig;
        int echo;

    public:
        Sonar(int trig, int echo) {
            this->trig = trig;
            this->echo = echo;
            pinMode(trig, OUTPUT);
            pinMode(echo, INPUT);
        }

        int getDistance() {
            digitalWrite(this->trig, HIGH);
            delayMicroseconds(10);
            digitalWrite(this->trig, LOW);
            return pulseIn(this->echo, HIGH) * 0.034 / 2;
        }
};

#endif