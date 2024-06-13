#include "hypervisor.h"

uint16_t saveStackPointer(){
  uint8_t lo = 0, hi = 0;
  asm volatile(
    "in r28, __SP_L__\n\t"
    "in r29, __SP_H__\n\t"
    "mov %0, r28      \n\t"   
    "mov %1, r29"
    : "=r" (lo), "=r" (hi)
  );

  uint16_t sp = 0;
  sp = hi << 8;
  sp |= lo;
  
  return sp;
}

void loadStackPointer(uint16_t sp){
  uint8_t lo = sp;
  sp = sp >> 8;
  uint8_t hi = sp;

  asm volatile(
    "mov r28, %0\n\t"
    "mov r29, %1\n\t"
    "out __SP_L__, r28\n\t"
    "out __SP_H__, r29"
    :
    : "r" (lo), "r" (hi)
  );
}