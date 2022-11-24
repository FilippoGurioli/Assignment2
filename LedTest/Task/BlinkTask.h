#ifndef BLINKTASK
#define BLINKTASK

#include "ITask.h"
#include "../Led/Led.h"

class BlinkTask: public ITask {

    private:
        int ledPin;
        ILed* led;
    
    public:
        BlinkTask(int ledPin) {
            this->ledPin = ledPin;
        }

        void init(int period) {
            ITask::init(period);
            led = new Led(this->ledPin);
        }

        void tick() {
            this->led->switchOn();
            delay(1000);
            this->led->switchOff();
        }
};

#endif