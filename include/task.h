#ifndef TASK_H_
#define TASK_H_

#include "Arduino.h"

#define TASK_NO 100

typedef void(*routine_t)(void);
typedef struct Task Task;

typedef struct pcb_t{

}pcb_t;

enum State
{
    WAITING,
    READY,
    BLOCKED,
    RUNNING,
};

typedef struct TaskImpl {
    int id;
    float period;
    int deadline;
    enum State state;
    routine_t routine;
    pcb_t* pcb;
} TaskImpl;

class Task{
    private:
        TaskImpl* task;

        explicit Task(TaskImpl* task):
            task(task){};

    public:
        Task(){};
        ~Task();

        static Task** buildTaskList();
        static int sort_deadline_asc(const void* t1, const void* t2);
        static int sort_period_asc(const void* t1, const void* t2);
        
        inline void setWaiting(){
            this->task->state = WAITING;
        }

        inline void setReady(){
            this->task->state = READY;
        }

        inline void setBlocked(){
            this->task->state = BLOCKED;
        }

        inline void setRunning(){
            this->task->state = RUNNING;
        }

        inline bool isReady(){
            return this->task->state == READY;
        }

        inline bool isWaiting(){
            return this->task->state == WAITING;
        }

        inline void execute(){
            this->task->routine();
        }

        inline uint8_t* getCurrentTcb(){
            return (uint8_t*) this->task->routine;
        }

        inline int getId(){
            return this->task->id;
        }

        inline pcb_t* getPcb(){
            return this->task->pcb;
        }

        inline void setPcb(pcb_t* pcb){
            this->task->pcb = pcb;
        }
};

#endif