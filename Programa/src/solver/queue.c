#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
  
// A utility function to create a new linked list node. 
QNode* new_node(int data) 
{ 
    QNode *node = (QNode*)malloc(sizeof(QNode)); 
    node->key = data; 
    node->next = NULL; 
    return node;
} 
  
// A utility function to create an empty queue 
Queue* queue_init()
{ 
    Queue *q = (Queue*)malloc(sizeof(Queue)); 
    q->head = q->tail = NULL; 
    return q;
} 
  
// The function to add a key k to q 
void queue_add(Queue* q, int data) 
{ 
    // Create a new LL node 
    QNode* temp = new_node(data); 
  
    // If queue is empty, then new node is head and tail both 
    if (q->tail == NULL) 
    { 
       q->head = q->tail = temp; 
       return;
    } 
  
    // Add the new node at the end of queue and change tail 
    q->tail->next = temp; 
    q->tail = temp;
} 
  
// Function to remove a key from given queue q 
QNode* queue_remove(Queue *q) 
{ 
    // If queue is empty, return NULL. 
    if (q->head == NULL) 
       return NULL; 
  
    // Store previous head and move head one node ahead 
    QNode* temp = q->head; 
    q->head = q->head->next; 
  
    // If head becomes NULL, then change tail also as NULL 
    if (q->head == NULL) 
       q->tail = NULL;
    return temp; 
}

bool queue_is_empty(Queue* q)
{
	return !q->head;
}

void queue_free(Queue* q)
{
	while (!queue_is_empty(q)) {
		QNode* node = queue_remove(q);
		free(node);
	}

	free(q);
}