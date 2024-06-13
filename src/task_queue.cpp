#include <task_queue.h>

// Function to initialize the queue
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Function to check if the queue is full
int isFull(Queue *q) {
    if(q->rear == MAX_SIZE - 1)
        return 1;
    else
        return 0;
}

// Function to check if the queue is empty
int isEmpty(Queue *q) {
    if(q->front == -1 || q->front > q->rear)
        return 1;
    else
        return 0;
}

// Function to add an element to the queue
void enqueue(Queue *q, Task* task) {
    if(isFull(q)) {
        return;
    } else {
        if(q->front == -1)
            q->front = 0;

        q->rear++;
        q->items[q->rear] = task;
    }
}

// Function to remove an element from the queue
Task* dequeue(Queue *q) {
    Task* task;
    if(isEmpty(q)) {
        return nullptr;
    } else {
        task = q->items[q->front];
        q->front++;

        if(q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return task;
}

/**
 * @brief Sorts the queue according to a criteria
 * 
 * @param options The criteria used to sort the queue
 */
void sortBy(Queue *q, enum sort_options options)
{
    switch (options)
    {
        case deadline:
            qsort((void*) (q->items), q->rear, sizeof(Task), sort_deadline_asc);
            break;
        
        case period:
            qsort((void*) (q->items), q->rear, sizeof(Task), sort_period_asc);
            break;

        default:
            break;
    }
}
