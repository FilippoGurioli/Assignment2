#ifndef CONTROLLER
#define CONTROLLER

#include "Scheduler.h"
#include "LampTask.h"
#include "WaterDetectionTask.h"
#include "ITask.h"
#include "State.h"
//#include "AlarmTask.h"

class Controller: public ITask {

    private:
        WaterDetectionTask* wdt;
        LampTask* lt;
        //AlarmTask* at;
        Scheduler scheduler;
        State state;
    
    public:
        Controller(WaterDetectionTask* wdt, LampTask* lt,/* AlarmTask* at,*/ Scheduler scheduler) {
            this->scheduler = scheduler;
            this->wdt = wdt;
            this->lt = lt;
            //this->at = at;
            state = this->wdt->getState();
        }

        void tick() {
            if (this->wdt->getState() == ALARM && state != ALARM) {
                scheduler.pop();
                //scheduler.addTask(alarmTask);
                Serial.println("pop");
            } else if (this->wdt->getState() != ALARM && state == ALARM) {
                //scheduler.pop();
                scheduler.addTask(this->lt);
                Serial.println("add");
            }
            state = this->wdt->getState();
        }
};

#endif