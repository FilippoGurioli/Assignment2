#ifndef SERVOTASK
#define SERVOTASK

#include "ITask.h"
#include "WaterDetectionTask.h"
#include "../Peripherals/Potentiometer/Potentiometer.h"
#include <ServoTimer2.h>

#define MINROT 750
#define MAXROT 2250

bool button = false;

class ServoTask: public ITask {

    private:
        ServoTimer2 servo;
        WaterDetectionTask* wdt;
        IPotentiometer* pot;
        int bPin;

    public:

        ServoTask(int sPin, int pPin, int bPin, WaterDetectionTask* wdt) {
            this->bPin = bPin;
            this->servo.attach(sPin);
            this->pot = new Potentiometer(pPin);
            this->wdt = wdt;
        }

        void init(int period) {
            ITask::init(period);
            this->servo.write(MINROT);
        }

        void tick() {
            if (button) {
                this->servo.write(map(this->pot->getValue(), 0, 1024, MINROT, MAXROT));
            } else {
                int wl = this->wdt->getDistance();
                wl = (wl < WL3) ? WL3 : wl;
                this->servo.write(map(wl, WL2, WL3, MINROT, MAXROT));
            }
        }

        void reset() {
            this->servo.write(MINROT);
            button = false;
        }

        int getAngle(){
            return map(this->servo.read(), MINROT, MAXROT, 0, 180);
        }

        void moveServo (int deg) {
            this->servo.write(deg);
        }

        
};

#endif