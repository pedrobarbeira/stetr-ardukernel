#ifndef TASK_H_
#define TASK_H_

#include "Arduino.h"

#define TASK_NO 100

typedef void(*routine_t)(void);
typedef struct Task Task;

typedef struct TaskImpl {
    int id;
    float period;
    int deadline;
    routine_t routine;
} TaskImpl;

class Task{
    private:
        TaskImpl* task;

        explicit Task(TaskImpl* task):
            task(task){};

    public:
        Task(){};
        ~Task();

        static Task* buildTaskList();

        TaskImpl* getTask();
};

#endif