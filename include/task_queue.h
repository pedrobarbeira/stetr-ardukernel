#ifndef TASK_QUEUE_H_
#define TASK_QUEUE_H_

#include <utils.h>
#include <task.h>
#include <stdlib.h>

#define SIZE 100

class TaskQueue {
    private:
        int head;
        int tail;
        int capacity;
        int count;

        Task** tasks;
        static int sort_deadline_asc(const void* t1, const void* t2);
        static int sort_period_asc(const void* t1, const void* t2);

    public:
        TaskQueue(int size = SIZE);
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
