#ifndef LAMPTASK
#define LAMPTASK

#define TH 300
#define T1 4000

#include "ITask.h"
#include "../Led/Led.h"
#include "../Photoresistor/Photoresistor.h"
#include "../Pir/Pir.h"

class LampTask: public ITask {
    
    private:
        int ledPin;
        int prPin;
        int pirPin;
        ILed* led;
        IPir* pir;
        IPhotoresistor* pr;
        /*
        I create a counter that count how many times
        "tick" is called to create the T1 delay of the lamp.
        */
        int cont;
    
    public:
        LampTask(int ledPin, int prPin, int pirPin) {
            this->ledPin = ledPin;
            this->prPin = prPin;
            this->pirPin = pirPin;
            this->cont = 0;
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
                    this->cont = 0;
                } else if (led->isOn() && !presence) {
                    if (cont * this->myPeriod < T1) {
                        cont++;
                    } else {
                        led->switchOff();
                        this->cont = 0;
                    }
                }
            }
        }

        void reset() {
            this->led->switchOff();
        }
};

#endif