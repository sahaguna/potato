// tool.c, 159


#include "spede.h"
#include "type.h"
#include "extern.h"


void MyBZero(q_t *p, int size) {
	p->size = size;
	p->head = size;
	p->tail = size;
}


void EnQ(int pid, q_t *p) {
// ?????????????????????????????????????????????????
// show error msg and return if queue's already full
// needs coding
// ????????????????????????????????????????????????	
	if (p->size == 20){
		printf("\nQueue is full \n");
		return;
	}else
	p->q[p->tail]= pid;
	p->tail ++;
	p->size ++;
}

int DeQ(q_t *p) { // return -1 if q is empty
// ?????????????????????????????????????????????????
// needs coding
// ?????????????????????????????????????????????????
	int pid;
	
	if (p->size == 0){
		printf("Queue is empty\n");
		return;
	}else
	pid=p->head;
	p->head--;
	p->size--;
	return pid;
}

