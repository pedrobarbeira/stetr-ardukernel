#include <task_queue.h>

TaskQueue* idleQueue = nullptr;
TaskQueue* oldReadyQueue = nullptr;
TaskQueue* readyQueue = nullptr;
uint8_t* pxCurrentTCB = nullptr;
int tickCount;

void vPortYieldFromTick() __attribute__ (( naked ));
void incrementTick(); //__attribute__ (( naked ));
void checkIfReady();// __attribute__ (( naked ));
void switchTask();// __attribute__ (( naked ));
void setup(void);
void loop(void);

void print1();
void print2();

#define SAVE_CONTEXT()                      \
    asm volatile (                          \
        "push r0                      \n\t" \
        "in r0, __SREG__              \n\t" \
        "cli                          \n\t" \
        "push r0                      \n\t" \
        "push r1                      \n\t" \
        "clr  r1                      \n\t" \
        "push r2                      \n\t" \
        "push r3                      \n\t" \
        "push r4                      \n\t" \
        "push r5                      \n\t" \
        "push r6                      \n\t" \
        "push r7                      \n\t" \
        "push r8                      \n\t" \
        "push r9                      \n\t" \
        "push r10                     \n\t" \
        "push r11                     \n\t" \
        "push r12                     \n\t" \
        "push r13                     \n\t" \
        "push r14                     \n\t" \
        "push r15                     \n\t" \
        "push r16                     \n\t" \
        "push r17                     \n\t" \
        "push r18                     \n\t" \
        "push r19                     \n\t" \
        "push r20                     \n\t" \
        "push r21                     \n\t" \
        "push r22                     \n\t" \
        "push r23                     \n\t" \
        "push r24                     \n\t" \
        "push r25                     \n\t" \
        "push r26                     \n\t" \
        "push r27                     \n\t" \
        "push r28                     \n\t" \
        "push r29                     \n\t" \
        "push r30                     \n\t" \
        "push r31                     \n\t" \
        "lds r26, %0                  \n\t" \
        "lds r27, %0 + 1              \n\t" \
        "in r0, __SP_L__              \n\t" \
        "st x+, r0                    \n\t" \
        "in r0, __SP_H__              \n\t" \
        "st x+, r0                    \n\t" \
        :                                   \
        : "m" (pxCurrentTCB) \
    );

#define RESTORE_CONTEXT()                   \
    asm volatile (                          \
        "lds r26, %0                  \n\t" \
        "lds r27, %0 + 1              \n\t" \
        "ld  r28, x+                  \n\t" \
        "out __SP_L__, r28            \n\t" \
        "ld  r29, x+                  \n\t" \
        "out __SP_H__, r29            \n\t" \
        "pop r31                      \n\t" \
        "pop r30                      \n\t" \
        "pop r29                      \n\t" \
        "pop r28                      \n\t" \
        "pop r27                      \n\t" \
        "pop r26                      \n\t" \
        "pop r25                      \n\t" \
        "pop r24                      \n\t" \
        "pop r23                      \n\t" \
        "pop r22                      \n\t" \
        "pop r21                      \n\t" \
        "pop r20                      \n\t" \
        "pop r19                      \n\t" \
        "pop r18                      \n\t" \
        "pop r17                      \n\t" \
        "pop r16                      \n\t" \
        "pop r15                      \n\t" \
        "pop r14                      \n\t" \
        "pop r13                      \n\t" \
        "pop r12                      \n\t" \
        "pop r11                      \n\t" \
        "pop r10                      \n\t" \
        "pop r9                       \n\t" \
        "pop r8                       \n\t" \
        "pop r7                       \n\t" \
        "pop r6                       \n\t" \
        "pop r5                       \n\t" \
        "pop r4                       \n\t" \
        "pop r3                       \n\t" \
        "pop r2                       \n\t" \
        "pop r1                       \n\t" \
        "pop r0                       \n\t" \
        "out __SREG__, r0             \n\t" \
        "pop r0                       \n\t" \
        :                                   \
        : "m" (pxCurrentTCB) \
    );

Task* task1 = new Task
{
    1, 3, 2, waiting, print1
};

Task* task2 = new Task
{
    1, 4, 2, waiting, print2
};

void print1()
{
    Serial.println("Task 1");
    delay(3000);
    task1->state = waiting;
}

void print2()
{
    Serial.println("Task 2");
    delay(2000);
    task2->state = waiting;
}

void setup()
{
    Serial.begin(9600);

    while (!Serial);
    Serial.println("TEST");

    config_timer1_interrupts();

    idleQueue = new TaskQueue();
    idleQueue->enqueue(task1);
    idleQueue->enqueue(task2);

    tickCount = 0;
    pxCurrentTCB = (uint8_t*) print1;
}

void loop()
{
    if(task1->state == waiting)
    {
        delay(3000);
        task1->state = ready;
    }
    /*
    else if(task2->state == waiting)
    {
        delay(1000);
        task2->state = ready;
    }
    */
}

/**
 * @brief Construct a new ISR object to handle Timer 1 interrupts.
 * It is a naked function, because context switching may occur 
 * and we need to save and restore the context manually
 */
ISR(TIMER1_COMPA_vect, ISR_NAKED)
{

    vPortYieldFromTick();

    asm volatile ("reti");
}

/**
 * @brief Increments the kernel tick and checks if a Task was activated
 * 
 */
void incrementTick()
{
    Serial.println("Increment tick");
    
    if(tickCount++ >= INT32_MAX)
        tickCount = 0;

    Serial.println(tickCount);
    checkIfReady();
}

/**
 * @brief Switches the execution context if a task with higher priority was activated 
 * 
 */
void switchTask()
{
    Serial.println("Switch task");
    if (pxCurrentTCB == nullptr && !readyQueue->isEmpty())
    {
        Serial.println("First run");
        readyQueue->sortBy(deadline);
        Task* currentTask = readyQueue->dequeue();
        oldReadyQueue = readyQueue;
        currentTask->state = running;
        pxCurrentTCB = (uint8_t*) currentTask->routine;
    }
    else if (oldReadyQueue->peek()->id != readyQueue->peek()->id)
    {
        Serial.println("Task with higher priority activated");
        readyQueue->sortBy(deadline);
        Task* currentTask = readyQueue->dequeue();
        oldReadyQueue = readyQueue;
        currentTask->state = running;
        pxCurrentTCB = (uint8_t*) currentTask->routine;
    }
}

/**
 * @brief Checks if a Task was activated and is ready to be run.
 * Whenever a Task is ready, it is moved to the ready queue
 */
void checkIfReady()
{
    Task** tasks = idleQueue->getAllTasks();

    for(int i = 0; i < idleQueue->size(); i++)
    {
        Task* t = tasks[i];

        if(t->state == ready)
        {
            readyQueue->enqueue(t);
        }
    }
}

/**
 * @brief Runs every tick, updating the tick count value
 * and checking for new Tasks moved to a ready state 
 */
void vPortYieldFromTick()
{

    SAVE_CONTEXT();

    incrementTick();

    //switchTask();

    RESTORE_CONTEXT();

    asm volatile("ret");
}
