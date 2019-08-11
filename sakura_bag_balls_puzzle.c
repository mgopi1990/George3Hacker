/*
 *
 * Sakura, who is very good friend of Naruto, gave him a question. 
 * Thinking that Naruto is stupid and will not be able to answer. 
 * As Naruto is hard-working he managed to solve it easily without 
 * any issues. Now, check if you can solve it without any difficulty.
 * 
 * Problem: 
 * You are given X empty bags and you have to fill them with C balls, 
 * where C is always a multiple of X. Now, there are only two ways in 
 * which you have to fill the bags. Also, you can only fill X balls in 
 * one minute. 
 * 
 * 1- One way is to put a ball in each bag, and 
 * 
 * 2- other way is to first choose the bag with smallest number of 
 * balls and fill it with X balls.
 * 
 * Now, you have to figure out, can the distribution of balls can be 
 * different by using both the methods
 * 
 * Constraints: 
 * 
 * 1 <= T <= 200
 * 1 <= X <= C <= 10^18
 * 
 * X is divisible by C.
 * 
 * Explanation: (for first two testcases)
 * 1- final distribution by both cases are:
 * a)           b)
 *              O   
 * O O          O
 * O O          O O
 * O O          O O
 * O O          O O
 * O O          O O
 * Hence, the answer is YES.
 * 
 * 2- In next case both distributions will be same.
 * 
 * Input Format:
 * The first line of the input contains a single integer T denoting the number of test cases. 
 * The description of T test cases follows.
 * The first and only line of each test case contains two space-separated integers C and X.
 * 
 * Output Format:
 * For each test case, print a single line containing the string "YES" 
 * if the final distributions of balls can be different or "NO" if they will be the same (without
 * 
 * Test cases: 
 * Input:
 * 4
 * 10 2
 * 1000 1
 * 8 2
 * 2000 10
 * 
 * Output:
 * YES
 * NO
 * NO
 * NO
 * 
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct ques_ {
	int X_empty_bags;
	int C_balls;
}ques;

int sakura_questions(ques **Q, int *T);
int naruto_answers(ques **Q, int *T);

int main()
{
	int T; /* very difficult to see T being used for n */
	ques *q;

	sakura_questions(&q, &T);
	naruto_answers(&q, &T);

	return 0;
}

/* Useless Sakura only knows to ask questions */
int sakura_questions(ques **Q, int *T)
{
	int i, n;
	ques *q;

	scanf ("%d", &n);
	q = malloc(sizeof(ques) * n);
	if (q == NULL)
	{
		*T = 0;
		*Q = NULL;
		return -1;
	}
	
	for (i = 0; i < n; i++)
		scanf ("%d %d", &(q[i].C_balls), &(q[i].X_empty_bags));

	*T = n;
	*Q = q;

	return 0;
}

/*
 * Lets hear what Kurama told Naruto
 * When we fill all the bags one by one, lets assume n balls are there in each bag.
 * So, if we fill each bag, X balls, then for all the bags to be filled, we need X*X balls.
 * so, n should be multiple of X. ie. n%X == 0
 *
 * if n%X == 0, then both approach 1 and 2 will yeild the same result.
 *
 * 1
 * 3 15
 *
 * Approach 1:
 * 
 *  x x x x x
 *  x x x x x
 *  x x x x x
 *
 *  15/3 = 5 balls each bag
 *
 * Approach 2:
 * 
 *  xxx xxx
 *  xxx xxx
 *  xxx
 *
 *  5 % 3 = 2 -> 0 if both approach have same arrangement
 *
 *  YES (Different approach yield different results)
 */
int naruto_answers(ques **Q, int *T)
{
	int i;
	int balls_on_each_bag;
	ques *q = *Q;
	
	for (i = 0; i < *T; i++)
	{
		/* 
		 * Sakura always lies; 
		 * She lied about no. of balls divisible by no. of bags
		 */
		if (q[i].C_balls % q[i].X_empty_bags) 
		{
			printf ("YES\n");
			continue;
		}

		balls_on_each_bag = q[i].C_balls / q[i].X_empty_bags;
		if (balls_on_each_bag % q[i].X_empty_bags)
		{
			printf ("YES\n");
			continue;
		}

		printf ("NO\n");
	}

	free(q);
	*T = 0;
	*Q = NULL;
	return 0;
}
