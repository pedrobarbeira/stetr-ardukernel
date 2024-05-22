#include <task_queue.h>

/**
 * @brief Construct a new Task Queue:: Task Queue object
 * 
 * @param size Queue size
 */
TaskQueue::TaskQueue(int size = TASK_NO)
{
    capacity = TASK_NO;
    head = 0;
    tail = -1;
    size = 0;

    tasks = new Task*[TASK_NO];
}

/**
 * @brief Destroy the Task Queue:: Task Queue object
 * 
 */
TaskQueue::~TaskQueue()
{
    for(int i = 0; i < this->size(); i++){
        delete tasks[i];
    }
    delete tasks;
}

/**
 * @brief Checks if the queue is empty
 * 
 * @return true when empty
 * @return false when not empty
 */
bool TaskQueue::isEmpty()
{
    return TaskQueue::size == 0;
}

/**
 * @brief Checks if the queue if full
 * 
 * @return true when full
 * @return false when not full
 */
bool TaskQueue::isFull()
{
    return TaskQueue::head == capacity - 1;
}

/**
 * @brief Adds a new task to the queue
 * 
 * @param t The new task to be added 
 */
void TaskQueue::enqueue(Task* t)
{
    if (isFull())
    {
        return;
    }

    tail = (tail + 1) % capacity;

    tasks[tail] = t;
    count++;
}

/**
 * @brief Retrieves the Task in the head of the queue and removes it
 * 
 * @return Task* The Task in the head of the queue
 */
Task* TaskQueue::dequeue()
{
    if (isEmpty())
    {
        return nullptr;
    }
 
    Task* task = tasks[head];

    head = (head + 1) % capacity;
    count--;

    return task;
}

/**
 * @brief Gets the size of the queue
 * 
 * @return int The queue's size 
 */
int TaskQueue::size()
{
    return count;
}

/**
 * @brief Sorts the queue according to a criteria
 * 
 * @param options The criteria used to sort the queue
 */
void TaskQueue::sortBy(enum sort_options options)
{
    switch (options)
    {
        case deadline:
            qsort((void*) (&tasks[head]), count, sizeof(Task), Task::sort_deadline_asc);
            break;
        
        case period:
            qsort((void*) (&tasks[head]), count, sizeof(Task), Task::sort_period_asc);
            break;

        default:
            break;
    }
}

/**
 * @brief Gets the Task in the head of the queue without removing it
 * 
 * @return Task* The Task in the head of the queue
 */
Task* TaskQueue::peek()
{
    return tasks[head];
}

/**
 * @brief Gets all the Tasks in a queue
 * 
 * @return Task** An array of pointers to Tasks 
 */
Task** TaskQueue::getAllTasks()
{
    return tasks;
}
