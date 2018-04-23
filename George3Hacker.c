/* 
	George the Hacker's code 
	
Simple recursion problem.

George is a deadly hacker ;). 
He has broken into the security systems of one of the reputed organisation to steal Administrator's password. 
However , the IT guys there are smart too. The password is stored in an encrypted format and not in plain text. 
George put up all his reverse engineering skills to crack the passwords. 
He has managed to get an integer N. 
Assuming all password consists of alphabets only (bad practise though), 
the ascii value of each letter of password add to form N. 
Since you are the best programmer in town, 
he asked for your help to write down a program that can generate all possible passwords which George can brute force upon. 
Please help him :D

Input : 100 < N < 10000 Output : all possible passwords that make up N

Sample Input: 195 Sample Output: AAA

Explanation : AAA consists of three letters all being A with ascii value as 65 . 
If we sum them up we get 65+65+65= 195 . No other combination Qualifies.
*/

#include <stdio.h>
#include <string.h>

#define MIN_N 100
#define MAX_N 10000
#define MIN_CHAR_SET_CHAR 'A'
#define ALLOWED_CHAR_SET "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

#define MAX_PWD_LEN ((MAX_N)/(MIN_CHAR_SET_CHAR))

typedef struct s_
{
    int N;
    char *char_set;
    char buf[MAX_PWD_LEN + 1];
    int pos, cur_sum;
}think_state;

void think(think_state *state);

void think(think_state *state)
{
    int i, sum;

#ifdef DEBUG_WANTED
    state->buf[state->pos] = '\0';
	printf ("\r [%s,%d] %d %d %d %s\r\n", __FUNCTION__, __LINE__, 
				state->N, state->cur_sum, state->pos, state->buf);
#endif

    for (i = 0; state->char_set[i] != '\0'; i++)
    {
        sum = state->cur_sum + state->char_set[i];
        if (sum <= state->N)
        {
            state->buf[state->pos++] = state->char_set[i];
            state->cur_sum = sum;

            if (sum == state->N)
            {
                state->buf[state->pos] = '\0';
                printf ("\r  %s\r\n", state->buf);
            }
            else
            {
                think (state);
            }
            state->pos--;
            state->cur_sum -= state->char_set[i]; 
        }
    }
}

int main()
{
    int N;
    think_state state;

    printf ("\r passwd: ");
    scanf("%d", &N);

    if (N < MIN_N || N > MAX_N)
    {
        printf ("\r Invalid Input\r\n");
        return 1;
    }

    memset (&state, 0, sizeof(think_state));
    state.char_set = ALLOWED_CHAR_SET;
    state.N = N;

	printf ("\r Guesses:\r\n");
    think(&state);

    return 0;
}
