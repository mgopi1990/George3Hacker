/*
A fun and easy problem. Will like all beginners to try it .

You have been selected for a game show whose prize money is 1 million dollors $$. However , its a life and death game.

The game is that N persons , including you , are made to stand in a circular fashion.A pistol with unlimited bullets is given randomly to any person out of these N persons and the person who has the pistol can shoot the person right in front of him and then pass the pistol to the next person ahead of him and the process goes on until only one person remains and he is the winner of the game :P .

You being a programmer , want to win this game , so you decide to write a quick program to calculate the position where you will need to stand so as to save yourself from being killed.

For example : if N=5 , 1->2->3->4->5->1 and pistol is given to person standing at position 1 . Then the game will proceed as below: a X b means a killed b

1 X 2
3 X 4
5 X 1
3 X 5

Game ends and person standing at 3rd position wins the game and prize money :D.

Input :
2 <=N<=1000000 (total number of persons)
1<=K<=1000000 (the position of the beginner of the game)
Output :
Number indicating winner's position.

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_PERSON 1000000
#define MIN_PERSON 2

typedef struct person_
{
	long int name;
	struct person_ *next;	
}person;

int main()
{
	long int i, N, K;
	person *p = NULL, *gun_guy = NULL;
	
	printf ("\r Enter size: ");
	scanf ("%ld", &N);

	if (N < MIN_PERSON || N > MAX_PERSON)
	{
		printf ("\r [%s,%d] Error: No. of person allowed (%ld<= N <= %ld)\r\n", 
					__FUNCTION__, __LINE__, MIN_PERSON, MAX_PERSON);
		return 1;
	}

	printf ("\r Enter starting position: ");
	scanf ("%ld", &K);

	if (K > N || K <= 0)
	{
		printf ("\r [%s,%d] Error: Can't give gun to that person %ld.\r\n", 
					__FUNCTION__, __LINE__, K);
		return 1;
	}

	/* Call the people */
	p = malloc(sizeof (person) * N);
	if (p == NULL)
	{
		printf ("\r [%s,%d] Malloc failed\r\n", __FUNCTION__, __LINE__);
		return 1;
	}

	/* Make them stand in a circle */
	for (i = 0; i < N-1; i++)
	{
		p[i].name =	i + 1;
		p[i].next = &p[i+1];	
	}	

	/* last guy is special */
	p[N-1].name = N;
	p[N-1].next = &p[0];


	/* Give the gun and keep killing :P */
	gun_guy = &p[K-1];
	for (i = 0; i < N-1; i++)
	{
#ifdef DEBUG_WANTED
	printf ("\r %ld X %ld\r\n", gun_guy->name, gun_guy->next->name);
#endif
		
		gun_guy->next = gun_guy->next->next;
		gun_guy = gun_guy->next;
	}

	printf ("\r Survivor: %ld\r\n", gun_guy->name);

	/* Go home, People */
	free (p);
	return 0;
}
