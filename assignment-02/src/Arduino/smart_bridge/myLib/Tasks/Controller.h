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
#include "ServoTask.h"
#include "LCDTask.h"
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
        State oldState;
        int cont = 0;
    
    public:
        Controller(Scheduler* scheduler, int period) {
            enableInterrupt(BUTTONPIN, interruptRoutine, RISING);
            MsgService.init();
            this->scheduler = scheduler;
            this->wdt = new WaterDetectionTask(GLEDPIN, RLEDPIN, STRIG, SECHO);
            this->lt = new LampTask(LEDPIN, PRPIN, PIRPIN);
            this->st = new ServoTask(SERVOPIN, POTPIN, BUTTONPIN);
            this->lcdt = new LCDTask();
            this->init(period);
            this->wdt->init(1000);
            this->lt->init(250);
            this->st->init(500);
            this->lcdt->init(750);
            this->scheduler->pushTask(this);
            this->scheduler->pushTask(wdt);
            this->scheduler->pushTask(lt);
            this->oldState = NORMAL;
        }

        void tick() {
            if (oldState == NORMAL) {
                if (state == PREALARM) {
                    this->scheduler->pushTask(this->lcdt);
                } else if (state == ALARM) {
                    this->scheduler->popTask();
                    this->scheduler->pushTask(this->st);
                    control = true;
                    this->scheduler->pushTask(this->lcdt);
                }
            } else if (oldState == PREALARM) {
                if (state == NORMAL) {
                    this->scheduler->popTask();
                } else if (state == ALARM) {
                    this->scheduler->popTask();
                    this->scheduler->popTask();
                    this->scheduler->pushTask(this->st);
                    control = true;
                    this->scheduler->pushTask(this->lcdt);
                }
            } else {
                if (state == NORMAL) {
                    control = false;
                    this->scheduler->popTask();
                    this->scheduler->popTask();
                    this->scheduler->pushTask(this->lt);
                } else if (state == PREALARM) {
                    control = false;
                    this->scheduler->popTask();
                    this->scheduler->popTask();
                    this->scheduler->pushTask(this->lt);
                    this->scheduler->pushTask(this->lcdt);
                }
            }
            if (cont == 0) {
                if (state == NORMAL)   MsgService.sendMsg("NORMAL");
                else if (state == PREALARM)   MsgService.sendMsg("PREALARM");
                else   MsgService.sendMsg("ALARM");
                
                if (ledOn) {
                    MsgService.sendMsg("ON");
                } else {
                    MsgService.sendMsg("OFF");
                }
                
                MsgService.sendMsg(String(wl));
            }
            this->cont++;
            this->cont = cont % 18;
            this->oldState = state;
        } 

        void reset () {
            //Nothing to reset
        }
		
};

#endif