// tool.c, 159

#include <stdio.h>
#include <stdlib.h>
#include "spede.h"
#include "type.h"
#include "extern.h"

typedef struct node *node_ptr;
typedef struct queue *queue_ptr;

/*struct node{
	int data;
	struct node *prev;
	struct node *next;
}*/

/*struct queue{
	node_ptr front;
	node_ptr back;
}*/

void MyBZero(q_t *p, int size) {
/*	queue_ptr myqueue;
	init(&myqueue);
	node_ptr new = (node_ptr)malloc(sizeof(struct node));
	myqueue->front = new;
*/
		int i = 1;
		for (i; i < 20; i++){
		EnQ(0,p);
}

/*int init(queue_ptr * qp){
	queue_ptr q = (queue_ptr)malloc(sizeof(struct queue));
	q->front = NULL;
	q->back = NULL;
	*qp = q;	//set qp
}
*/
void EnQ(int pid, q_t *p) 
// ?????????????????????????????????????????????????
// show error msg and return if queue's already full
// needs coding
// ????????????????????????????????????????????????	
	if (p.size == Q_SIZE){
		printf(stderr, "%s: Queue is full%s; %s\n",strerror(errorno));
		return -1;
	}else
	tail++;
	p.q[tail] = pid;
	
}

int DeQ(q_t *p) { // return -1 if q is empty
// ?????????????????????????????????????????????????
// needs coding
// ?????????????????????????????????????????????????
	if (p.size == 0){
		printf(stderr, "%s: Queue is full%s; %s\n",strerror(errorno));
		return -1;
	}else
	head--;
	
}

