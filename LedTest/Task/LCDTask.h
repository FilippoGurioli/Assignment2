#ifndef LCDTASK
#define LCDTASK

#include "ITask.h"
#include "../Display/Display.h"
#include "State.h"

class LCDTask: public ITask {

    private:
        IDisplay* display;
        WaterDetectionTask* wdt;
        bool first;

    public:
        LCDTask(WaterDetectionTask* wdt/*, servotasdk*/) {
            this->wdt = wdt;
            this->display = new Display();
            this->first = true;
        }

        void tick() {
            State state = this->wdt->getState();
            int wl = this->wdt->getDistance();
            //int degrees = this->servoTask->getDegrees();
            if (first) {
                if (state == PREALARM) {
                    this->display->printTitle("PREALARM");
                    this->display->printStatString("Water level: ");
                } else if (state == ALARM) {
                    this->display->printTitle("!!ALARM!!");
                    this->display->printStatString("Water level: ");
                    this->display->printStatString("Valve open:  ");
                }
                first = false;
            }
            switch (state) {
                case ALARM:
                    this->display->updateStatValue(2, 23);
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