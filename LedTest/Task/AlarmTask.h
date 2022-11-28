#ifndef ALARMTASK
#define ALARMTASK

#include "ITask.h"
#include "WaterDetectionTask.h"
#include <ServoTimer2.h>
#include "../Potentiometer/Potentiometer.h"
#include "../Button/Button.h"

#define MINROT 750
#define MAXROT 2250

class AlarmTask: public ITask {

    private:
        ServoTimer2 servo;
        WaterDetectionTask* wdt;
        IPotentiometer* pot;
        IButton* b;
        int cont;
        int max;

    public:

        AlarmTask(int sPin, int pPin, int bPin, WaterDetectionTask* wdt) {
            this->servo.attach(sPin);
            this->pot = new Potentiometer(pPin);
            this->b = new Button(bPin);
            this->wdt = wdt;
            this->cont = 0;
        }

        void init(int period) {
            ITask::init(period);
            this->servo.write(MINROT);
            this->max = 500 / period;
        }

        void tick() {
            this->b->listen();
            if (cont == 0) {
                if (this->b->isOn()) {
                    this->servo.write(map(this->pot->getValue(), 0, 1024, MINROT, MAXROT));
                } else {
                    int wl = this->wdt->getDistance();
                    wl = (wl < WL3) ? WL3 : wl;
                    this->servo.write(map(wl, WL2, WL3, MINROT, MAXROT));
                }
            }
            this->cont = (this->cont + 1) % this->max;
        }

        void reset() {
            this->servo.write(MINROT);
        }

        int getAngle(){
            return map(this->servo.read(), MINROT, MAXROT, 0, 180);
        }
};

#endif