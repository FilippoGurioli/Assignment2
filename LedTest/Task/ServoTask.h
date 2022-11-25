#ifndef SERVOTASK
#define SERVOTASK

#include "ITask.h"
#include <ServoTimer2.h>
#include "WaterDetectionTask.h"

#define MINROT 750
#define MAXROT 2250


class ServoTask: public ITask {

    private:
        ServoTimer2 servo;
        WaterDetectionTask* wdt;

    public:

        ServoTask(int sPin, WaterDetectionTask* wdt) {
            this->servo.attach(sPin);
            this->wdt = wdt;
        }

        void init(int period) {
            ITask::init(period);
            this->servo.write(MINROT);
        }

        void tick() {
            int wl = this->wdt->getDistance();
            wl = (wl < WL3) ? WL3 : wl;
            this->servo.write(map(wl, WL2, WL3, MINROT, MAXROT));
        }

        void reset() {
            this->servo.write(MINROT);
        }
};

#endif