/*
   Checks for repeating characters in a sentence.
   Wastes a lot of space, since it uses the index.
*/

#include <stdio.h>
#include <string.h>

#define V_LEN 127
#define S_LEN 250

int main()
{
	char count[V_LEN] = {0,};
	char str[S_LEN];
	int i;

	printf ("\r Sentence: ");
	fgets(str, S_LEN, stdin);
	str[strlen(str)-1] = '\0';

	for (i = 0; str[i] != '\0'; i++)
	{
		if (i >= V_LEN)
			continue;

		count[str[i]]++;
	}

	for (i = 0; i <= V_LEN; i++)
	{
		if (count[i])
			printf (" The letter %c appeared %d times\r\n", i, count[i]);
	}
	
	return 0;
}
