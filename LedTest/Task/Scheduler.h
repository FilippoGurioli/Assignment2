#ifndef SCHEDULER
#define SCHEDULER

#include "ITask.h"
#include "Utils/Timer.h"

#define MAX_TASKS 10

class Scheduler {
    private:
        int basePeriod;
        int nTasks;
        ITask* taskList[MAX_TASKS];
        Timer timer;

    public:
        void init(int basePeriod) {
            this->basePeriod = basePeriod;
            timer.setupPeriod(basePeriod);
            nTasks = 0;
        }

        bool addTask(ITask* task) {
            if (nTasks < MAX_TASKS - 1) {
                taskList[nTasks] = task;
                nTasks++;
                return true;
            } else {
                return false;
            }
        }

        void schedule() {
            timer.waitForNextTick();
            for (int i = 0; i < nTasks; i++) {
                if (taskList[i]->updateAndCheckTime(basePeriod)) {
                    taskList[i]->tick();
                }
            }
        }

        bool pop() {
            if (nTasks > 0) {
                nTasks--;
                taskList[nTasks]->reset(); //Anche se idealmente resetterebbe la task, non l'oggetto usato dalla task
                taskList[nTasks] = NULL;
                return true;
            } else {
                return false;
            }
        }

        int getTasks() {
            return nTasks;
        }
};

#endif