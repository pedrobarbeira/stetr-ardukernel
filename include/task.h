#ifndef TASK_H_
#define TASK_H_

typedef struct task {
    int id;
    float period;
    int deadline;
    void (*routine)();
} Task;

#endif