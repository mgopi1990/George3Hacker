/*
 * Scalar Word Break
 *
 * Given a string A and a dictionary of words B, determine if A can be
 * segmented into a space-seperated sequence of one or more dictionary 
 * words. 
 *
 * Input:
 * The first argument is a string, A.
 * The second argument is an array of strings, B.
 *
 * Output:
 * Return 0/1 (0 for false, 1 for true) for this problem
 *
 * Constraints:
 * 1 <= len(A) <= 6500
 * 1 <= len(B) <= 10000
 * 1 <= len(B[i]) <= 20
 * 
 * Examples:
 * Input 1:
 *  A = "myinterviewtrainer",
 *  B = ["trainer", "my", "interview"]
 *
 *  Output 1:
 *   1
 *
 *  Explanation 1:
 *   Return 1 (corresponding to true) because "myinterviewtrainer" can be segmented as "my interview trainer"
 *
 *  Input 2:
 *   A = "a"
 *   B = [ "aaa" ]
 *
 *  Output 2:
 *   0
 *
 *  Explanation 2:
 *   Return 0 (corresponding to false) because "a" cannot be segmented as "aaa"
 *
 */

/*
 * compile like,
 *  gcc word_break.c -g -DTEST1 
 *  gcc word_break.c -g -DTEST2
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN_A 6500

int wordBreak (char *A, char **B, int n2);
int word_break (char *A, char **B, int n2, int state, int B_offset[]);

int main()
{
#ifdef TEST1
	char A[LEN_A] = "myinterviewmytrainer";
	char *B[] = { "trainer", "my", "myinterview" };

	printf ("%d", wordBreak (A, B, 3));
#endif

#ifdef TEST2
	char A[LEN_A] = "a";
	char *B[] = { "aaa"};

	printf ("%d", wordBreak (A, B, 3));
#endif

    return 0;
}

int wordBreak(char *A, char **B, int n2) {
	int *B_offset = malloc(sizeof (int) *n2);
	if (B_offset == NULL) {
		return 0;
	}
	return (word_break(A, B, n2, 0, B_offset));
}


int word_break (char *A, char **B, int n2, int state, int B_offset[])
{
	int i, j, k, ret_val, len;
	char *ptr = NULL, *ptr2 = NULL;

	if (state >= n2) {
		return 1;
	}

	len = strlen(B[state]);
	ptr = A;
	
	while ((ptr2 = strstr(ptr, B[state])) != NULL) {
		memset (ptr2, ' ', len);

		B_offset[state] = (ptr2 - A);

		ret_val = word_break(A, B, n2, state+1, B_offset);
		if (ret_val == 1) {
			return 1;
		}

		memcpy (ptr2, B[state], len);
		ptr += len;
	}

	return 0;
}
