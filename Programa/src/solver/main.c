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

    FILE* test_file = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    if (!test_file || !output)
    {
        printf("Error abriendo archivos!\n");
        return 2;
    }

    int dimension;
    char string_board[17] = "";

    fscanf(test_file, "%d\n", &dimension);

    printf("DIMENSION: %d\n", dimension);

    int i = 0;
    for (int row = 0; row < dimension; ++row)
    {
        for (int col = 0; col < dimension; ++col)
        {
            int number;
            fscanf(test_file, "%d,\n", &number);
            string_board[i] = number + '0';
            i++;
        }
    }

    printf("%s\n", string_board);

    Board* board = board_init(dimension);
    board_to_matrix(board, string_board);
    board_print(board);

    board_free(board);
    fclose(test_file);
    fclose(output);

    return 0;
}
