#ifndef TASK_H_
#define TASK_H_

enum state
{
    waiting,
    ready,
    blocked,
    running,
};

typedef struct task
{
    int id;
    float period;
    int deadline;
    enum state state;
    void (*routine)();
} Task;

#endif