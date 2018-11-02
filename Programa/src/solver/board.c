#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

Board* board_init(int dimension)
{
    Board* board = (Board* )malloc(sizeof(Board));
    board->dimension = dimension;

    board->cell = (int** )malloc(sizeof(int*) * dimension);
    for (int row = 0; row < dimension; row++)
    {
        board->cell[row] = (int* )malloc(sizeof(int) * dimension);
        for (int col = 0; col < dimension; col++)
        {
            // initialize with -1 as empty
            board->cell[row][col] = -1;
        }
    }

    /* Place 0 at (0,0) in board by default*/
    board->row_zero = 0;
    board->col_zero = 0;

    return board;
}

void board_set_cell(Board* board, int row, int col, int value)
{
    /* Update row and col for zero */
    if (value == 0)
    {
        board->row_zero = row;
        board->col_zero= col;
    }

    board->cell[row][col] = value;
}

void board_move_up(Board* board)
{
    if (board->row_zero > 0)
    {
        /* Save temp value*/
        int value = board->cell[board->row_zero - 1][board->col_zero];
        /* Move it down*/
        board_set_cell(board, board->row_zero, board->col_zero, value);
        /* Move zero up*/
        board_set_cell(board, board->row_zero - 1, board->col_zero, 0);        
    
    } else {
        /* Else, zero is at row 0*/

        /* Save temp value*/
        int value = board->cell[board->dimension - 1][board->col_zero];
        /* Move it down (where zero is)*/
        board_set_cell(board, board->row_zero, board->col_zero, value);
        /* Move zero up*/
        board_set_cell(board, board->dimension - 1, board->col_zero, 0);                
    }
    return;
}

void board_move_down(Board* board)
{
    if (board->row_zero < board->dimension - 1)
    {
        /* Save temp value*/
        int value = board->cell[board->row_zero + 1][board->col_zero];
        /* Move it up*/
        board_set_cell(board, board->row_zero, board->col_zero, value);
        /* Move zero down*/
        board_set_cell(board, board->row_zero + 1, board->col_zero, 0);        
    
    } else {
        /* Else, zero is at row dimension - 1*/

        /* Save temp value*/
        int value = board->cell[0][board->col_zero];
        /* Move it up (where zero is)*/
        board_set_cell(board, board->row_zero, board->col_zero, value);
        /* Move zero down*/
        board_set_cell(board, 0, board->col_zero, 0);                
    } 
    return;
}

void board_move_left(Board* board)
{
    if (board->col_zero > 0)
    {
        /* Save temp value*/
        int value = board->cell[board->row_zero][board->col_zero - 1];
        /* Move it to zero*/
        board_set_cell(board, board->row_zero, board->col_zero, value);
        /* Move zero left*/
        board_set_cell(board, board->row_zero, board->col_zero - 1, 0);        
    
    } else {
        /* Else, zero is at col 0*/

        /* Save temp value*/
        int value = board->cell[board->row_zero][board->dimension - 1];
        /* Move it down (where zero is)*/
        board_set_cell(board, board->row_zero, board->col_zero, value);
        /* Move zero left across*/
        board_set_cell(board, board->row_zero, board->dimension - 1, 0);                
    }
    return;
}

void board_move_right(Board* board)
{
    if (board->col_zero < board->dimension - 1)
    {
        /* Save temp value*/
        int value = board->cell[board->row_zero][board->col_zero + 1];
        /* Move it up*/
        board_set_cell(board, board->row_zero, board->col_zero, value);
        /* Move zero down*/
        board_set_cell(board, board->row_zero, board->col_zero + 1, 0);        
    
    } else {
        /* Else, zero is at col dimension - 1*/

        /* Save temp value*/
        int value = board->cell[board->row_zero][0];
        /* Move it up (where zero is)*/
        board_set_cell(board, board->row_zero, board->col_zero, value);
        /* Move zero down*/
        board_set_cell(board, board->row_zero, 0, 0);                
    } 
    return;
}

void board_to_string(Board* board, char* buffer)
{
    char str[17] = "";

    for (int row = 0; row < board->dimension; row++)
    {
        for (int col = 0; col < board->dimension; col++)
        {
            char hex[2] = "";

            int elem = board->cell[row][col];
            /* Get hexadecimal respresentation*/
            sprintf(hex, "%x", elem);
            /* Add to str character array*/
            strcat(str, hex);
        }
    }

    /* Copy result to buffer*/
    strcpy(buffer, str);
}

void board_to_matrix(Board* board, char* string_board)
{
    int i;

    i = 0;
    for (int row = 0; row < board->dimension; row++)
    {
        for (int col = 0; col < board->dimension; col++)
        {
            /* convert from hexadecimal to int */
            char hexa_number= string_board[i];

            int number = (int) strtol(&hexa_number, NULL, 16);
            /* add to board*/
            board_set_cell(board, row, col, number);
            i++;
        }
    }
}

bool board_is_solution(Board* board)
{
    char buffer_string[17] = "";
    char solution[17] = "";
    
    if (board->dimension == 4)
    {
        strcpy(solution, "123456789abcdef0");        
    } 

    if (board->dimension == 3) {
        strcpy(solution,"123456780");
    }

    board_to_string(board, buffer_string);
    
    if (strcmp(buffer_string, solution) == 0) {
        return true;
    }

    return false;
}

int board_diff(Board* board, char* board_children, char* board_parent, char* buffer)
{
    int i = 0;
    int row;
    int col;
    char output[10] = "";

    while (i < board->dimension * board->dimension)
    {
        /* convert from hexadecimal to int */
        char hexa_number = board_parent[i];
        int number = (int)strtol(&hexa_number, NULL, 16);

        if ( number != 0 && board_parent[i] != board_children[i])
        {
            row = (int) (i / (board->dimension));
            col = i % (board->dimension);

            // printf("index: %d\n", i);
            sprintf(output, "%d,%d", col, row);

            strcpy(buffer, output);

            return 0;
        }

        i++;
    }

    return -1;
}

void board_print(Board* board)
{
    for (int row=0; row < board->dimension; row++)
    {
        for(int column=0; column < board->dimension; column++)
        {
            printf("%d\t", board->cell[row][column]);
        }
        printf("\n");
    }
    printf("\n");
}

void board_free(Board* board)
{
    for (int row = 0; row < board->dimension; row++)
    {
        free(board->cell[row]);
    }

    free(board->cell);
    free(board);
}