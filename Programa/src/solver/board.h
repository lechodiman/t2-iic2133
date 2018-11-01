#pragma once
#include <stdbool.h>

typedef struct board Board;

struct board
{
    int dimension;
    int** cell;
    int row_zero;
    int col_zero;
}