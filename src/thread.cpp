#include "thread.h"

Thread::~Thread(){
  delete this->scheduler;
}