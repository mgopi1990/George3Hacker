#include <stdio.h>
#include <string.h>

char tracks[][80] = {
"I left my heart in Harvard Med School",
"Newark, Newark - a wonderful town",
"Dancing with a Dork",
"From here to maternity",
"The girl from Iwo Jima",
};

void find_track(char search_for[])
{
	int i;
	for (i = 0; i < 5; i++)
	{
		/* printf ("\r [%s] [%s]\r\n", tracks[i], search_for); */
		if (strstr(tracks[i], search_for))
		{
			printf (" Track %i: '%s'\n", i, tracks[i]);
		}
	}
}

int main()
{
	char search_for[80];
 	int len;
	printf ("Search for: ");
	fgets(search_for, 5, stdin);
	len = strlen(search_for);
	if (search_for[len-1] == '\n')
		search_for[len-1] = '\0'; 
	find_track(search_for);
	return 0;
}
