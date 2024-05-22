
#include <scheduler.h>
#include <task_queue.h>
#include <utils.h>

TaskQueue* idleQueue;
Scheduler* scheduler;

void task_1(){
  Serial.print("Executing task 1\n");
}

void task_2(){
  Serial.print("Executing task 2\n");
}

void setup()
{
  Serial.begin(9600);

  config_timer1_interrupts();

  scheduler = new Scheduler();

  idleQueue = new TaskQueue();
  idleQueue->enqueue(new Task{1, 1, 4, task_1});
  idleQueue->enqueue(new Task{2, 2, 3, task_2});

  scheduler->setIdleQueue(idleQueue);
}

void loop()
{

}

ISR(TIMER1_COMPA_vect)
{
  scheduler->schedule();
}
