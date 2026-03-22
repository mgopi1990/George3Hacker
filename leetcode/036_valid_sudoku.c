/* 

36. Valid Sudoku

Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

Each row must contain the digits 1-9 without repetition.
Each column must contain the digits 1-9 without repetition.
Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note:

A Sudoku board (partially filled) could be valid but is not necessarily solvable.
Only the filled cells need to be validated according to the mentioned rules.
 

Example 1:


Input: board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true
Example 2:

Input: board = 
[["8","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.
 

Constraints:

board.length == 9
board[i].length == 9
board[i][j] is a digit 1-9 or '.'.

*/


#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_ROW 9
#define MAX_COL 9

enum {
	HASH_TABLE_ROW,
	HASH_TABLE_COL,
	HASH_TABLE_SUBBOX,
	HASH_TABLE_MAX
};

int hash_str_num (char str_num);
bool isValidSudoku(char** board, int boardSize, int* boardColSize); 


/*
 * basically this function, shifts number, 
 * sets appropriate position to 1
 * eg. 0x1 << (shift-1)	 [shift > 0]
 */
int hash_str_num (char str_num) 
{
	switch (str_num)
	{
		case '1': return 0x0001;
		case '2': return 0x0002;
		case '3': return 0x0004;
		case '4': return 0x0008;
		case '5': return 0x0010;
		case '6': return 0x0020;
		case '7': return 0x0040;
		case '8': return 0x0080;
		case '9': return 0x0100;
	  /*case '.': return 0x0000;*/
		default:  return 0x0000;
	}
}


/* what is wrong with this prototype ?
 * gcc wouldnt like passing 2 dimension array like this */
bool isValidSudoku(char** board, int boardSize, int* boardColSize)
{
	int hashtable[HASH_TABLE_MAX][MAX_ROW];
	int i, j, k, set_bit;
	char (*sudoku)[MAX_COL] = (char (*)[MAX_COL]) board;

	memset (hashtable, 0, sizeof(hashtable));

	for (i = 0; i < boardSize; i++)
	{
		for (j = 0; j < *boardColSize; j++) {
			set_bit = hash_str_num (sudoku[i][j]);

			/* find which sub box we are */
			k = ((i / 3) *3) +  (j / 3);

			/*
			 * we check the index over each table.
			 * if set already, number is repeating.
			 * return false
			 */
			if ((hashtable[HASH_TABLE_ROW][i] & set_bit) ||
				(hashtable[HASH_TABLE_COL][j] & set_bit) ||
				(hashtable[HASH_TABLE_SUBBOX][k] & set_bit))
			{
				return false;
			}

			hashtable[HASH_TABLE_ROW][i] |= set_bit;
			hashtable[HASH_TABLE_COL][j] |= set_bit;
			hashtable[HASH_TABLE_SUBBOX][k] |= set_bit;
		}
	}
	
	/* done with all. sudoku is clean. return true */
	return true;
} 

int main() {
	int max_col = MAX_COL; /* I dont know why I am doing this */
	char board1[MAX_ROW][MAX_COL] = {
		{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
		{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
		{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
		{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
		{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
		{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
		{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
		{'.', '.', '.', '.', '8', '.', '.', '7', '9'}
	};
	char board2[MAX_ROW][MAX_COL] = {
		{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
		{'6', '.', '.', '1', '9', '5', '.', '.', '.'},
		{'.', '9', '8', '.', '.', '.', '.', '6', '.'},
		{'8', '.', '.', '.', '6', '.', '.', '.', '3'},
		{'4', '.', '.', '8', '.', '3', '.', '.', '1'},
		{'7', '.', '.', '.', '2', '.', '.', '.', '6'},
		{'.', '6', '.', '.', '.', '.', '2', '8', '.'},
		{'.', '.', '.', '4', '1', '9', '.', '.', '5'},
		{'.', '.', '.', '.', '8', '.', '.', '7', '9'}
	};

	printf ("\r1: %d\r\n", isValidSudoku((char **)&board1[0][0], MAX_ROW, &max_col)); 
	printf ("\r2: %d\r\n", isValidSudoku((char **)&board2[0][0], MAX_ROW, &max_col)); 

	return 0;
}

