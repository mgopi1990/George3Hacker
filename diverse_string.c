/*
 * We consider alphabet with only three letters: 'a', 'b' and 'c'. 
 * A string is called diverse if no three consecutive letters are the same. 
 * In other words, a diverse string may not contain any of the strings 
 * 'aaa', 'bbb', or 'ccc'. 
 * 
 * Write a function,
 *  string_diverse (int A, int B, int C);
 * 
 * that given three integers A, B and C, returns any longest possible diverse 
 * string containing at most A letters 'a', at most B letters 'b' and at most 
 * C letters 'c'. If there is no possibility of building any string, return 
 * empty string. 
 * 
 * Example:
 * 
 * 1. Given A=6, B=1 and C=1, our function may return, 'aabaacaa'. 
 * Note that 'aacaabaa' would also be a correct answer. 
 * Your function may return any correct answer.
 * 
 * 2. Given A=1, B=3, and C=1, your function ay return 'abbcb', 'bcbab', 'bacbb' 
 * or any serveral other strings.
 * 
 * 3. Given A=0, B=1 and C=8, your function should return 'ccbcc' which is the 
 * only correct answer for this case.
 * 
 * Assume that,
 *  A,B,C are integers within the range [0..100],
 *  A+B+C > 0
 * 
 * In your solution focus on correctness. 
 * The performance of your solution will not be the focus of the assessment. 
 * 
 */

#include <stdio.h>

#define MAX_N	10
#define DIV_N	2

int string_diverse (int A, int B, int C, char *str);

#ifdef UNIT_TEST
 #define PASS 1
 #define FAIL 0
 
 int unit_test (int (*test_func)(int, int, int, char *));
#endif

int main()
{

#ifdef UNIT_TEST
#endif 
	return 0;
}

#ifdef UNIT_TEST
int unit_test_str (int A, int B, int C, char *str)
{
	int a, b, c, i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == 'A')
			a++;
		else if (str[i] == 'B')
			b++;
		else if (str[i] == 'C')
			c++;
		else
			return FAIL;
	}

	if (a > A)
		return FAIL;

	if (b > B)
		return FAIL;

	if (c > C)
		return FAIL;

	

	return PASS;
}

int unit_test (int (*test_func)(int, int, int, char *))
{
	int i, j, k, result, uno;
	char str[MAX_N * 3 +1];

	uno = 1;
	for (i = 0; i < MAX_N; i++)
	{
		for (j = 0; i < MAX_N; i++)
		{
			for (k = 0; k < MAX_N; k++)
			{
				test_func (i, j, k, str);	
				result = unit_test_str (i, j, k, str);	

				printf ("\r%d,%d,%d,%d,%s,%s\r\n", 
						uno++, i, j, k, str, 
						result?"PASS":"FAIL");

			}
		}
	}
}

#endif
