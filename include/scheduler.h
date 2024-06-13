#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <task_queue.h>

class Scheduler{
  private:
    TaskQueue* taskQueue;
    Task* currTask;
    //add other fields
  public:
    explicit Scheduler(TaskQueue* taskQueue):
      taskQueue(taskQueue){};
};

/*
extern int tickCount;

static TaskQueue* idleQueue;
extern TaskQueue* oldReadyQueue;
extern TaskQueue* readyQueue;

void incrementTick() __attribute__ (( naked ));
void setCurrentTask(Task* task);
void setIdleQueue(TaskQueue* q);
void setReadyQueue(TaskQueue* q);
void checkIfReady() __attribute__ (( naked ));
void switchTask() __attribute__ (( naked ));

*/
#endif