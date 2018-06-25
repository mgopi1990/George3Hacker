/*
 * Take an input string parameter and determine 
 * if exactly 3 question marks exist between every pair of numbers that add up to 10. 
 * If so, return true, otherwise return false.
 *
 * Test cases:
 *
 * "arrb6???4xxbl5???eee5" => true
 * "acc?7??sss?3rr1??????5" => true
 * "5??aaaaaaaaaaaaaaaaaaa?5?5" => false
 * "9???1???9???1???9" => true
 * "aa6?9" => false
 *
 */

#include <stdio.h>

#define SUM 10
#define SYMBOL '?'
#define SYMBOL_COUNT 3

#define INP_BUFLEN 50

int check_string(char string[], int sum, char symbol, int symbol_count);

int check_string(char string[], int sum, char symbol, int symbol_count)
{
    int i;
    int num1, num2, count, atleast_once = 0; 

    for (i = 0; string[i] != '\0'; i++)
    {
        if (string[i] >= '0' && string[i] <= '9') 
        {
            num2 = string[i] - '0';
            count = 0;
            break;    
        }
    }
   
    for (;string[i] != '\0'; i++)
    {
        if (string[i] >= '0' && string[i] <= '9')
        {
            num1 = num2;
            num2 = string[i] - '0'; 

            if ((num1 + num2) == sum)
            {
                if (count != symbol_count)
                {
                    return -1;
                }
                atleast_once = 1;
            }
            count = 0;
        } 
        else if (string[i] == symbol)
        {
            count++;
        }
    }

    if (!atleast_once)
        return -1;
    
    return 0;
}

int main()
{
    char input[INP_BUFLEN];
    int i = 0;

    while (1)
    {
        fgets(input, INP_BUFLEN, stdin);

        /* lazy chomp */
        for (i = 0; input[i] != '\0'; i++);
        input[i-1] = '\0';

        if (input[0] == '\0')
            break;

        printf ("\r%s => %s\r\n", input, 
                 (!check_string(input, SUM, SYMBOL, SYMBOL_COUNT))?"true":"false");
    }     
    return 0;
}
