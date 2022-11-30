#ifndef LAMPTASK
#define LAMPTASK

#define TH 300
#define T1 4000

#include "ITask.h"
#include "../Peripherals/Led/Led.h"
#include "../Peripherals/Photoresistor/Photoresistor.h"
#include "../Peripherals/Pir/Pir.h"

bool ledOn = false;

class LampTask: public ITask {
    
    private:
        int ledPin;
        int prPin;
        int pirPin;
        ILed* led;
        IPir* pir;
        IPhotoresistor* pr;
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
                ledOn = false;
            } else if (light <= TH) {
                if (!led->isOn() && presence) {
                    led->switchOn();
                    ledOn = true;
                    this->cont = 0;
                } else if (led->isOn() && !presence) {
                    if (cont * this->myPeriod < T1) {
                        cont++;
                    } else {
                        led->switchOff();
                        ledOn = false;
                        this->cont = 0;
                    }
                }
            }
        }

        void reset() {
            this->led->switchOff();
            ledOn = false;
        }
};

#endif