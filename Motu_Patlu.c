/* 
* Motu Patlu - The last brick problem
* 
* Motu and Patlu are putting N bricks in a wall in iterations. They want to see who puts the last brick.
* 
* The follow a simple rule,
* 
*     First Patlu will put the brick and then Motu
*     Patlu can add i bricks in ith iteration while Motu can add 2xi [two times i]
* 
* Task is to print the name of the one who will put the last brick.
* Eg: 
* Input : 11
* Output : Patlu
* turn1: PMM
* turn2: PMMPPMMMM
* turn3: PMMPPMMMMPPP  <- since 11 comes in Patlu's turn.
* */

#include <stdio.h>

int main()
{
	int turn, nbricks, brick; 
	char *players[2] = { "Patlu", "Motu" };
	char *last_player;

	scanf("%d", &nbricks);
	turn = 1;
	brick = 0;

#if 1
	for (turn = 1;1 ; turn++)
	{
		/* Paltu played */
		brick += turn;
		if (brick >= nbricks)
		{
			last_player = players[0];
			break;
		}

		/* Motu's turn */
		brick += turn * 2;
		if (brick >= nbricks)
		{
			last_player = players[1];
			break;
		}
	}
	printf("%s\r\n", last_player);
#else
 	/* In case they are playing like this 
 	 * Turn1: P
	 * Turn2: PMM
	 * Turn3: PMMPPP
	 * Turn4: PMMPPPMMMMMMMM <- 11th brick placed by Motu
	 */
	for (turn = 1; brick < nbricks; turn++)
		brick += (turn%2)?turn:turn*2;
	printf("%s\r\n", players[turn%2]);
#endif

	return 0;
}
