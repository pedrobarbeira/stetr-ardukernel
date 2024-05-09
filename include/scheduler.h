#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <task_queue.h>
#include <Arduino.h>

class Scheduler {

    private:
        TaskQueue* idleQueue;
        TaskQueue* oldQueue;
        TaskQueue* readyQueue;

        int tick;

    public:
        Scheduler();
        ~Scheduler();

        void schedule();
        void setIdleQueue(TaskQueue* q);
        void dispatch();
        void incrementTick();
};

#endif
