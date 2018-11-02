#pragma once
#include <stdbool.h>

typedef struct stack_node 
{ 
    char data[17];
    struct stack_node *next; 
} SNode;
  
typedef struct stack 
{ 
    SNode *head;
} Stack;

Stack* stack_init();
void stack_add(Stack* q, char* data);
int stack_remove(Stack *q, char* buffer);
bool stack_is_empty(Stack* q);
void stack_free(Stack* q);
