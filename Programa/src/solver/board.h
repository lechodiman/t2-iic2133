#pragma once
#include <stdbool.h>

typedef struct board Board;

struct board
{
    int dimension;
    int** cell;
    int row_zero;
    int col_zero;
};

Board* board_init(int dimension);
void board_move_up(Board* board);
void board_move_down(Board* board);
void board_move_left(Board* board);
void board_move_right(Board* board);
void board_to_string(Board* board, char* buffer);
void board_to_matrix(Board* board, char* string_board);
bool board_is_solution(Board* board);
void board_print(Board* board);
void board_free(Board* board);

