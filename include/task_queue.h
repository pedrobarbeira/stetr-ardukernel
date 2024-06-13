#ifndef TASK_QUEUE_H_
#define TASK_QUEUE_H_

#include <utils.h>
#include <task.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 

typedef struct Queue {
    Task* items[MAX_SIZE];
    int front, rear;
} Queue;

void initializeQueue(Queue *q);
int isFull(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, Task* task);
Task* dequeue(Queue *q);

#endif
