#include <stdio.h>

#define MAX_MOVES 9 9 9 9 9 9 9 9 9 

enum 
{
	TOP_LEFT,    TOP_MID,    TOP_RIGHT,
	MID_LEFT,    MID_MID,    MID_RIGHT,
	BOTTOM_LEFT, BOTTOM_MID, BOTTOM_RIGHT
};

enum
{
	SUCCESS = 0, 
	FAILURE = -1
};

enum
{
	TRUE = 1,
	FALSE = 0
};

enum
{
	WIN = 'W',
	LOSS = 'L'
};

enum
{
	XXX = 'X',
	O00 = 'O',
	EMPTY = ' '
};

typedef struct think_
{
	char move_history[];
	char move;
	char nchilds;
	char status;
	struct think_ child[0];
}think;

typedef struct qnode_
{
	think *node;
	struct qnode_ *next;	
}qnode;

typedef struct queue_
{
	struct queue_ *dequeue, *enqueue;
}queue;

think* think_malloc(int nchild)
{
	int size = sizeof(think) + nchild * sizeof(think *);
	think *node = (think *) malloc(size);
	if (node == NULL)
		return FAILURE;
	memset (node, 0, size);
	return node;
}

think* construct_think_tree()
{
	think *root;
	qnode element;
	int i;	
	char *board;
	char board[10] = {
			' ', ' ', ' ',
			' ', ' ', ' ',
			' ', ' ', ' ', 
			'\0'
			}; /* Oja board */

	
}

int destroy_think_tree(think **head)
{
	int i = 0;

	if (*head == NULL)
		return SUCCESS;

	for (i = 0; i < (*head)->nchilds; i++)
		destroy_think_tree (&(*head)->child[i]);

	free (*head);
	*head = NULL;

	return SUCCESS;
}

/* Queue enqueue/dequeue */
int queue_enqueue(queue *q, think *node)
{
	qnode *n = malloc(qnode);
	if (n == NULL)
		return FAILURE;

	n->next = NULL;
	n->node = node;

	if (q->enqueue)
		q->enqueue->next = n;
	else
		q->enqueue = n;

	return SUCCESS;
}

think *queue_dequeue(queue *q)
{
	qnode *element = NULL;
	think *tnode = NULL;
	if (q->dequeue == NULL)
		return NULL;

	element = q->dequeue;
	q->dequeue = q->dequeue->next;

	tnode = element->node;
	free(element);

	return (tnode);		
}

