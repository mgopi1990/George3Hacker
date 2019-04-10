/*
 * You are to form the max possible time using 6 digits from a set of 9 digits entered by the user. 
 * and each digit can be used only once at a time and the time range is from 00:00:01 to 12:00:00 
 *
 * Example: 
 * between 00:00:01 and 12:00:00 
 * Input: 1 2 3 9 4 0 0 0 0
 *   12:49:30 -> but its bigger than 12:00:00
 *   10:49:32 -> this is the MAX :P 
 *
 * */

#include <stdio.h>

#define MIN_TIME "00:00:01"
#define MAX_TIME "12:00:00"

#define INP_MAX_LEN 10

#define NUM(x) ((x)&0x0F)
#define STR(x) ((x)|0x30)

#define MSB(x) ((x)/10)
#define LSB(x) ((x)%10)

#define SEC_IN_HOUR 3600
#define SEC_IN_MIN  60
#define SEC(x)   ((x)->hour * SEC_IN_HOUR + (x)->min * SEC_IN_MIN + (x)->sec)

#define NOT_FOUND -1

typedef struct time_ 
{
    int hour, min, sec;
}time;

/* returns index of the found digit, and sets - in that place 
 * if not returns -1 
 */
int find_return_digit_in_string (char digit, char *string)
{
    int i;
    for (i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == digit)
        {
            string[i] = '-';
            return i; 
        }
    } 
    return NOT_FOUND;
}

int time_from_string(char *string, time *t)
{
    int i, hour, min, sec; 

#ifndef SKIP_UNWANTED_CHECK
    if (string[8] != '\0')
        return 0;

    if ((string[2] != ':') || (string[5] != ':'))
        return 0;

    for (i = 0; string[i] != '\0'; i++)
    {
        if (string[i] == ':')
            continue;
    
        if (!(string[i] >= '0' && string[i] <= '9'))
            return 0;
    }    
#endif

    hour = NUM(string[0]) * 10 + NUM(string[1]);
    min  = NUM(string[3]) * 10 + NUM(string[4]);
    sec  = NUM(string[6]) * 10 + NUM(string[7]);

#ifndef SKIP_UNWANTED_CHECK
    if (hour > 12)
        return 0;

    if (min > 60)
        return 0;
    
    if (sec > 60)
        return 0;
#endif


    t->hour = hour; 
    t->min  = min; 
    t->sec  = sec; 

    return 1;
}

int time_to_string(int hour, int min, int sec, char *string)
{
    /* construct string from time t 
     * sizeof(string) > 9 
     */
    string[0] = STR(MSB(hour));
    string[1] = STR(LSB(hour));
    string[2] = ':';
    string[3] = STR(MSB(min));
    string[4] = STR(LSB(min));
    string[5] = ':';
    string[6] = STR(MSB(sec));
    string[7] = STR(LSB(sec));
    string[8] = '\0';

    return 1;
}

int find_big_time (char *digits, char *str_min_time, char *str_max_time, char *str_big_time)
{
    time min_time, max_time;
    int hour, min, sec;
    int min_time_sec, max_time_sec;
    int index[6]; /* incase we want to write back the char to the digits[] */
    int i = 0;

#ifndef SKIP_UNWANTED_CHECK
    for (i = 0; digits[i] != '\0'; i++)
    {
        if (!(digits[i] >= '0' && digits[i] <= '9'))
        {
            printf ("\r [ERROR] [%s,%d] Invalid input\r\n", __FUNCTION__, __LINE__); 
            return 0;
        }
    }    
#endif

    if(!time_from_string(str_min_time, &min_time))
    {
        printf ("\r [ERROR] [%s,%d] Invalid min_time\r\n", __FUNCTION__, __LINE__); 
        return 0;
    }

    if (!time_from_string(str_max_time, &max_time))
    {
        printf ("\r [ERROR] [%s,%d] Invalid max_time\r\n", __FUNCTION__, __LINE__); 
        return 0;
    }

    min_time_sec = SEC(&min_time);
    max_time_sec = SEC(&max_time);

#ifndef SKIP_UNWANTED_CHECK
    if (min_time_sec > max_time_sec)
    {
        printf ("\r [ERROR] [%s,%d] min_time > max_time \r\n", __FUNCTION__, __LINE__); 
        return 0;
    }
#endif

    for (hour = max_time.hour; hour >= min_time.hour; hour--)
    {
        if ((index[0] = find_return_digit_in_string(STR(MSB(hour)), digits)) == NOT_FOUND)
        {
            hour -= LSB(hour);
            continue;
        } 

        if ((index[1] = find_return_digit_in_string(STR(LSB(hour)), digits)) == NOT_FOUND)
        {
            digits[index[0]] = STR(MSB(hour));
            continue;
        }

        for (min = max_time.min; min >= min_time.min; min--)
        {
            if ((index[2] = find_return_digit_in_string(STR(MSB(min)), digits)) == NOT_FOUND)
            {
                min -= LSB(min);
                continue;
            } 

            if ((index[3] = find_return_digit_in_string(STR(LSB(min)), digits)) == NOT_FOUND)
            {
                digits[index[2]] = STR(MSB(min));
                continue;
            }

            for (sec = max_time.sec; sec >= min_time.sec; sec--)
            {
                if ((index[4] = find_return_digit_in_string(STR(MSB(sec)), digits)) == NOT_FOUND)
                {
                    sec -= LSB(sec);
                    continue;
                } 

                if ((index[5] = find_return_digit_in_string(STR(LSB(sec)), digits)) == NOT_FOUND)
                {
                    digits[index[4]] = STR(MSB(sec));
                    continue;
                }

                time_to_string(hour, min, sec, str_big_time);
                return 1; 
            }

            /* return the digits we took wrongly :P */
            digits[index[2]] = STR(MSB(min));
            digits[index[3]] = STR(LSB(min));
        } 

        /* return the digits we took wrongly :P */
        digits[index[0]] = STR(MSB(hour));
        digits[index[1]] = STR(LSB(hour));
    }
 
    printf ("\r [ERROR] [%s,%d] No time construction possible for given input \r\n", __FUNCTION__, __LINE__); 
    return 0;  
}

int main()
{
    char input[INP_MAX_LEN];
    char output[10];

    printf ("\r Enter input: ");
    fgets(input, INP_MAX_LEN, stdin); 

    if (!find_big_time (input, MIN_TIME, MAX_TIME, output))
        return -1;

    printf ("\r %s\r\n", output); 
    return 0;
}
