#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
  
// A utility function to create a new linked list node. 
SNode* new_stack_node(char* data) 
{ 
    SNode *node = (SNode*)malloc(sizeof(SNode)); 
    strcpy(node->data, data);
    node->next = NULL;
    return node;
} 
  
// A utility function to create an empty Stack 
Stack* stack_init()
{ 
    Stack *q = (Stack*)malloc(sizeof(Stack)); 
    q->head = NULL;
    q->size = 0;
    return q;
} 
  
// The function to add a key k to q 
void stack_add(Stack* q, char* data) 
{ 
    // Create a new LL node 
    SNode* temp = new_stack_node(data); 
  
    temp->next = q->head;
    q->head = temp; 
    q->size++;
    
    return;
} 
  
// Function to remove a key from given Stack q 
int stack_remove(Stack *q, char* buffer) 
{ 
    // If Stack is empty, return -1. 
    if (q->head == NULL) 
       return -1;
  

    SNode* temphead = q->head;
    q->head = q->head->next;

    strcpy(buffer, temphead->data); 
    free(temphead);
    q->size--;

    return 0;
}

bool stack_is_empty(Stack* q)
{
    return !q->head;
}

void stack_free(Stack* q)
{
    char data[17] = "";
    while (!stack_is_empty(q)) {
        stack_remove(q, data);
    }

    free(q);
}