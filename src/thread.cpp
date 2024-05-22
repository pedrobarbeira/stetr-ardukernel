#include "thread.h"

Thread::~Thread(){
  delete taskQueue;

}