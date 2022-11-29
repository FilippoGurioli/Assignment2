/*
Componenti del gruppo:
Filippo Gurioli - 0000971360
Silvia Furegato - 0000977475
Tommaso Turci   - 0000971189
*/
#include "myLib/Tasks/Controller.h"
#include "myLib/Scheduler.h"

Scheduler scheduler;
Controller* controller;

void setup() {
  scheduler.init(50);
  controller = new Controller(&scheduler);
}

void loop() {
  scheduler.schedule();
}
