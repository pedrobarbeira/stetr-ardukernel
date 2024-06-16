#ifndef _THREAD_H
#define _THREAD_H

#include <scheduler.h>

class Thread{
  private:
    Scheduler* scheduler;
    uint16_t stackPointer;
    int tickCount;

  public:
    explicit Thread(Scheduler* scheduler):
      scheduler(scheduler), tickCount(0){};

    inline uint16_t activateThread(){
      return this->stackPointer;
    };

    inline void deactivateThread(uint16_t sp){
      this->stackPointer = sp;
    };

    inline void incrementTick(){
      tickCount++;
    }

    ~Thread();
};

#endif //_THREAD_H_