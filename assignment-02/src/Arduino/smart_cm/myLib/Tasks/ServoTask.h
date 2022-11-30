#ifndef SERVOTASK
#define SERVOTASK

#include "ITask.h"
#include "../Peripherals/Potentiometer/Potentiometer.h"
#include <ServoTimer2.h>

#define MINROT 750
#define MAXROT 2250

bool button = false;
int servoAngle = 0;

class ServoTask: public ITask {

    private:
        ServoTimer2 servo;
        IPotentiometer* pot;

    public:

        ServoTask(int sPin, int pPin, int bPin) {
            this->servo.attach(sPin);
            this->pot = new Potentiometer(pPin);
        }

        void init(int period) {
            ITask::init(period);
            this->servo.write(MINROT);
        }

        void tick() {
            if (button) {
                int var = this->pot->getValue();
                this->servo.write(map(var, 0, 1024, MINROT, MAXROT));
                servoAngle = map(var, 0, 1024, 0, 181);
            } else {
                int var = (wl < WL3) ? WL3 : wl;
                this->servo.write(map(var, WL2, WL3, MINROT, MAXROT));
                servoAngle = map(var, WL2, WL3, 0, 181);
            }
        }

        void reset() {
            this->servo.write(MINROT);
            button = false;
            servoAngle = 0;
        }

        void moveServo (int deg) {
            this->servo.write(deg);
        }

        
};

#endif