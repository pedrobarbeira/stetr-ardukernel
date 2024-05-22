#include "hypervisor.h"

Hypervisor::~Hypervisor(){
  for(int i = 0; i < this->threadNo; i++){
    delete threads[i];
  }
  delete threads;
  delete loadBalancer;
}

pcb_t* Hypervisor::getExecutionPcb(){
  //asm code to get current execution context goes here
  return nullptr;
}

void Hypervisor::setExecutionPcb(pcb_t* pcb){
  //asm code to set current execution context goes here
}

Thread* Hypervisor::nextThread(){
  currThread = (currThread + 1) % threadNo;
  return threads[currThread];
}

void Hypervisor::switchThread(){
  Thread* thread = threads[currThread];

  pcb_t* currPcb = this->getExecutionPcb();
  thread->deactivateThread(currPcb);

  thread = nextThread();
  currPcb = thread->activateThread();
  this->setExecutionPcb(currPcb);
}