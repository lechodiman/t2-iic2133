#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "hashmap.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Modo de uso: ./solver [test.txt] [output.txt]\n");
        printf("Donde:\n");
        printf("\t[test.txt] es el archivo de input\n");
        printf("\t[output.txt] es el nombre del archivo a escribir con el output\n");
    }


    HashMap* m = hashmap_init();
    char msg[] = "hola";
    char value[] = "value";
    hashmap_put(m, msg, value);
    bool in_map = hashmap_in_map(m, "chao");

    printf("chao IN MAP? %d\n", in_map);

    char arg[10];
    hashmap_get(m, "hola", arg);

    printf("arg: %s\n", arg);

    hashmap_free(m);

    return 0;
}
