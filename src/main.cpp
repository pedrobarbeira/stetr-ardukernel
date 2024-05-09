#include <Arduino.h>
#include <scheduler.h>
#include <task_queue.h>
#include <utils.h>

TaskQueue* idleQueue;
Scheduler* scheduler;

void print()
{
  Serial.println("Test task code");
}

void setup()
{
  Serial.begin(9600);

  config_timer1_interrupts();

  scheduler = new Scheduler();

  idleQueue = new TaskQueue();
  idleQueue->enqueue(new Task{1, 1, 4, print});
  idleQueue->enqueue(new Task{2, 2, 3, print});

  scheduler->setIdleQueue(idleQueue);
}

void loop()
{

}

ISR(TIMER1_COMPA_vect)
{
  scheduler->schedule();
}
