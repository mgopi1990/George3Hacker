#include <stdio.h>

#define MAX_ROW 22
#define MAX_COL 18

#define N_WORDS 20
#define WORD_LEN 20

char words[N_WORDS][WORD_LEN] = {
    "allocation", "double", "recursion",
    "array",      "exit",   "return",
    "boolean",    "float",  "stack",
    "break",      "function","struct",
    "case",       "int",     "switch",
    "char",       "loop",    "typedef",
    "define",     "pointer"
};

char map[MAX_COL][MAX_ROW] = {
"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
"\0SARFHJYARRACGPUINTER\0",
"\0TWIHAXITAOLFLOOTRCDE\0",
"\0AMIBSTRECALLUMECSAOT\0",
"\0CRETGSULCWOORNGUBEUU\0",
"\0LSNFSFFBDJCADECRWRBR\0",
"\0ATATEHFUGJAGRNLTNBLM\0",
"\0CRINQFUOECTPTOFSILIF\0",
"\0OULOORNDEFINEKSCZOVT\0",
"\0LCOIVSCASAOKCXDLIONE\0",
"\0LLOSWITCHBNAEQICXPUP\0",
"\0AZBRRDITSATDAZNTOKOE\0",
"\0KFSUYFOAESACRTTIERSD\0",
"\0DARCHAMLATCHRHNDAEFE\0",
"\0QPEETAOORCTAATYPEDEF\0",
"\0GDRRHODEFINREFLGOCET\0",
"\0ARRGBDNRUTERECURSIOM\0",
"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"};

char *direction[] = {
    "NORTH", "NORTH_EAST", "EAST", "SOUTH_EAST",
    "SOUTH", "SOUTH_WEST", "WEST", "NORTH_WEST"
};
              
enum 
{
    NORTH,
    NORTH_EAST,
    EAST,
    SOUTH_EAST,
    SOUTH,
    SOUTH_WEST,
    WEST,
    NORTH_WEST
};


typedef struct _sol
{
    int x, y, dir;
}sol;

int find_word (char (*map)[MAX_ROW], char *word, sol *ans)
{
    int i, j, k, flag, dir;

    for (i = 1; i < (MAX_COL-1); i++)
    {
        for (j = 1; j < (MAX_ROW-1); j++)
        {
            for (dir = NORTH; dir <= NORTH_WEST; dir++)
            {
                flag = 1;
                switch(dir)
                {
                    case NORTH:
                        for (k = 0; word[k] != '\0'; k++)
                        {
                            if (word[k] == map[i-k][j])
                                continue;
                            flag = 0;
                        }
                        break;

                    case NORTH_EAST:
                        for (k = 0; word[k] != '\0'; k++)
                        {
                            if (word[k] == map[i-k][j+k])
                                continue;
                            flag = 0;
                        }
                        break; 

                    case EAST:
                        for (k = 0; word[k] != '\0'; k++)
                        {
                            if (word[k] == map[i][j+k])
                                continue;
                            flag = 0;
                        }
                        break; 

                    case SOUTH_EAST:
                        for (k = 0; word[k] != '\0'; k++)
                        {
                            if (word[k] == map[i+k][j+k])
                                continue;
                            flag = 0;
                        }
                        break; 

                    case SOUTH:
                        for (k = 0; word[k] != '\0'; k++)
                        {
                            if (word[k] == map[i+k][j])
                                continue;
                            flag = 0;
                        }
                        break; 

                    case SOUTH_WEST:
                        for (k = 0; word[k] != '\0'; k++)
                        {
                            if (word[k] == map[i+k][j-k])
                                continue;
                            flag = 0;
                        }
                        break; 

                    case WEST:
                        for (k = 0; word[k] != '\0'; k++)
                        {
                            if (word[k] == map[i][j-k])
                                continue;
                            flag = 0;
                        }
                        break; 

                    case NORTH_WEST:
                        for (k = 0; word[k] != '\0'; k++)
                        {
                            if (word[k] == map[i-k][j-k])
                                continue;
                            flag = 0;
                        }
                        break; 
                }

                if (flag == 1)
                {
                    ans->x = j;
                    ans->y = i;
                    ans->dir = dir;
                    return 1;
                } 
            }
        }
    }    

    return 0;
}

int main()
{
    int i, j;
    sol ans;

    for (i = 0; i < N_WORDS; i++)
    {
        /* upper case the give string */
        for (j = 0; words[i][j] != '\0'; j++)
        {
            if (words[i][j] >= 'a' && words[i][j] <= 'z')
                words[i][j] &= 0xDF;
        } 
    
        if (find_word (map, words[i], &ans))
            printf ("\r %20s (%02d, %02d) %s\r\n", words[i], ans.x, ans.y, direction[ans.dir]);        
        else
            printf ("\r %20s NOT FOUND\r\n", words[i]);        
    
    }  
}
