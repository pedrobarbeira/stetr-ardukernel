#ifndef _TASK_LIST_H
#define _TASK_LIST_H

#include "task.h"

#define d1 13
#define d2 12
#define d3 11
#define d4 10

typedef struct task_list_t task_list_t;

struct task_list_t{
	task_t** tasks;
	int taskNo;
};

task_list_t* build_task_list();

int execute_tasks(task_list_t* taskList);

int delete_task_list(task_list_t* taskList);

#endif //_TASK_LIST_H_
