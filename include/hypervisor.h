#ifndef _HYPERVISOR_H
#define _HYPERVISOR_H

#include "load_balancer.h"
#include "task_queue.h"

class Hypervisor{
  private:
    LoadBalancer* loadBalancer;
    TaskQueue** queues;
    int queueNo;
    int currQueue;

  public:
    explicit Hypervisor(LoadBalancer* loadBalancer, int queueNo):
      loadBalancer(loadBalancer), queueNo(queueNo), currQueue(0){
        queues = loadBalancer->balanceQueues(this->queueNo);
      };
};

#endif _HYPERVISOR_H_