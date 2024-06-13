#include "task.h"

void task_1(){
  for(int i = 0; i < 5; i++){
    Serial.print("Executing task 1\n");
    delay(200);
  }  
}

void task_2(){  
  for(int i = 0; i < 5; i++){
    Serial.print("Executing task 2\n");
    delay(200);
  }  
}

void task_3(){  
  for(int i = 0; i < 5; i++){
    Serial.print("Executing task 3\n");
    delay(200);
  }  
}

void task_4(){  
  for(int i = 0; i < 5; i++){
    Serial.print("Executing task 4\n");
    delay(200);
  }  
}


Task* buildTask(uint8_t* stackbase, float period, int deadline, State state, routine_t routine){
  tcb_t* tcb = new tcb_t{period, deadline, state};

  uint8_t* ptr = (uint8_t*) (stackbase + STACK_SIZE - 1);
  ptr[0] = 0;
  ptr[-1] = 0;
  ptr -= 2;

  uint16_t entryAdd = (uint16_t) routine;
  ptr[0] = (uint8_t) entryAdd;
  ptr[-1] = (uint8_t) (entryAdd >> 8);
  ptr -= 2;

  for(int i = 0; i < 32; i++){
    ptr[-i] = 0;
  } 
  ptr -= 32;
  
  uint16_t stackPtr = ((uint16_t) ptr);

  return new Task{(uint16_t) stackPtr, stackbase, tcb};
}

Task** buildTaskList(uint8_t** stackSpace){
  Task** tasks = new Task*[TASK_NO];

  tasks[0] = buildTask(stackSpace[0], 2, 10, WAITING, task_1);
  tasks[1] = buildTask(stackSpace[1], 5, 11, WAITING, task_2);
  tasks[2] = buildTask(stackSpace[2], 6, 12, WAITING, task_3);
  tasks[3] = buildTask(stackSpace[3], 4, 13, WAITING, task_4);
}

/**
 * @brief Sorts a queue by ascending deadline
 * 
 * @param t1 First Task to compare
 * @param t2 Second Task to compare
 * @return int Negative if t1 is less than t2; 0 if they are equal; Positive if t1 is greater than t2
 */
int sort_deadline_asc(const void* t1, const void* t2)
{
    Task* task1 = (Task*) t1;
    Task* task2 = (Task*) t2;

    return (task1->tcb->deadline - task2->tcb->deadline);
}

/**
 * @brief Sorts a queue by ascending period
 * 
 * @param t1 First Task to compare
 * @param t2 Second Task to compare
 * @return int Negative if t1 is less than t2; 0 if they are equal; Positive if t1 is greater than t2
 */
int sort_period_asc(const void* t1, const void* t2)
{
    Task* task1 = (Task*) t1;
    Task* task2 = (Task*) t2;

    return (task1->tcb->period - task2->tcb->period);
}