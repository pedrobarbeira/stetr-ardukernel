#ifndef _HYPERVISOR_H
#define _HYPERVISOR_H

#include "load_balancer.h"
#include "task_queue.h"

class Hypervisor{
  private:
    LoadBalancer* loadBalancer;
    Thread** threads;
    int threadNo;
    int currThread;
    Thread* nextThread();

  public:
    static void loadStackPointer(uint16_t sp);
    static uint16_t saveStackPointer();
    explicit Hypervisor(LoadBalancer* loadBalancer, int queueNo):
      loadBalancer(loadBalancer), threadNo(queueNo), currThread(0){
        threads = loadBalancer->buildThreads(this->threadNo);
      };

      void switchThread();

      ~Hypervisor();
};

#endif //_HYPERVISOR_H_