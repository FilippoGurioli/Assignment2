#ifndef LCDTASK
#define LCDTASK

#include "ITask.h"
#include "../Display/Display.h"
#include "State.h"
#include <string.h>

class LCDTask: public ITask {

    private:
        IDisplay* display;
        WaterDetectionTask* wdt;

    public:
        LCDTask(WaterDetectionTask* wdt/*, servotasdk*/) {
            this->wdt = wdt;
            display = new Display();
        }

        void tick() {
            int wl = this->wdt->getDistance();
            //int degrees = this->servoTask->getDegrees();
            switch (this->wdt->getState()) {
                case PREALARM:
                    this->display->clear();
                    this->display->printLine("PREALARM", true);
                    this->display->printLine("Water level:", false);
                    this->display->printLine(String(wl), false);
                break;
                case ALARM:
                    this->display->clear();
                    this->display->printLine("ALARM", true);
                    this->display->printLine("Degrees:          Water level:", false);
                    String string = String(0) + "    " + String(wl);
                    this->display->printLine(string, false);
                break;
            }
        }

        void reset() {
            this->display->clear();
        }

};

#endif