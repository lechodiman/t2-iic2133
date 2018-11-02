#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
  
// A utility function to create a new linked list node. 
QNode* new_node(char* data) 
{ 
    QNode *node = (QNode*)malloc(sizeof(QNode)); 
    strcpy(node->data, data);
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
void queue_add(Queue* q, char* data) 
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
int queue_remove(Queue *q, char* buffer) 
{ 
    // If queue is empty, return -1. 
    if (q->head == NULL) 
       return -1;
  
    // Store previous head and move head one node ahead 
    QNode* temp = q->head; 
    q->head = q->head->next; 
  
    // If head becomes NULL, then change tail also as NULL 
    if (q->head == NULL) 
       q->tail = NULL;
    
    strcpy(buffer, temp->data); 
    free(temp);

    return 0;
}

bool queue_is_empty(Queue* q)
{
	return !q->head;
}

void queue_free(Queue* q)
{
    char data[17] = "";
	while (!queue_is_empty(q)) {
		queue_remove(q, data);
	}

	free(q);
}