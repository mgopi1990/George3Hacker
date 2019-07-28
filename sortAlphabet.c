/*
 * SortAlpha.c
 * 
 * Try to sort like this . 
 *
 * Input  = "aBcDbAdC"
 * Output = "aABbcCDd"
 *
 * Note: the order should not change.
 *
 */

#include <stdio.h>

/* A is 0x41  0100 0001, 
 * a is 0x61  0110 0001 
 *      0xDF  1101 1111
 */
#define IGNORE_CASE(x) ((x) & 0xDF)

char* sortAlpha(char *string);

int main()
{
	char input[100];

	scanf ("%s", input);	
	printf ("%s\r\n", sortAlpha(input));

	return 0;
}

char* sortAlpha(char *string)
{
	int i, j, k, len, temp;

	/* why include string.h for just strlen */
	for (len = 0; string[len] != '\0'; len++);

	for (i = 0; i < len; i++)
	{
		/* assume string[i] is a, look for all a, A */
		for (j = i+1; j < len; j++)
		{
			/* break as soon as we find a, A */
			if (IGNORE_CASE(string[i]) == IGNORE_CASE(string[j]))
				break;
		}

		/* incase, we are done with a, A; proceed with next letter */
		if (j == len)
			continue;

		/* right shift to fill the gap from which we find the new A */
		temp = string[j];
		for (k = j; k >= i+1; k--)
		{
			string[k] = string[k-1];	
		}
	
		/* write back our A in the location */
		string[i+1] = temp;
	}

	/* simply return */
	return (string);
}

