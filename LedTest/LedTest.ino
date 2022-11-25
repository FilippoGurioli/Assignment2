#include "Task/Scheduler.h"
#include "Task/Controller.h"

Scheduler scheduler;
Controller* controller;

void setup() {
  Serial.begin(9600);
  scheduler.init(50);
  controller = new Controller(&scheduler);
}

void loop() {
  scheduler.schedule();
}