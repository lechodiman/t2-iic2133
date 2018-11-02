#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "hashmap.h"
#include "board.h"

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
    queue_add(q, "123456780");
    queue_add(q, "012345678");
    char output[17] = "";
    queue_remove(q, output);
    printf("output: %s\n", output);
    queue_remove(q, output);
    printf("output: %s\n", output);

    printf("is empty: %d\n", queue_is_empty(q));
    queue_free(q);
    return 0;
}
