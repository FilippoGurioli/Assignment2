#ifndef CONTROLLER
#define CONTROLLER

#define PRPIN A0
#define POTPIN A1
#define LEDPIN 2
#define STRIG 3
#define SECHO 4
#define RLEDPIN 5
#define GLEDPIN 6
#define BUTTONPIN 7
#define PIRPIN 8
#define SERVOPIN 9

#include "../Scheduler.h"
#include "ITask.h"
#include "WaterDetectionTask.h"
#include "LampTask.h"
#include "LCDTask.h"
#include "ServoTask.h"
#include "../Utils/State.h"
#include "../Utils/MsgService.cpp"
#include <EnableInterrupt.h>

bool control = false;

void interruptRoutine() {
    if (control)    button = !button;
}

class Controller: public ITask {

    private:
        WaterDetectionTask* wdt;
        LampTask* lt;
        LCDTask* lcdt;
        Scheduler* scheduler;
        ServoTask* st;
        State state;
        int cont = 0;
    
    public:
        Controller(Scheduler* scheduler, int period) {
            MsgService.init();
            this->scheduler = scheduler;
            this->wdt = new WaterDetectionTask(GLEDPIN, RLEDPIN, STRIG, SECHO);
            this->lt = new LampTask(LEDPIN, PRPIN, PIRPIN);
            this->st = new ServoTask(SERVOPIN, POTPIN, BUTTONPIN, wdt);
            this->lcdt = new LCDTask(wdt, st);
            this->init(period);
            this->wdt->init(1000);
            this->lt->init(250);
            this->st->init(500);
            this->lcdt->init(750);
            this->scheduler->pushTask(this);
            this->scheduler->pushTask(wdt);
            this->scheduler->pushTask(lt);
            this->state = NORMAL;
        }


        void tick() {
            State newState = this->wdt->getState();
            if (state == NORMAL) {
                if (newState == PREALARM) {
                    this->scheduler->pushTask(this->lcdt);
                } else if (newState == ALARM) {
                    this->scheduler->popTask();
                    this->scheduler->pushTask(this->st);
                    control = true;
                    this->scheduler->pushTask(this->lcdt);
                }
            } else if (state == PREALARM) {
                if (newState == NORMAL) {
                    this->scheduler->popTask();
                } else if (newState == ALARM) {
                    this->scheduler->popTask();
                    this->scheduler->popTask();
                    this->scheduler->pushTask(this->st);
                    control = true;
                    this->scheduler->pushTask(this->lcdt);
                }
            } else {
                if (newState == NORMAL) {
                    control = false;
                    this->scheduler->popTask();
                    this->scheduler->popTask();
                    this->scheduler->pushTask(this->lt);
                } else if (newState == PREALARM) {
                    control = false;
                    this->scheduler->popTask();
                    this->scheduler->popTask();
                    this->scheduler->pushTask(this->lt);
                    this->scheduler->pushTask(this->lcdt);
                }
            }
            if (cont == 0) {

                if (newState == NORMAL)   MsgService.sendMsg("NORMAL");
                else if (newState == PREALARM)   MsgService.sendMsg("PREALARM");
                else   MsgService.sendMsg("ALARM");
                
                if (this->lt->isOn()) {
                    MsgService.sendMsg("ON");
                } else {
                    MsgService.sendMsg("OFF");
                }
                
                MsgService.sendMsg(String(this->wdt->getDistance()));
            }
            this->cont++;
            this->cont = cont % 18;

            //silvia
            //int deg = (int)MsgService.receiveMsg();
            //this->st->moveServo(deg);

            this->state = newState;
        } 

        void reset () {
            //Nothing to reset
        }
};

#endif