/*
https://www.facebook.com/photo.php?fbid=2054459774792447&set=pcb.1640056289415995&type=3&theater

Given a trianglular assortment of size N where the total number of rows is N, which is always 
even. The tirangles are numbered starting with the triangle in the first row, and increasing 
left ot right and top to bottom. An example of such an arrangement with N=6 is given below.

         --
        / 1\
      -- -- --
     / 2\ 3/ 4\
   -- -- -- -- --
  / 5\ 6/ 7\ 8/ 9\
  --- -- -- -- ---
  \10/11\12/13\14/
   -- -- -- -- --
     \15/16\17/
      -- -- --
        \18/
         --

The task is to find minimum distance d from a given starting triangle (S) to all the other
triangles. Two triangles are called adjacent if they have a common edge. From a triangle,
you can only go to an adjacent triangle. Distance between two triangles is the minimum
number of edges to be crossed to reach the destination triangle from the starting triangle.
The distance between any triangle to its adjacent triangle is 1 unit.

*/

#include <stdio.h>
	
int construct_graph(node *daimond, int N);

typedef struct node_
{
	int name;
	struct node_ *left;
	struct node_ *right;
	struct node_ *up;
	struct node_ *down;

	/* weight calc */	
	int weight;
	struct node_ *parent;

	/* points to next row start */
	struct node_ *next_row;
}node;

int main()
{
	int N = 6, S = 8; 
	int num_nodes;
	node *daimond;

#if 0 
	scanf("%d %d", &N, &S);
#endif

	/*  using AP summation formula
		 Sn = a + (n-1) * d
		 a  = 1 (no of nodes in start of triangle)
		 n  = N ()
		 d  = 2 (each level, no of node increases by 2)
	*/

	num_nodes = (1 + (N-1) * 2) * 2;	
	
	daimond = malloc(sizeof(node) * daimond);
	if (daimond == NULL) 
	{
		printf ("\r[%s,%d] FAILED: Couldnt allocate memory\r\n",
					__FUNCTION__, __LINE__); 
		return 1;	
	}
	/* 	Atleast it takes care of assigning NULL 
		to unused pointers	
	*/
	memset (daimond, 0, sizeof(node) * daimond);

	construct_graph(daimond, N);
	print_graph(daimond, N);
	draw_tree(diamond, N, daimond);	
	

	free (n);
	return 0;
}
	
int construct_graph(node *daimond, int N)
{
	int i = 0;
	int name = 1;
	int num_nodes;
	node *prev_node;

	num_nodes = 1;
	prev_node = &daimond[0];
	for (i = 0; i < N/2; i++)
	{
		daimond[name-1].name = name++;
		for (j = 1; j < num_nodes; j++)
		{
			daimond[j].name = name++; 
			daimond[j].left = &daimond[j-1];
			daimond[j-1].right = &daimond[j];	
		}
		num_nodes += 2;
	}

	prev_node = &daimond[0];
	for (i = 1; i < N/2; i++)
	{
		daimond[name-1].name = name++;
		
	}
}
