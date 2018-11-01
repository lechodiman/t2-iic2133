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

    bool is_sol;

    Board* board = board_init(4);
    
    board_print(board);

    char string_board[] = "123456789abcdef0";
    board_to_matrix(board, string_board);

    board_print(board);

    is_sol = board_is_solution(board);
    printf("IS SOL: %d\n", is_sol);


    board_move_left(board);
    board_print(board);

    board_move_up(board);
    board_print(board);

    board_move_right(board);
    board_print(board);

    board_move_down(board);
    board_print(board);

    is_sol = board_is_solution(board);
    printf("IS SOL: %d\n", is_sol);

    char out_matrix[17] = "";
    board_to_string(board, out_matrix);

    printf("OUT is: %s\n", out_matrix);

    board_to_matrix(board, out_matrix);
    board_print(board);

    board_free(board);

    return 0;
}
