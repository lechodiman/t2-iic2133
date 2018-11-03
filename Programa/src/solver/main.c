#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"
#include "hashmap.h"
#include "board.h"
#include "stack.h"

void write_path(Board* board, HashMap* m, Stack* s, FILE* output)
{
    char curr_state[17] = "";
    char parent_state[17] = "";
    char line_diff[10] = "";

    if (board->dimension == 4)
    {
        strcpy(curr_state, "123456789abcdef0");        
    } 

    if (board->dimension == 3) {
        strcpy(curr_state,"123456780");
    }

    /* Look for parent state */
    while (strcmp(curr_state, "start") != 0)
    {
        /* Get parent state */
        hashmap_get(m, curr_state, parent_state);

        board_diff(board, curr_state, parent_state, line_diff);

        stack_add(s, line_diff);

        /* Update curr state */
        strcpy(curr_state, parent_state);
    } 

    /* Remove extra step */
    stack_remove(s, line_diff);

    /* Write output*/
    fprintf(output, "%d\n", s->size);

    while (!stack_is_empty(s))
    {
        stack_remove(s, line_diff);

        /* Write in file */ 
        fprintf(output, "%s\n", line_diff);
    }

}

void bfs(Board* board, Queue* q, HashMap* m)
{
    char initial_string_board[17] = "";
    board_to_string(board, initial_string_board);
    // printf("initial_string_board: %s\n", initial_string_board);
    
    // FILE* states_file = fopen("states.txt", "w");

    queue_add(q, initial_string_board);
    hashmap_put(m, initial_string_board, "start");

    bool solved = false;

    if (board_is_solution(board))
    {
        // printf("Solution found!\n");
        return;
    }

    /* Initialize previous and current states */
    char prev_string_board[17] = "";
    char curr_string_board[17] = "";

    /* Previous board state starts as the initial */
    // strcpy(prev_string_board, initial_string_board);

    /* While there are states to explore */    
    while (!queue_is_empty(q))
    {
        /* Get state from queue */
        queue_remove(q, prev_string_board);
        /* Insert state to board */
        board_to_matrix(board, prev_string_board);
        // printf("EXPLORING NEW MATRIX:\n");
        // board_print(board);

        /* If it is solution*/
        if (board_is_solution(board) && !solved)
        {
            solved = true;
            // printf("Solution found!\n");
            // fclose(states_file);
            return;
        }

        /* Explore states*/

        /* Explore left*/
        board_move_left(board);
        /* Get string representation */
        board_to_string(board, curr_string_board);
        /* If state not in hashmap*/
        if (!hashmap_in_map(m, curr_string_board))
        {
            // printf("ADDED LEFT:\n");
            // board_print(board);

            /* Add to queue*/
            queue_add(q, curr_string_board);
            // fprintf(states_file, "%s\n", curr_string_board);
            /* Add curr: prev to hashmap*/
            hashmap_put(m, curr_string_board, prev_string_board);
        }
        /* Reset to state before explore */
        board_move_right(board);


        /* Explore right*/
        board_move_right(board);
        /* Get string representation */
        board_to_string(board, curr_string_board);
        /* If state not in hashmap*/
        if (!hashmap_in_map(m, curr_string_board))
        {   
            // printf("ADDED RIGHT:\n");
            // board_print(board);

            /* Add to queue */
            queue_add(q, curr_string_board);
            // fprintf(states_file, "%s\n", curr_string_board);
            /* Add curr: prev to hashmap*/
            hashmap_put(m, curr_string_board, prev_string_board);
        }
        /* Reset to state before explore */
        board_move_left(board);

        /* Explore down*/
        board_move_down(board);
        /* Get string representation */
        board_to_string(board, curr_string_board);
        /* If state not in hashmap*/
        if (!hashmap_in_map(m, curr_string_board))
        {   
            // printf("ADDED DOWN:\n");
            // board_print(board);

            /* Add to queue */
            queue_add(q, curr_string_board);
            // fprintf(states_file, "%s\n", curr_string_board);
            /* Add curr: prev to hashmap*/
            hashmap_put(m, curr_string_board, prev_string_board);
        }
        /* Reset to state before explore */
        board_move_up(board);

        /* Explore up*/
        board_move_up(board);
        /* Get string representation */
        board_to_string(board, curr_string_board);
        /* If state not in hashmap*/
        if (!hashmap_in_map(m, curr_string_board))
        {   
            // printf("ADDED UP:\n");
            // board_print(board);

            /* Add to queue */
            queue_add(q, curr_string_board);
            // fprintf(states_file, "%s\n", curr_string_board);
            /* Add curr: prev to hashmap*/
            hashmap_put(m, curr_string_board, prev_string_board);


        }
        /* Reset to state before explore */
        board_move_down(board);

    }
    return;
}


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

    // printf("DIMENSION: %d\n", dimension);

    int i = 0;
    for (int row = 0; row < dimension; ++row)
    {
        for (int col = 0; col < dimension; ++col)
        {
            int number;
            char hex[2] = "";
            fscanf(test_file, "%d,\n", &number);
            sprintf(hex, "%x", number);
            strcat(string_board, hex);
            // string_board[i] = hex;
            i++;
        }
    }

    Board* board = board_init(dimension);
    Queue* q = queue_init();
    HashMap* m = hashmap_init();
    Stack* s = stack_init();

    board_to_matrix(board, string_board);
    // printf("INITIAL MATRIX BEFORE BFS:\n");
    // board_print(board);

    bfs(board, q, m);
    write_path(board, m, s, output);

    board_free(board);
    queue_free(q);
    hashmap_free(m);
    stack_free(s);
    fclose(test_file);
    fclose(output);

    return 0;
}
