#ifndef _HYPERVISOR_H
#define _HYPERVISOR_H

#include "task_queue.h"
#include "thread.h"

Thread** threads;
uint8_t threadNo;
uint8_t currThread;
    
Thread* nextThread();

uint16_t saveCtx();
void restoreCtx(uint16_t sp);
    
void loadStackPointer(uint16_t sp);
uint16_t saveStackPointer();

void switchThread();


#endif //_HYPERVISOR_H_