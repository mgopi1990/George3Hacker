/*
 * My machine will check if the encoding is correctly done or not 
 * User will provide input and output. 
 * 
 * Eg1:
 *  Input = hello
 *  Output = elloh
 *
 * Eg2:
 *  Input=listen
 *  Output=silent
 *
 * Like wise, make sure the output s exactly same from the input.My machine will encode. 
 *
 */

#include <stdio.h>

#define TRUE  1
#define FALSE 0

#define SLEN  100
#define NON_PRINT_CHAR 0x0D

int isTransformed (char *input, char *output);

int main()
{
	char input[SLEN], output[SLEN];

	printf ("\r Input: ");
	scanf("%s", input);

	printf ("\r Output: ");
	scanf("%s", output);

	printf ("\r %s\r\n", isTransformed (input, output)? "YES": "NO");

	return 0;
}

/*
 * checks if transformation is correct or not 
 * assume max string len is SLEN
 * destroys input and output, so copy and pass
 */
int isTransformed (char *input, char *output)
{
	int i, j;

	for (i = 0; input[i] != '\0'; i++)
	{
		for (j = 0; output[j] != '\0'; j++)
		{
			if (input[i] == output[j]) 
			{
				input[i] = output[j] = NON_PRINT_CHAR;
				break;
			}
		}

		if (input[i] != NON_PRINT_CHAR)
			return FALSE;
	}

	for (j = 0; output[j] != '\0'; j++)
	{
		if (output[j] != NON_PRINT_CHAR)
			return FALSE;
	}

	return TRUE;
}
