/* 
	George the Hacker's code 
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
