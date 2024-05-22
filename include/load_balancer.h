#ifndef _LOAD_BALANCER_H
#define _LOAD_BALANCER_H

#include "task_queue.h"

class LoadBalancer{
  private:
    Task** tasks;
    
    TaskQueue** initializeQueues(int queueNo);
  public:
    explicit LoadBalancer(Task** tasks):
      tasks(tasks){};

    TaskQueue** balanceQueues(int queueNo);

    ~LoadBalancer();


};

#endif //_LOAD_BALANCER_H_