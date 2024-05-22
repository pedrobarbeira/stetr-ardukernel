#ifndef _LOAD_BALANCER_H
#define _LOAD_BALANCER_H

#include "task_queue.h"
#include "thread.h"

class LoadBalancer{
  private:
    Task** tasks;
    int nextThread;
    int threadNo;
    
    TaskQueue** initializeQueues(int threadNo);
    TaskQueue** buildQueues(int threadNo);
    
  public:
    explicit LoadBalancer(Task** tasks):
      tasks(tasks), nextThread(0), threadNo(1){};

    Thread** buildThreads(int threadNo);

    ~LoadBalancer();
};

#endif //_LOAD_BALANCER_H_