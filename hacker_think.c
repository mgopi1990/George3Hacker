#include <stdio.h>
#include <string.h>

#define MIN_N 100
#define MAX_N 1000
#define MIN_CHAR_SET_CHAR 'A'
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
                printf ("\r %s\r\n", state->buf);
            }
            else
            {
                think (state);
                state->pos--;
                state->cur_sum -= sum;
            }
        }
    }
}

 int main()
{
#if 0
    char char_set[] = "zyxwvustrqponmlkjihgfedcbaZYXWVUSTRQPONMLKJIHGFEDCBA";
#else
    char char_set[] = "ZYXWVUSTRQPONMLKJIHGFEDCBA";
#endif
    int N = 195;
    think_state state;
#if 0
    printf ("\r passwd: ");
    scanf("%d", &N);
#endif
    if (N < MIN_N || N > MAX_N)
    {
        printf ("\r Invalid Input\r\n");
        return 1;
    }

    memset (&state, 0, sizeof(think_state));
    state.char_set = char_set;
    state.N = N;

    think(&state);

    return 0;
}
