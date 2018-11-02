#pragma once
#include <stdbool.h>

typedef struct queue_node 
{ 
    char data[17]; 
    struct queue_node *next; 
} QNode;
  
typedef struct queue 
{ 
    QNode *head;
    QNode *tail;
} Queue;

Queue* queue_init();
void queue_add(Queue* q, char* data);
int queue_remove(Queue *q, char* buffer);
bool queue_is_empty(Queue* q);
void queue_free(Queue* q);
