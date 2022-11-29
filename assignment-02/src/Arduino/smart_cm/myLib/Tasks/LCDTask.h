#ifndef LCDTASK
#define LCDTASK

#include "ITask.h"
#include "../Peripherals/Display/Display.h"
#include "../Utils/State.h"
#include "ServoTask.h"

class LCDTask: public ITask {

    private:
        IDisplay* display;
        WaterDetectionTask* wdt;
        bool first;
        ServoTask* st;

    public:
        LCDTask(WaterDetectionTask* wdt, ServoTask* st) {
            this->wdt = wdt;
            this->display = new Display();
            this->first = true;
            this->st = st;
        }

        void tick() {
            State state = this->wdt->getState();
            int wl = this->wdt->getDistance();
            int degrees = this->st->getAngle();
            if (first) {
                if (state == PREALARM) {
                    this->display->printTitle("PREALARM!");
                    this->display->printStatString("WL:");
                } else if (state == ALARM) {
                    this->display->printTitle("!!ALARM!!");
                    this->display->printStatString("WL:");
                    this->display->printStatString("Valve:");
                }
                first = false;
            }
            switch (state) {
                case ALARM:
                    this->display->updateStatValue(2, degrees);
                case PREALARM:
                    this->display->updateStatValue(1, wl);
                    break;
                
            }
        }

        void reset() {
            this->display->clear();
            this->first = true;
        }

};

#endif