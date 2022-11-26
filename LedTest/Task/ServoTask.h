#ifndef SERVOTASK
#define SERVOTASK

#include "ITask.h"
#include "WaterDetectionTask.h"
#include <ServoTimer2.h>
#include "../Potentiometer/Potentiometer.h"

#define MINROT 750
#define MAXROT 2250


class ServoTask: public ITask {

    private:
        ServoTimer2 servo;
        WaterDetectionTask* wdt;
        IPotentiometer* pot;

    public:

        ServoTask(int sPin, int pPin, WaterDetectionTask* wdt) {
            this->servo.attach(sPin);
            this->pot = new Potentiometer(pPin);
            this->wdt = wdt;
        }

        void init(int period) {
            ITask::init(period);
            this->servo.write(MINROT);
        }

        void tick() {
            int wl = this->wdt->getDistance();
            wl = (wl < WL3) ? WL3 : wl;
            //this->servo.write(map(wl, WL2, WL3, MINROT, MAXROT));
            this->servo.write(map(this->pot->getValue(), 0, 1024, MINROT, MAXROT));
        }

        void reset() {
            this->servo.write(MINROT);
        }
};

#endif