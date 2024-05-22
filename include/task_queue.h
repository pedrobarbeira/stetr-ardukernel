#ifndef TASK_QUEUE_H_
#define TASK_QUEUE_H_

#include <utils.h>
#include <task.h>
#include <stdlib.h>

class TaskQueue {
    private:
        int head;
        int tail;
        int capacity;
        int count;

        Task** tasks;
    public:
        TaskQueue(int size = TASK_NO);
        ~TaskQueue();

        bool isEmpty();
        bool isFull();
        void enqueue(Task* t);
        Task* dequeue();
        int size();
        void sortBy(enum sort_options);
        Task* peek();
        Task** getAllTasks();
};

#endif
