#pragma once
#include <stdbool.h>

typedef struct queue_node 
{ 
    int key; 
    struct queue_node *next; 
} QNode;
  
typedef struct queue 
{ 
    QNode *head;
    QNode *tail;
} Queue;

Queue* queue_init();
void queue_add(Queue* q, int data);
int queue_remove(Queue *q);
void queue_free(Queue* q);
