#ifndef LCDTASK
#define LCDTASK

#include "ITask.h"
#include "WaterDetectionTask.h"
#include "../Peripherals/Display/Display.h"

class LCDTask: public ITask {

    private:
        IDisplay* display;
        bool first;

    public:
        LCDTask() {
            this->display = new Display();
            this->first = true;
        }

        void tick() {
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
                    this->display->updateStatValue(2, servoAngle -1);
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