#include <scheduler.h>

void scheduler(TaskQueue* queue) {
    
    int size = queue->size();

    queue->sort();

    for (int i = 0; i < size; i++)
    {
        Task t = queue->dequeue();
        Serial.println(t.deadline);
    }
}
