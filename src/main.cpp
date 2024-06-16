#include <hypervisor.h>

volatile void* volatile pxCurrentTCB = 0;
int tickCount;

void setup(void);
void loop(void);

Task** tasks;
int taskNum = 4;
int currTask = 0;

static uint8_t space1[128];
static uint8_t space2[128];
static uint8_t space3[128];
static uint8_t space4[128];

uint8_t* stackspace[4] = {
    space1, space2, space3, space4
};

void mock_task_1(){
    while(1){
        Serial.println("Printing task 1");
        delay(200);
    }
}

void mock_task_2(){
    while(1){
        Serial.println("Printing task 2");
        delay(400);
    }
}

Task* task1;
Task* task2;

void setup()
{
    Serial.begin(9600);

    while (!Serial);
    Serial.println("We are live");

    config_timer1_interrupts();

    task1 = buildTask(space1, 2, 10, WAITING, mock_task_1);
    task2 = buildTask(space2, 2, 10, WAITING, mock_task_2);

    pxCurrentTCB = (uint8_t*) task1->stackptr;
    delay(200);

    RESTORE_CTX()
}

void loop()
{
}

int task = 0;
uint16_t task1sp = 0;
uint16_t task2sp = 0;

/**
 * @brief Construct a new ISR object to handle Timer 1 interrupts.
 * It is a naked function, because context switching may occur 
 * and we need to save and restore the context manually
 */
ISR(TIMER1_COMPA_vect){
    // Task* task = tasks[currTask];
    // uint16_t sp = Hypervisor::saveCtx();
    // task->setStackPtr(sp);

    // currTask = (++currTask) % taskNum;
    // task = tasks[currTask];
    // Hypervisor::restoreCtx(task->getStackPointer());
}
