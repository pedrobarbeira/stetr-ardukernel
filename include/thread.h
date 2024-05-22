#ifndef _THREAD_H
#define _THREAD_H

#include "task_queue.h"
#include "scheduler.h"

class Thread{
  private:
    Scheduler* scheduler;
    int tickCount;

  public:
    explicit Thread(Scheduler* scheduler):
      scheduler(scheduler), tickCount(0){};

    inline pcb_t* activateThread(){
      return this->scheduler->getCurrentPcb();
    };

    inline void deactivateThread(pcb_t* pcb){
      this->scheduler->storeCurrentPcb(pcb);
    };

    inline void incrementTick(){
      tickCount++;
    }

    ~Thread();
};

#endif //_THREAD_H_