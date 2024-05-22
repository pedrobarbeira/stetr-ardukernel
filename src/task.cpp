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

Task** Task::buildTaskList(){
  Task** tasks = new Task*[TASK_NO];

  tasks[0] = new Task(new TaskImpl{0, 2, 10, WAITING, task_1});
  tasks[1] = new Task(new TaskImpl{1, 5, 11, WAITING, task_2});
  tasks[2] = new Task(new TaskImpl{2, 6, 12, WAITING, task_3});
  tasks[3] = new Task(new TaskImpl{3, 4, 13, WAITING, task_4});
}