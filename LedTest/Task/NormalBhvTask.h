#ifndef NORMALBHV
#define NORMALBHV

#define TH 300
#define T1 3000

#include "ITask.h"
#include "../Led/Led.h"
#include "../Photoresistor/Photoresistor.h"
#include "../Pir/Pir.h"

class NormalBhvTask: public ITask {
    
    private:
        int ledPin;
        int prPin;
        int pirPin;
        ILed* led;
        IPir* pir;
        IPhotoresistor* pr;
        /*
        knowing the period of this task, I can create a counter that count how many times
        "tick" is called to create the T1 delay of the lamp.
        */
        int cont;
    
    public:
        NormalBhvTask(int ledPin, int prPin, int pirPin) {
            this->ledPin = ledPin;
            this->prPin = prPin;
            this->pirPin = pirPin;
            cont = 0;
        }

        void init(int period) {
            ITask::init(period);
            led = new Led(ledPin);
            pr = new Photoresistor(prPin);
            pir = new Pir(pirPin);
        }

        void tick() {
            bool presence = this->pir->getPresence();
            int light = this->pr->getLightLevel();
            if (led->isOn() && light > TH) {
                led->switchOff();
            } else if (light <= TH) {
                if (!led->isOn() && presence) {
                    led->switchOn();
                    cont = 0;
                } else if (led->isOn() && !presence) {
                    if (cont * this->myPeriod < T1) {
                        cont++;
                    } else {
                        led->switchOff();
                        cont = 0;
                    }
                }
            }
        }
};

#endif