#include <stdio.h>

typedef (void)(*Task)(void*);

typedef struct{
	int preemption_level;
	int priority;
	Task task;
}task_t;

void task_1(void*){
	:
}

void task_2(void*){

}

void task_3(void*){
}



int main(){


	return 0;
}
