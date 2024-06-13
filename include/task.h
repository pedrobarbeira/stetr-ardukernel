#ifndef TASK_H_
#define TASK_H_

#include "Arduino.h"

#define TASK_NO 100
#define STACK_SIZE 128

typedef void(*routine_t)(void);

enum State{
    WAITING,
    READY,
    BLOCKED,
    RUNNING,
};

typedef struct tcb_t{
    float period;
    int deadline;
    enum State state;
}tcb_t;

typedef struct Task {
    uint16_t stackptr;
    uint8_t* stackbase;
    tcb_t* tcb;

    ~Task(){
        delete stackbase;
        delete tcb;
    }
} Task;

Task* buildTask(uint8_t* stackbase, float period, int deadline, State state, routine_t routine);
Task** buildTaskList(uint8_t** stackSpace);
int sort_deadline_asc(const void* t1, const void* t2);
int sort_period_asc(const void* t1, const void* t2);

#endif