int is_win(char *board, char move)
{
	switch(move)
	{
		case TOP_LEFT:
			/*
			 *  O|X|X
			 *  _____
			 *  X|X|
			 *  _____
			 *  X| |X
			 */
			if (board[TOP_LEFT] == board[TOP_MID] && 
				board[TOP_LEFT] == board[TOP_RIGHT])
				return TRUE;
			else if (board[TOP_LEFT] == board[MID_LEFT] &&
					 board[TOP_LEFT] == board[BOTTOM_LEFT])
				return TRUE;
			else if (board[TOP_LEFT] == board[MID_MID] &&
					 board[TOP_LEFT] == board[BOTTOM_RIGHT])
				return TRUE;
			return FALSE;			

		case TOP_MID:
			/*
			 *  X|O|X
			 *  _____
			 *   |X|
			 *  _____
			 *   |X|
			 */
			if (board[TOP_MID] == board[TOP_LEFT] &&
				board[TOP_MID] == board[TOP_RIGHT])
				return TRUE;
			else if (board[TOP_MID] == board[MID_MID] &&
					 board[TOP_MID] == board[BOTTOM_MID])
				return TRUE;
			return FALSE;

		case TOP_RIGHT:
			/*
			 *  X|X|O
			 *  _____
			 *   |X|X
			 *  _____
			 *  X| |X
			 *
			 */
			if (board[TOP_RIGHT] == board[TOP_MID] &&
				board[TOP_RIGHT] == board[TOP_LEFT])
				return TRUE;
			else if (board[TOP_RIGHT] == board[MID_RIGHT] &&
					 board[TOP_RIGHT] == board[BOTTOM_RIGHT])
				return TRUE;
			else if (board[TOP_RIGHT] == board[MID_MID] &&
					 board[TOP_RIGHT] == board[BOTTOM_LEFT])
				return TRUE;
			return FALSE;
			
		case MID_LEFT:
			/*
			 *  X| | 
			 *  _____
			 *  O|X|X
			 *  _____
			 *  X| | 
			 *
			 */
			if (board[MID_LEFT] == board[TOP_LEFT] && 
				board[MID_LEFT] == board[BOTTOM_LEFT])
				return TRUE;
			else if (board[MID_LEFT] == board[MID_MID] &&
					 board[MID_LEFT] == board[MID_RIGHT])
				return TRUE;
			return FALSE;			

		case MID_MID:
			/*
			 *  X|X|X
			 *  _____
			 *  X|O|X
			 *  _____
			 *  X|X|X
			 *
			 */
			if (board[MID_MID] == board[MID_LEFT] && 
				board[MID_MID] == board[MID_RIGHT])
				return TRUE;
			else if (board[MID_MID] == board[TOP_MID] &&
					 board[MID_MID] == board[BOTTOM_MID])
				return TRUE;
			else if (board[MID_MID] == board[TOP_LEFT] &&
					 board[MID_MID] == board[BOTTOM_RIGHT])
				return TRUE;
			else if (board[MID_MID] == board[TOP_RIGHT] &&
					 board[MID_MID] == board[BOTTOM_LEFT])
				return TRUE;
			return FALSE;			

		case MID_RIGHT:
			/*
			 *   | |X
			 *  _____
			 *  X|X|O
			 *  _____
			 *   | |X
			 *
			 */
			if (board[MID_RIGHT] == board[TOP_RIGHT] && 
				board[MID_RIGHT] == board[BOTTOM_RIGHT])
				return TRUE;
			else if (board[MID_RIGHT] == board[MID_MID] &&
					 board[MID_RIGHT] == board[MID_LEFT])
				return TRUE;
			return FALSE;			

		case BOTTOM_LEFT:
			/*
			 *  X| |X
			 *  _____
			 *  X|X| 
			 *  _____
			 *  O|X|X
			 *
			 */
			if (board[BOTTOM_LEFT] == board[MID_LEFT] && 
				board[BOTTOM_LEFT] == board[TOP_LEFT])
				return TRUE;
			else if (board[BOTTOM_LEFT] == board[BOTTOM_MID] &&
					 board[BOTTOM_LEFT] == board[BOTTOM_RIGHT])
				return TRUE;
			else if (board[BOTTOM_LEFT] == board[MID_MID] &&
					 board[BOTTOM_LEFT] == board[TOP_RIGHT])
				return TRUE;
			return FALSE;			

		case BOTTOM_MID:
			/*
			 *   |X| 
			 *  _____
			 *   |X| 
			 *  _____
			 *  X|O|X
			 *
			 */
			if (board[BOTTOM_MID] == board[BOTTOM_LEFT] && 
				board[BOTTOM_MID] == board[BOTTOM_RIGHT])
				return TRUE;
			else if (board[BOTTOM_MID] == board[MID_MID] &&
					 board[BOTTOM_MID] == board[TOP_MID])
				return TRUE;
			return FALSE;			

		case BOTTOM_RIGHT:
			/*
			 *   | |X
			 *  _____
			 *   | |X
			 *  _____
			 *  X|X|O
			 *
			 */
			if (board[BOTTOM_RIGHT] == board[BOTTOM_MID] && 
				board[BOTTOM_RIGHT] == board[BOTTOM_LEFT])
				return TRUE;
			else if (board[BOTTOM_RIGHT] == board[MID_RIGHT] &&
					 board[BOTTOM_RIGHT] == board[TOP_RIGHT])
				return TRUE;
			else if (board[BOTTOM_RIGHT] == board[MID_MID] &&
					 board[BOTTOM_RIGHT] == board[TOP_LEFT])
				return TRUE;
			return FALSE;			

		default:
			return FALSE;
	}	
}

/* Main */
int main()
{
	
	return 0;
}
