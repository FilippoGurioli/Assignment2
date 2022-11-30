/*
Componenti del gruppo:
Filippo Gurioli - 0000971360
Silvia Furegato - 0000977475
Tommaso Turci   - 0000971189

Periodi (ms)
Scheduler       300
Controller      300
WDT         900/600/300
LT              600
LCDT            900
ST              900

Cose da fare (in ordine di importanza secondo me):
- riguardare tutti i define (gli include li ho già guardati) per i periodi e i WL, lt.TH, lt.T1, MINROT e MAXROT
- fare video
- riguardare tutti i periodi con quelli che ho suggerito sopra (biaginus)
- gestire le librerie esterne di java (lib) e arduino (enableInterrupt e liquidCrystal)
- gestire il servo tramite java
- creare il protocollo di comunicazione della seriale (con tanto di passaggio del periodo, WL1, WL2, WL3)
- vedere se c'è un modo per fare i cpp
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
