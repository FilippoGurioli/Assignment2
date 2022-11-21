#define LEDPIN 2
#define PRPIN A0
#define PIRPIN 11
#define STRIG 3
#define SECHO 4
#define GLEDPIN 12
#define RLEDPIN 13

#include "Task/Scheduler.h"
#include "Task/Controller.h"
#include "Task/LampTask.h"
#include "Task/WaterDetectionTask.h"
//#include "Task/AlarmTask.h"

Scheduler scheduler;
Controller* controller;
WaterDetectionTask* wdt;
LampTask* lt;
//AlarmTask* al;

void setup() {
  Serial.begin(9600);
  wdt = new WaterDetectionTask(GLEDPIN, RLEDPIN, STRIG, SECHO);
  lt = new LampTask(LEDPIN, PRPIN, PIRPIN);
  controller = new Controller(wdt, lt,/* at,*/ scheduler);
  //at = new AlarmTask(...);
  scheduler.init(50);
  wdt->init(1000);
  lt->init(250);
  controller->init(250);

  scheduler.addTask(controller);
  scheduler.addTask(wdt);
  scheduler.addTask(lt);
}

void loop() {
  scheduler.schedule();
}