#ifndef LCDTASK
#define LCDTASK

#include "ITask.h"
#include "../Display/Display.h"
#include "State.h"
#include "AlarmTask.h"

class LCDTask: public ITask {

    private:
        IDisplay* display;
        WaterDetectionTask* wdt;
        bool first;
        AlarmTask* at;

    public:
        LCDTask(WaterDetectionTask* wdt, AlarmTask* at) {
            this->wdt = wdt;
            this->display = new Display();
            this->first = true;
            this->at = at;
        }

        void tick() {
            State state = this->wdt->getState();
            int wl = this->wdt->getDistance();
            int degrees = this->at->getAngle();
            if (first) {
                if (state == PREALARM) {
                    this->display->printTitle(F("PREALARM"));
                    this->display->printStatString(F("Water level: "));
                } else if (state == ALARM) {
                    this->display->printTitle(F("!!ALARM!!"));
                    this->display->printStatString(F("Water level: "));
                    this->display->printStatString(F("Valve open:  "));
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