#include "tasklist.h"

void task_1(void* args){
	digitalWrite(d1, !digitalRead(d1));
	delay(100);
}

task_list_t* build_task_list(int taskNo){
	task_list_t* taskList = (task_list_t*) malloc(sizeof(task_list_t));
	
	taskList->taskNo = taskNo;
	taskList->tasks = (task_t**) malloc(sizeof(task_t) * taskNo);
	taskList->tasks[0] = create_task(&task_1, NULL);
	
	return taskList;
}

int execute_tasks(task_list_t* taskList){
		for(int i = 0; i < taskList->taskNo; i++){
			execute_task(taskList->tasks[i]);
		}
		return 0;
}

int delete_task_list(task_list_t* taskList){
	for(int i = 0; i < taskList->taskNo; i++){
		delete_task(taskList->tasks[i]);
	}
	free(taskList->tasks);
	free(taskList);
	return 0;
}
