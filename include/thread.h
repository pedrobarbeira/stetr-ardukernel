#ifndef _THREAD_H
#define _THREAD_H

#include "task_queue.h"
#include "scheduler.h"

typedef struct pcb_t{

}pcb_t;

class Thread{
  private:
    TaskQueue* taskQueue;
    //should have scheduler
    pcb_t* pcb;

  public:
    explicit Thread(TaskQueue* taskQueue):
      taskQueue(taskQueue){};

    void activateThread();
    void deactivateThread();

    ~Thread();
};

#endif //_THREAD_H_