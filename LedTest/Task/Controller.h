#ifndef CONTROLLER
#define CONTROLLER

#define PRPIN A0
#define LEDPIN 2
#define STRIG 3
#define SECHO 4
#define GLEDPIN 6
#define RLEDPIN 7
#define PIRPIN 11

#include "Scheduler.h"
#include "LampTask.h"
#include "WaterDetectionTask.h"
#include "LCDTask.h"
#include "ITask.h"
#include "State.h"
//#include "AlarmTask.h"

class Controller: public ITask {

    private:
        WaterDetectionTask* wdt;
        LampTask* lt;
        LCDTask* lcdt;
        //AlarmTask* at;
        Scheduler* scheduler;
        State state;
    
    public:
        Controller(Scheduler* scheduler) {
            this->scheduler = scheduler;
            this->wdt = new WaterDetectionTask(GLEDPIN, RLEDPIN, STRIG, SECHO);
            this->lt = new LampTask(LEDPIN, PRPIN, PIRPIN);
            this->lcdt = new LCDTask(wdt);
            this->init(50);
            wdt->init(1000);
            lt->init(250);
            lcdt->init(500);
            this->scheduler->addTask(this);
            this->scheduler->addTask(wdt);
            this->scheduler->addTask(lt);
            //this->at = at;
            this->state = NORMAL;
        }

        void tick() {
            State newState = this->wdt->getState();
            /*if (state == NORMAL) {
                if (newState == PREALARM) {
                    this->scheduler->addTask(this->lcdt);
                } else if (newState == ALARM) {
                    scheduler->pop();
                    this->scheduler->addTask(this->lt);
                    this->scheduler->addTask(this->lcdt);
                }
            } else if (state == PREALARM) {
                if (newState == NORMAL) {
                    scheduler->pop();
                } else if (newState == ALARM) {
                    scheduler->pop();
                    scheduler->pop();
                    this->scheduler->addTask(this->lt);
                    this->scheduler->addTask(this->lcdt);
                }
            } else {
                if (newState == NORMAL) {
                    scheduler->pop();
                    scheduler->pop();
                    this->scheduler->addTask(this->lt);
                } else if (newState == PREALARM) {
                    scheduler->pop();
                    scheduler->pop();
                    this->scheduler->addTask(this->lt);
                    this->scheduler->addTask(this->lcdt);
                }
            }*/
            if (state == NORMAL) {
                if (newState == PREALARM) {
                    this->scheduler->addTask(this->lcdt);
                } else if (newState == ALARM) {
                    this->scheduler->pop();
                    this->scheduler->addTask(this->lcdt);
                }
            } else if (state == PREALARM) {
                if (newState == NORMAL) {
                    this->scheduler->pop();
                } else if (newState == ALARM) {
                    this->scheduler->pop();
                    this->scheduler->pop();
                    this->scheduler->addTask(this->lcdt);
                }
            } else {
                if (newState == NORMAL) {
                    this->scheduler->pop();
                    this->scheduler->addTask(this->lt);
                } else if (newState == PREALARM) {
                    this->scheduler->pop();
                    this->scheduler->addTask(this->lt);
                    this->scheduler->addTask(this->lcdt);
                }
            }
            state = newState;
        } 

        void reset () {
            //Nothing to reset
        }
};

#endif