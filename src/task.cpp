#include "task.h"

void task_1(){  
  Serial.print("Executing task 1\n");
}

void task_2(){  
  Serial.print("Executing task 2\n");
}

void task_3(){  
  Serial.print("Executing task 3\n");
}

void task_4(){  
  Serial.print("Executing task 4\n");
}

Task::~Task(){
  delete task;
}

TaskImpl* Task::getTask(){
  return this->task;
}

Task* Task::buildTaskList(){
  Task[] tasks = new Task[TASK_NO];
}