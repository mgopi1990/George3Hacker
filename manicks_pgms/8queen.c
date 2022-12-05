#include <stdio.h>
#include <stdlib.h>

int queen (int);
int printQ ();
int place (int, int);
int display ();

int count = 0, x[20];

int main()
{
	queen (1);
	display ();
	return 0;
}

int queen (int k)
{
	int i;
	for (i = 1; i <= 8; i++)
	{
		if (place (k, i) == 1)
		{
			x[k] = i;
			if (k == 8)
				printQ ();
		}
		else
			queen (k + i);
	}
}

int place (int k, int i)
{
	int j;

	for (j = 1; j < k; j++)
	{
		if ((x[j] == i) || (abs (x[j] - i) == abs (j-k)))
			return (0);
	}
	return (1);
}

int printQ ()
{
	int i, j;
	count++;

	for (i = 1; i <= 8; i++)
	{
		for (j = 1; j <= 8; j++)
		{
			if (x[i] == j)
				printf ("\tQ");
			else
				printf ("\t-");
		}
		printf ("\r\n");
	}

	printf ("\r\n");
	return 0;
}

int display ()
{
	if (count == 0)
		printf ("\r No possible solution\r\n");
	else
		printf ("\r No. of possible solutions: %d\r\n", count);

	return 0;
}
