#include <stdio.h>

enum 
{
	TOP_LEFT	= '1',
	TOP_MID 	= '2',
	TOP_RIGHT	= '3',
	MID_LEFT	= '4',
	MID_MID		= '5',
	MID_RIGHT	= '6',
	BOTTOM_LEFT	= '7',
	BOTTOM_MID	= '8',
	BOTTOM_RIGHT = '9'
};

enum
{
	SUCCESS = 0, 
	FAILURE = -1
};

enum
{
	WIN = 'W',
	LOSS = 'L'
};

enum
{
	XXX = 'X',
	O00 = 'O'
};

typedef struct think_
{
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
#define 
	think *root;
	int i = 0;
	for (i = 0; i < TIC_TOC_SQUARES; i++)
	{

	}
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


/* Main */
int main()
{
	
	return 0;
}
