/*
 * Solves sudoku puzzle
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* marks unfilled cell */
#define NUM_UNFILLED '.'

/* Fetches value from the board for given (m,n) */
char get_board (char *board, int m, int n, int maxRowSize, int maxColSize)
{
	int index = m * maxColSize + n;
	return board[index];
}

/* Sets value in board for given (m,n) */
void set_board (char *board, int m, int n, int value, int maxRowSize, int maxColSize)
{
	int index = m * maxColSize + n;
	board[index] = value;
}

/* checks if the value is already present in the row 
 * returns true if not found
 * returns false if found 
 */
int is_valid_in_row (char *board, int i, int j, int val, int maxRowSize, int maxColSize)
{
	int x = 0;
	for (x = 0; x < maxColSize; x++) {
		if (x == j) 
			continue; 
		if (get_board(board, i, x, maxRowSize, maxColSize) == val) {
			break; 
		}
	}
	return (x == maxColSize);
}

/* checks if the value is already present in the column
 * returns true if not found
 * returns false if found 
 */
int is_valid_in_col(char *board, int i, int j, int val, int maxRowSize, int maxColSize)
{
	int x = 0;
   	for (x = 0; x < maxRowSize; x++) {
   	    if (x == i) 
   	        continue; 
   	    if (get_board(board, x, j, maxRowSize, maxColSize) == val) {
   	        break; 
   	    }
   	}
   	return (x == maxRowSize);
}


/* checks if the value is already present in the current block
 * returns true if not found
 * returns false if found 
 */
int is_valid_in_block(char *board, int i, int j, int val, int maxRowSize, int maxColSize)
{
	int x, y, x_start, x_end, y_start, y_end;
	x_start = (i/3)*3;
	x_end = ((i/3)+1)*3;
	y_start = (j/3)*3;
	y_end = ((j/3)+1)*3;
	for (x = x_start; x < x_end; x++) {
	    for (y = y_start; y < y_end; y++) {
	        if ((x == i) && (y == j)) 
	            continue; 
	        if (get_board(board, x, y, maxRowSize, maxColSize) == val) {
	            return 0; 
	        }
	    }
	}
	return 1;
}

/* Prints the sudoku board */
int print_board (char *board, int maxRowSize, int maxColSize)
{
	int i, j;

	for (i = 0; i < maxRowSize; i++)
	{
		for (j = 0; j < maxColSize; j++)
		{
			printf ("%c", get_board(board, i, j, maxRowSize, maxColSize));	
		}
		printf ("\n");
	}
}

/* recursive solver function */
int solve_board (char *board, int l, int m, int maxRowSize, int maxColSize)
{
    int val;

	/* we have gone through all cells, and no issues so far */
    if (l == maxRowSize)
        return 1;

	/* we done the current column, lets move to next row */
    if (m == maxColSize)
        return solve_board (board, l+1, 0, maxRowSize, maxColSize);

    if (get_board(board, l, m, maxRowSize, maxColSize) != NUM_UNFILLED)
        return solve_board (board, l, m+1, maxRowSize, maxColSize);

	/* take care of NUM_UNFILLED cell */
    for (val = '1'; val <= '9'; val++)
	{
        if (is_valid_in_row(board, l,m,val, maxRowSize, maxColSize) && 
			is_valid_in_col(board, l,m,val, maxRowSize, maxColSize) &&
            is_valid_in_block(board, l,m,val, maxRowSize, maxColSize))
		{
			set_board(board, l, m, val, maxRowSize, maxColSize);
            if (solve_board(board, l, m+1, maxRowSize, maxColSize))
                return 1;
			set_board(board, l, m, NUM_UNFILLED, maxRowSize, maxColSize);
        }
    }

    return 0;
}

/* sudoku solver */
void solve_sudoku(char *board, int maxRowSize, int maxColSize)
{
    solve_board (board, 0, 0, maxRowSize, maxColSize);
	/* boardRowSize, boardColSize); */
}

/* main program */
int main () {
	int maxRowSize = 9, maxColSize = 9;
	char *board = malloc (sizeof(char) * maxRowSize * maxColSize + 1);
	if (board == NULL) {
		printf ("\r Malloc failed for board\r\n");
		return -1;
	}

	strcpy (board, 	"2.5..9..4"
					"......3.7"
					"7..856.1."
					"45.7....."
					"..9...1.."
					".....2.85"
					".2.418..6"
					"6.8......"
					"1..2..7.8" );

    solve_sudoku (board, maxRowSize, maxColSize);
	print_board (board, maxRowSize, maxColSize);
    return 0;
}

