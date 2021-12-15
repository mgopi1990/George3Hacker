/*
 * 67. Add Binary
 *
 * Given two binary strings a and b, return their sum as a binary string.
 *
 * Example 1:
 *
 * Input: a = "11", b = "1"
 * Output: "100"
 *
 * Example 2:
 *
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 *
 * Constraints:
 *
 * 1 <= a.length, b.length <= 10^4
 * a and b consist only of '0' or '1' characters.
 * Each string does not contain leading zeros except for the zero itself.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 10^4 given in the puzzle
 * 1 for '\0' and 1 to store carry
 */
#define MAX_STRLEN 10002
#define BIT(x) (0x01 & (x))

typedef struct {
	int sno;
	char a[MAX_STRLEN], b[MAX_STRLEN];
	char sum[MAX_STRLEN];
}testcase;

testcase tc[] = {
{1, "11", "1", "100"},
{2, "1010", "1011", "10101"},
{3, "1111", "1", "10000"},
{4, "0111", "1", "1000"},
{5, "0", "1", "1"}
};


char *addBinary(char *a, char *b) {
	char *max_str = NULL, *min_str = NULL;
	int a_len, b_len, min_len, max_len, remaining, i;
	char *sum = (char *) malloc (sizeof(char) * MAX_STRLEN);
	char op1, op2, carry = 0;

	if (sum == NULL) {
		return NULL;
	}

	/* calculate length for both the strings */
	for (a_len = 0; a[a_len] != '\0'; a_len++);
	for (b_len = 0; b[b_len] != '\0'; b_len++);

	/* move the strings to the end '\0' */
	if (a_len > b_len)
	{
		max_str = &a[a_len-1];
		min_str = &b[b_len-1];
		max_len = a_len;
		min_len = b_len;
	}
	else
	{
		max_str = &b[b_len-1];
		min_str = &a[a_len-1];
		max_len = b_len;
		min_len = a_len;
	}
	sum += max_len-1;

	/* use fuller adder logic to add */
	for (i = 0; i < min_len; i++)
	{
		/* 
		 * use full adder
		 * sum = op1 ^ op2 ^ carry
		 * carry = (op1 & op2) | (op2 & carry) | (op1 & carry) 
		 */
		op1 = BIT(*max_str);
		op2 = BIT(*min_str);	

		*sum = (op1 ^ op2) ^ carry;
		carry = (op1 & op2) | (op2 & carry) | (op1 & carry);

		sum--;
		min_str--;
		max_str--;
	}

	/* take care of the remaining bits */
	while (i < max_len)
	{
		op1 = BIT(*max_str);
		*sum = op1 ^ carry;
		carry = op1 & carry;

		sum--;
		max_str--;
		i++;
	}

	/* it would be one bit off; come back to correct ptr */
	sum++;
	if (carry)
	{
		/* we have carry, right shift the numbers 
		 * and convert it back
		 */
		for (i = max_len; i > 0; i--)
			sum[i] = '0' | sum[i-1];

		sum[0] = '1';
		sum[max_len+1] = '\0';
	}
	else 
	{
		/* convert to string */
		for (i = max_len-1; i >= 0; i--)
			sum[i] |= '0';
		sum[max_len] = '\0';
	}	

	return sum;
}

int main()
{
	int n = sizeof (tc)/sizeof(tc[0]);
	char *sum;
	int i;

	for (i = 0; i < n; i++)
	{
		sum = addBinary(tc[i].a, tc[i].b);
		if (sum)
		{
			if (strcmp(sum, tc[i].sum) != 0)
			{
				printf ("\r FAILED: %d: %s + %s != %s (expected:%s)\r\n",
							tc[i].sno, tc[i].a, tc[i].b, sum, tc[i].sum);
			}
			free (sum);
		}
		else {
			printf ("\r FAILED: %d: %s + %s != (NULL) (expected:%s)\r\n",
							tc[i].sno, tc[i].a, tc[i].b, tc[i].sum);
		}			
	}

	return 0;
}

