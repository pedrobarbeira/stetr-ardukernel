#include "hypervisor.h"

Hypervisor::~Hypervisor(){
  for(int i = 0; i < this->threadNo; i++){
    delete queues[i];
  }
  delete queues;
  delete loadBalancer;
}