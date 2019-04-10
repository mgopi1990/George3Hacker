/*
 * aaabbcc  - valid (remove one a)
 * aabbcc   - valid 
 * abbcc    - valid (remove one a)
 * aaaabbcc - invalid (4-a, 2-b, 2-c)
 * aabbbcc  - valid
 * aaa      - invalid
 * string is valid if,
 * 1. equal no of chars, 
 * 2. remove one char makes it valid
 */

#include <stdio.h>
#include <string.h>

#define LEN 50
#define EMPTY_CHAR '.'
int is_string_valid (char *string);

int main()
{
    /* lets assume inp_string wont have '.' EMPTY_CHAR. 
     * We use it for removing char */
    char inp_string[10][LEN] = {"aaabbcc", "aabbcc", "abbcc", "aaaabbcc", "aabbbcc", "aaa", "aaabcc"};
    int i = 0;

    for (i = 0; i < 7; i++)
    {
        printf ("\r %s\t- %s\r\n", inp_string[i], is_string_valid(inp_string[i])?"Valid":"Invalid");
    }
    
    return 0;
}

int is_string_valid (char *inp_string)
{
    char temp_string[LEN];
    char char_list[LEN] = "";
    int i = 0, j = 0, already_present, n, removed, one_less;

    strcpy(temp_string, inp_string); 
    
    n = 0;
    /* simply fill the known char_list */
    for (i = 0; temp_string[i]!= '\0'; i++)
    {
        already_present = 0;
        for (j = 0; j < n; j++)
        {
            if (temp_string[i] == char_list[j])
            {
                already_present = 1;
                break;
            }
        } 

        if (already_present == 0)
        {
            /* add '\0' later */
            char_list[n++] = temp_string[i];

            /* mark empty */
            temp_string[i] = EMPTY_CHAR;
        }
    } 
    char_list[n] = '\0';

    /* there should be atleast two types of char to match */
    if (n <= 1)
        return 0;

    one_less = 1;
    while (1) 
    {
        removed = 0;
        for (j = 0; j < n; j++)
        {
            for (i = 0; temp_string[i] != '\0'; i++)
            {
                if (temp_string[i] == EMPTY_CHAR)
                    continue;

                if (temp_string[i] == char_list[j])
                {
                    temp_string[i] = EMPTY_CHAR;
                    removed++;
                    break;
                }    
            } 
        } 

        if (removed == 0)
        {
            /* string exhausted */
            return 1;
        }
        else if (removed == 1)
        {
            if (one_less)
                return 0;

            /* exactly one char removed */
            for (i = 0; temp_string[i] != '\0'; i++)
            {
                /* Validate if the temp_string became empty */
                if (temp_string[i] != EMPTY_CHAR)
                    return 0;
            }
            
            return 1;
        }
        else if (removed < n)
        {
           if (removed == n-1 && one_less)
                continue;

           return 0; 
        }
        else
            one_less = 0;        
    }

    return 0;        
}

