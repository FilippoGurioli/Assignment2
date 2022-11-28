#ifndef CONTROLLER
#define CONTROLLER

#define PRPIN A0
#define POTPIN A1
#define LEDPIN 2
#define STRIG 3
#define SECHO 4
#define BUTTONPIN 5
#define GLEDPIN 6
#define RLEDPIN 7
#define PIRPIN 8
#define SERVOPIN 9

#include "Scheduler.h"
#include "LampTask.h"
#include "WaterDetectionTask.h"
//#include "LCDTask.h"
#include "ITask.h"
#include "State.h"
#include "AlarmTask.h"

class Controller: public ITask {

    private:
        WaterDetectionTask* wdt;
        LampTask* lt;
        //LCDTask* lcdt;
        Scheduler* scheduler;
        AlarmTask* at;
        State state;
    
    public:
        Controller(Scheduler* scheduler) {
            this->scheduler = scheduler;
            this->wdt = new WaterDetectionTask(GLEDPIN, RLEDPIN, STRIG, SECHO);
            this->lt = new LampTask(LEDPIN, PRPIN, PIRPIN);
            this->at = new AlarmTask(SERVOPIN, POTPIN, BUTTONPIN, wdt);
            //this->lcdt = new LCDTask(wdt, at);
            this->init(50);
            this->wdt->init(1000);
            this->lt->init(250);
            this->at->init(100);
            //this->lcdt->init(750);
            this->scheduler->addTask(this);
            this->scheduler->addTask(wdt);
            this->scheduler->addTask(lt);
            this->state = NORMAL;
        }

        void tick() {
            State newState = this->wdt->getState();
            if (state == NORMAL) {
                if (newState == PREALARM) {
                    //this->scheduler->addTask(this->lcdt);
                } else if (newState == ALARM) {
                    this->scheduler->pop();
                    this->scheduler->addTask(this->at);
                    //this->scheduler->addTask(this->lcdt);
                }
            } else if (state == PREALARM) {
                if (newState == NORMAL) {
                    //this->scheduler->pop();
                } else if (newState == ALARM) {
                    //this->scheduler->pop();
                    this->scheduler->pop();
                    this->scheduler->addTask(this->at);
                    //this->scheduler->addTask(this->lcdt);
                }
            } else {
                if (newState == NORMAL) {
                    this->scheduler->pop();
                    //this->scheduler->pop();
                    this->scheduler->addTask(this->lt);
                } else if (newState == PREALARM) {
                    this->scheduler->pop();
                    //this->scheduler->pop();
                    this->scheduler->addTask(this->lt);
                    //this->scheduler->addTask(this->lcdt);
                }
            }
            state = newState;
        } 

        void reset () {
            //Nothing to reset
        }
};

#endif