#include <scheduler.h>

Scheduler::Scheduler()
{
    idleQueue = nullptr;
    readyQueue = nullptr;
    oldQueue = nullptr;

    tick = 0;
}

Scheduler::~Scheduler()
{
    delete idleQueue;
    delete readyQueue;
    delete oldQueue;
}

void Scheduler::schedule()
{   
    int size = readyQueue->size();

    oldQueue = readyQueue;
    readyQueue->sortBy(deadline);

    for (int i = 0; i < size; i++)
    {
        Task t = readyQueue->peek();
        Serial.println(t.deadline);
    }
}

void Scheduler::setIdleQueue(TaskQueue* q)
{
    idleQueue = q;
}

void Scheduler::dispatch()
{
    if (oldQueue->peek().id != readyQueue->peek().id)
        return;

    Task t = readyQueue->dequeue();

    t.routine();
}

void Scheduler::incrementTick()
{
    tick++;
}
