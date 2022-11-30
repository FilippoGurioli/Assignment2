/*
Componenti del gruppo:
Filippo Gurioli - 0000971360
Silvia Furegato - 0000977475
Tommaso Turci   - 0000971189
*/
#include "myLib/Tasks/Controller.h"
#include "myLib/Scheduler.h"

#define PERIOD 50

Scheduler scheduler;
Controller* controller;

void setup() {
  scheduler.init(PERIOD);
  controller = new Controller(&scheduler, PERIOD);
}

void loop() {
  scheduler.schedule();
}
