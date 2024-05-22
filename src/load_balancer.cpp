#include "load_balancer.h"

LoadBalancer::~LoadBalancer(){
  for(int i = 0; i < TASK_NO; i++){
    delete tasks[i];
  }
  delete tasks;
}

TaskQueue** LoadBalancer::initializeQueues(int queueNo){
  int tasksPerQueue = TASK_NO / queueNo;
  int remainder = TASK_NO % queueNo;
  
  TaskQueue** queue = new TaskQueue*[queueNo];
  
  for(int i = 0; i < queueNo; i++){
    if(remainder > 0){
      queue[i] = new TaskQueue(tasksPerQueue + 1);
      remainder--;
    }else{
      queue[i] = new TaskQueue(tasksPerQueue);
    }
  }
  return queue;
}

TaskQueue** LoadBalancer::balanceQueues(int queueNo){
  TaskQueue** queues = initializeQueues(queueNo);

  int queueIdx =0 ;
  for(int i = 0; i < TASK_NO; i++){
    queueIdx = TASK_NO % queueNo;
    queues[queueIdx]->enqueue(tasks[i]);
  }

  return queues;
}