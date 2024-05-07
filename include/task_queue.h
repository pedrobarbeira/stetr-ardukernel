#ifndef TASK_QUEUE_H_
#define TASK_QUEUE_H_

#include <task.h>
#include <Arduino.h>

#define SIZE 100

class TaskQueue {
    private:
        int head;
        int tail;
        int capacity;
        int count;

        Task* tasks;
        void increase_size();
        static int sort_deadline_asc(const void* t1, const void* t2);

    public:
        TaskQueue(int size = SIZE);
        ~TaskQueue();

        bool isEmpty();
        bool isFull();
        void enqueue(Task* t);
        Task dequeue();
        int size();
        void sort();
};

#endif
