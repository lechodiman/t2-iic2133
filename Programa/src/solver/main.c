#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"


int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Modo de uso: ./solver [test.txt] [output.txt]\n");
        printf("Donde:\n");
        printf("\t[test.txt] es el archivo de input\n");
        printf("\t[output.txt] es el nombre del archivo a escribir con el output\n");
    }

    Queue* q = queue_init();
    queue_add(q, 10);
    queue_add(q, 20);
    int elem = queue_remove(q);
    printf("REMOVED %d\n", elem);
    queue_remove(q);
    queue_add(q, 30); 
    queue_add(q, 40); 
    queue_add(q, 50); 
    int elem2 = queue_remove(q);
    printf("REMOVED %d\n", elem2);

    queue_free(q);
    
    return 0;
}
