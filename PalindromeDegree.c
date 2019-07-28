/*

Palidrome Degree.

lets call the panidrome degree of string s such a maximum number k, for which s is k-palidrome. For example, 'abaaba' has degree equals to 3.

You are given a string. Your task is to find the sum of the palindrome degrees of all its prefixes.

Input:
The first line of the input data contains a non-empty string, consisting of letters and digits. The length of the string does not exceed 5106. The string is case-sensitive.

Output:
Output the only number the sum of the palindrome degrees of all the string's prefixes.

TEST CASE 1:

INPUT
abacaba

OUTPUT
6

EXPLANATION
a - 1
ab - 0
aba - 2
abac - 0
abaca - 0
abcab - 0
abacaba - 4
SUM = 6

TEST CASE 2:
INPUT
CCeCeCCCee

OUTPUT
4

EXPLANATION

C - 1
CC - 1
CCe - 0
CCeC - 0
CCeCe - 0
CCeCeC - 0
CCeCeCC - 2
CCeCeCCC - 0
CCeCeCCCe - 0
CCeCeCCCee - 0
SUM = 4
*/


#include <stdio.h>

#ifdef DEBUG_WANTED
#include <string.h>
#endif

#define MAX_SLEN 5107

/* assume its only A-Z, a-z, and 0-9 */
#define COUNT 64

#define TRUE	1
#define FALSE	0

int isPalindrome (char *string, int len);
int PalindromeDegree (char *string);

int main()
{
	char input[MAX_SLEN];
	int ans;

	scanf("%s", input);
	ans = PalindromeDegree(input);

#ifdef DEBUG_WANTED
	printf ("\r [%s,%d] %s %d\r\n", __FUNCTION__, __LINE__, input, ans);
#endif
	printf ("%d\r\n", ans);

	return 0;
}

int isPalindrome (char *string, int len)
{
	int i = 0;

	for (i = 0; i < len/2; i++)
	{
		if (string[i] != string[len-1 - i])
			return FALSE;
	}

#ifdef DEBUG_WANTED
	{
		char sub_string[MAX_SLEN];
		strncpy(sub_string, string, len);	
		sub_string[len+1] = '\0';
		printf ("\r [%s,%d] %3d %s\r\n", 
				__FUNCTION__, __LINE__, len, sub_string);
	}
#endif
	return TRUE;
}

int PalindromeDegree (char *string)
{
	int i, j, k, uniq_count = 0, count = 0, sum = 0;
	char unique_chars[COUNT+1];

#ifdef DEBUG_WANTED
	memset(unique_chars, 0, COUNT+1);
#endif

	for (i = 0; string[i] != '\0'; i++)
	{
		if(isPalindrome(string, i+1))
		{
			while (j < ((i+1)/2 + (i+1)%2))
			{
				for (k = 0; k < uniq_count; k++)
				{
					if (unique_chars[k] == string[j])
						break;
				}

				if (k == uniq_count) {
					unique_chars[uniq_count++] = string[j];
				}
 				j++;
			}
#ifdef DEBUG_WANTED
	printf ("\r [%s,%d] counted_till: %3d count:%d unique:%s\r\n", 
				__FUNCTION__, __LINE__, j, uniq_count, unique_chars);
#endif
			sum += uniq_count;
		}
	}

	return sum;
}
