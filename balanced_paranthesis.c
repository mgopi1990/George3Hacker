/*
Check if the parantheses are balanced
*/

#include <stdio.h>

int balancedParantheses(char *str);

int main()
{
	int i;
	char *input[5] = { "(((())))", "))((", "()()())", "()()(", "()(())"};

	for (i = 0; i < 5; i++)
		printf ("\r %s\t%d\r\n", input[i], balancedParantheses (input[i]));

	return 0;
}

int balancedParantheses (char *str)
{
	int i = 0;
	int pair_check = 0;
	for (i = 0; str[i]!='\0'; i++)
	{
		if (str[i] == '(')
			pair_check++;
		else if (str[i] == ')')
			pair_check--;

		if (pair_check < 0)
			return -1;
	}

	if (pair_check == 0)
		return 0;

	return -1;
}
