#include <stdio.h>
#include "tasklist.h"
#include "task.h"

int main(){
	task_list_t* taskList = build_task_list();
	
	if(execute_tasks(taskList)){
		fprintf(stderr, "Error executing tasks\n");
	}
	else{
		printf("Done\n");
	}
	
	delete_task_list(taskList);
	
	return 0;
}
