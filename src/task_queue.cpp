#include <task_queue.h>

TaskQueue::TaskQueue(int size = SIZE)
{
    capacity = SIZE;
    head = 0;
    tail = -1;
    count = 0;

    tasks = new Task[SIZE];
}

TaskQueue::~TaskQueue()
{
    delete tasks;
}

bool TaskQueue::isEmpty()
{
    return TaskQueue::count == 0;
}

bool TaskQueue::isFull()
{
    return TaskQueue::head == capacity - 1;
}

void TaskQueue::enqueue(Task* t)
{
    if (isFull())
    {
        return;
    }

    tail = (tail + 1) % capacity;

    tasks[tail] = *t;
    count++;
}

Task TaskQueue::dequeue()
{
    if (isEmpty())
    {
        return;
    }

    Task t = tasks[head];

    head = (head + 1) % capacity;
    count--;

    return t;
}

int TaskQueue::size()
{
    return count;
}

void TaskQueue::sortBy(enum sort_options options)
{
    switch (options)
    {
    case deadline:
        qsort((void*) (&tasks[head]), count, sizeof(Task), sort_deadline_asc);
        break;
    
    case period:
        qsort((void*) (&tasks[head]), count, sizeof(Task), sort_period_asc);
        break;

    default:
        break;
    }
}

int TaskQueue::sort_deadline_asc(const void* t1, const void* t2)
{
    Task* task1 = (Task*) t1;
    Task* task2 = (Task*) t2;

    return (task1->deadline - task2->deadline);
}

int TaskQueue::sort_period_asc(const void* t1, const void* t2)
{
    Task* task1 = (Task*) t1;
    Task* task2 = (Task*) t2;

    return (task1->period - task2->period);
}

Task TaskQueue::peek()
{
    return tasks[head];
}
