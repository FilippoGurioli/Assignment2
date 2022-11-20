#define LEDPIN 2
#define PRPIN A0
#define PIRPIN 11
#define STRIG 3
#define SECHO 4
#define GLEDPIN 12
#define RLEDPIN 13

#include "Task/NormalBhvTask.h"
#include "Task/Scheduler.h"
#include "Task/WaterDetectionTask.h"

Scheduler scheduler;

void setup() {
  Serial.begin(9600);
  scheduler.init(50);
  ITask* nbt = new NormalBhvTask(LEDPIN, PRPIN, PIRPIN);
  ITask* wdt = new WaterDetectionTask(GLEDPIN, RLEDPIN, STRIG, SECHO);
  nbt->init(250);
  wdt->init(1000);
  scheduler.addTask(nbt);
  scheduler.addTask(wdt);
}

void loop() {
  scheduler.schedule();
}