#include "Task/Scheduler.h"
#include "Task/Controller.h"

Scheduler scheduler;
Controller* controller;

void setup() {
  scheduler.init(50);
  controller = new Controller(&scheduler);
}

void loop() {
  scheduler.schedule();
}
