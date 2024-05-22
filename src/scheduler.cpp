/*
#include <scheduler.h>

TaskQueue* oldReadyQueue = nullptr;
TaskQueue* readyQueue = nullptr;
uint8_t* pxCurrentTCB = nullptr;
int tickCount = 0;

void incrementTick()
{
    Serial.println("Increment tick");
    Serial.println(tickCount);
    
    if(tickCount++ >= INT32_MAX)
        tickCount = 0;

    tickCount++;
    

    checkIfReady();

    asm volatile ("ret");
}

void switchTask()
{
    Serial.println("Switch task");
    if (pxCurrentTCB == nullptr && !readyQueue->isEmpty())
    {
        Serial.println("First run");
        readyQueue->sortBy(deadline);
        Task* currentTask = readyQueue->dequeue();
        oldReadyQueue = readyQueue;
        pxCurrentTCB = (uint8_t*) currentTask->routine;
    }
    else if (oldReadyQueue->peek().id != readyQueue->peek().id)
    {
        Serial.println("Task with higher priority activated");
        readyQueue->sortBy(deadline);
        Task* currentTask = readyQueue->dequeue();
        oldReadyQueue = readyQueue;
        pxCurrentTCB = (uint8_t*) currentTask->routine;
    }
}

void setCurrentTask(Task* task)
{
    pxCurrentTCB = (uint8_t*) task->routine;
}

void checkIfReady()
{
    Task* tasks = idleQueue->getAllTasks();

    for(int i = 0; i < idleQueue->size(); i++)
    {
        Task t = tasks[i];

        if(t.state == ready)
        {
            readyQueue->enqueue(&t);
        }
    }

    asm volatile ("ret");
}

void setIdleQueue(TaskQueue* q)
{
    idleQueue = q;
}

void setReadyQueue(TaskQueue* q)
{
    readyQueue = q;
}
*/