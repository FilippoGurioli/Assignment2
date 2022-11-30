#ifndef WATERDETECTIONTASK
#define WATERDETECTIONTASK

#include "ITask.h"
#include "../Peripherals/Sonar/Sonar.h"
#include "../Peripherals/Led/Led.h"
#include "../Utils/State.h"

#define PE_N 1000
#define PE_P 500
#define PE_A 250

#define WL1 50
#define WL2 25
#define WL3 10

State state;
int wl = 0;

class WaterDetectionTask: public ITask {
    
    private:
        int greenLedPin;
        int redLedPin;
        int echoPin;
        int trigPin;
        ISonar* sonar;
        ILed* redLed;
        ILed* greenLed;

        void switchPeriod(int newPeriod) {
            this->myPeriod = newPeriod;
        }

    public:
        WaterDetectionTask(int greenLedPin, int redLedPin, int trigPin, int echoPin) {
            this->greenLedPin = greenLedPin;
            this->redLedPin = redLedPin;
            this->trigPin = trigPin;
            this->echoPin = echoPin;
            state = NORMAL;
        }

        void init(int period) {
            ITask::init(period);
            redLed = new Led(redLedPin);
            greenLed = new Led(greenLedPin);
            sonar = new Sonar(trigPin, echoPin);
            this->greenLed->switchOn();
        }

        void tick() {
            wl = this->sonar->getDistance();
            if (wl > WL1 && state != NORMAL) { //->NORMAL
                state = NORMAL;
                greenLed->switchOn();
                redLed->switchOff();
                this->switchPeriod(PE_N);
            } else if (wl <= WL1 && wl > WL2 && state != PREALARM) { //->PREALARM
                state = PREALARM;
                this->switchPeriod(PE_P);
                greenLed->switchOn();
            } else if (wl <= WL2 && state != ALARM) { //->ALARM
                state = ALARM;
                redLed->switchOn();
                greenLed->switchOff();
                this->switchPeriod(PE_A);
            } else if (wl <= WL1 && wl > WL2) {
                if (redLed->isOn()) {
                    redLed->switchOff();
                } else {
                    redLed->switchOn();
                }
            }
        }

        void reset () {
            //Nothing to reset
        }

};

#endif