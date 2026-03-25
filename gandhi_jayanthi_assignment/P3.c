/*
 * P3.
 * Done on 01-Sep-2013; Gandhi Jayanthi ME CSE linux system call assignment;
 *
 * Let us consider a situation in which the processes are forked in the following way.
 * C2 is child of C1, C3 and C4 are children of C2, C5, C6 and C7 are children of C3.
 * Given a string as input, the program prints 4 outputs.
 * These 4 outputs are by processes C4, C5, C6, and C7.
 * Arrow marks indicate the parent child relationship.
 * The communication among them is through message queues.
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/signal.h>


#define MAX_STR_LEN 80
/* Some Random ID to make the queue unique */
#define MSG_ID_KEY 1678

enum 
{
    MSG_TO_C2 = 1,
    MSG_TO_C3,
    MSG_TO_C4,
    MSG_TO_C5,
    MSG_TO_C6,
    MSG_TO_C7
};

enum
{
    SUCCESS = 0,
    FAILURE = -1
};

typedef struct
{
    long msgtype;
    char msgtext[MAX_STR_LEN];
}msgbuf;

int C1_process(); /*C1 Process: converts string to lower case and pass to C2*/
int C2_process(); /*C2 Process: appends C2 at string end and sends to C3, C4*/
int C3_process(); /*C3 process: adds C3 to beginning of text and pass it to C5, C6, C7 */
int C4_process(); /*C4 process: converts 4th char to upper case and prints */
int C5_process(); /*C5 process: converts 5th char to upper case and prints */
int C6_process(); /*C6 process: converts 6th char to upper case and prints */
int C7_process(); /*C7 process: converts 7th char to upper case and prints */
int HelperProcess (int msg_type, int index); /* the ideal/original C4, C5, C6, C7 process */


/* global data */
msgbuf buf;
char *inp_string = buf.msgtext;
int msqid = 0;

int main()
{
    printf ("\r Enter string: ");
    scanf("%[^\n]s", inp_string);

    if (strlen (inp_string) >= (MAX_STR_LEN - 4)) /* reserving 4 spaces for appending 'C2' and 'C4' */
    {
        printf ("\r [ERROR] C1: String is too big to process\r\n");
        return FAILURE;
    }

    if ((msqid = msgget (MSG_ID_KEY, 0644 | IPC_CREAT)) == -1)
    {
        printf ("\r [ERROR] C1: Unable to create message queue\r\n");
        return FAILURE;
    }

    C1_process ();
    return SUCCESS;
}

/* Converts all char to lowercase, and passes it to C2 */
int C1_process()
{
    pid_t c2;
    int i = 0;

    /* converting string to lowercase (C1) */
    for (i = 0; inp_string[i] != '\0'; i++)
    {
        inp_string[i] = tolower(inp_string[i]);
    }

    c2 = fork();
    if (c2 == 0)
    {
        /* In Child C2's context */
        C2_process();
        return SUCCESS;
    }
    else
    {
        buf.msgtype = MSG_TO_C2;
        if (msgsnd (msqid, (msgbuf *) &buf, sizeof (buf.msgtext), 0) < 0)
        {
            printf ("\r [ERROR] C1: Unable to send message to msg queue\r\n");
            kill (c2, SIGTERM); /* Terminating Child, incase of FAILURE */
            return FAILURE;
        }
        
        printf ("\r C1: %s\r\n", inp_string);
        wait (NULL);

        if (msgctl (msqid, IPC_RMID, NULL) == -1)
        {
            printf ("\r [ERROR] C1: Unable to send remove msg queue\r\n");
            return FAILURE;
        }
    }
    return SUCCESS;
}

/* Appends C2 at end of string and passes it to C3, C4 */
int C2_process()
{
        pid_t c3, c4;
        
        if (msgrcv (msqid, (msgbuf *) &buf, sizeof (buf.msgtext), 
                    MSG_TO_C2, 0) < 0)
        {
            printf ("\r [ERROR] C2: Unable to recieve message from msg queue\r\n");
            return FAILURE;
        }

        strcat (inp_string, "C2");
        printf ("\r C2: %s\r\n", inp_string);

        c3 = fork();
        if (c3 == 0)
        {
            /* Child C3's context.*/
            C3_process();
            return SUCCESS;
        }
        else
        {
            c4 = fork();
            if (c4 == 0)
            {
                /* Child C4's context */
                C4_process();
                return SUCCESS;
            }
            else 
            {
                buf.msgtype = MSG_TO_C3;
                if (msgsnd (msqid, (msgbuf *) &buf, sizeof (buf.msgtext), 0) < 0)
                {
                    printf ("\r [ERROR] C2: Unable to send message to msg queue for C3\r\n");
                    kill (c3, SIGTERM); /* Terminating Child, incase of FAILURE */
                    kill (c4, SIGTERM); /* Terminating Child, incase of FAILURE */
                    return FAILURE;
                }

                buf.msgtype = MSG_TO_C4;
                if (msgsnd (msqid, (msgbuf *) &buf, sizeof (buf.msgtext), 0) < 0)
                {
                    printf ("\r [ERROR] C2: Unable to send message to msg queue for C4\r\n");
                    kill (c3, SIGTERM); /* Terminating Child, incase of FAILURE */
                    kill (c4, SIGTERM); /* Terminating Child, incase of FAILURE */
                    return FAILURE;
                }

                wait (NULL);  /* As we have spawned 2 childs */
                wait (NULL);
            }
        }
        return SUCCESS;
}

/* Appends C3 to beginning of string,
 * spawns C5, C6 and C7.
 * Unwanted confusion due to excessive nesting avoided
*/
int C3_process()
{
    pid_t c5, c6, c7;
    int len, i;

    if (msgrcv (msqid, (msgbuf *) &buf, sizeof (buf.msgtext), 
                MSG_TO_C3, 0) < 0)
    {
        printf ("\r [ERROR] C3: Unable to recieve message from msg queue\r\n");
        return FAILURE;
    }

    len = strlen (inp_string);
    /* shifting string two steps to right 
     * to insert new text
     */
    for (i = len; i >= 0; i--)
    {
        inp_string[i + 2] = inp_string[i];
    }
    /* Adding C3 at beginning of string */
    inp_string[0] = 'C';
    inp_string[1] = '3';

    printf ("\r C3: %s\r\n", inp_string);

    c5 = fork();
    if (c5 == 0)
    {
        /* Child C5's context.*/
        C5_process();
        return SUCCESS;
    }

    c6 = fork();
    if (c6 == 0)
    {
        /* Child C6's context. */
        C6_process();
        return SUCCESS;
    }

    c7 = fork();
    if (c7 == 0)
    {
        /* Child C7's context */
        C7_process();
        return SUCCESS;
    }
 
    buf.msgtype = MSG_TO_C5;
    if (msgsnd (msqid, (msgbuf *) &buf, sizeof (buf.msgtext), 0) < 0)
    {
        printf ("\r [ERROR] C3: Unable to send message to msg queue for C5\r\n");
        kill (c5, SIGTERM); /* Terminating Child, incase of FAILURE */
        kill (c6, SIGTERM); 
        kill (c7, SIGTERM); 
        return FAILURE;
    }

    buf.msgtype = MSG_TO_C6;
    if (msgsnd (msqid, (msgbuf *) &buf, sizeof (buf.msgtext), 0) < 0)
    {
        printf ("\r [ERROR] C3: Unable to send message to msg queue for C6\r\n");
        kill (c5, SIGTERM); /* Terminating Child, incase of FAILURE */
        kill (c6, SIGTERM);
        kill (c7, SIGTERM);
        return FAILURE;
    }

    buf.msgtype = MSG_TO_C7;
    if (msgsnd (msqid, (msgbuf *) &buf, sizeof (buf.msgtext), 0) < 0)
    {
        printf ("\r [ERROR] C3: Unable to send message to msg queue for C7\r\n");
        kill (c5, SIGTERM); /* Terminating Child, incase of FAILURE */
        kill (c6, SIGTERM);
        kill (c7, SIGTERM);
        return FAILURE;
    }

    wait (NULL);  /* As we have spawned 3 childs */
    wait (NULL);
    wait (NULL);
    return SUCCESS;
}

/* Recieves string from parent(C2) and converts 4th char to caps */
int C4_process()
{
    HelperProcess (MSG_TO_C4, 3);
    return SUCCESS;
}

/* Recieves string from parent(C3) and converts 5th char to caps */
int C5_process()
{
    HelperProcess (MSG_TO_C5, 4);
    return SUCCESS;
}

/* Recieves string from parent(C3) and converts 6th char to caps */
int C6_process()
{
    HelperProcess (MSG_TO_C6, 5);
    return SUCCESS;
}

/* Recieves string from parent(C3) and converts 7th char to caps */
int C7_process()
{
    HelperProcess (MSG_TO_C7, 6);
    return SUCCESS;
}

/* This function recieves the string from msqid, 
 * and converts the char at index to uppercase */
int HelperProcess (int msg_type, int index)
{
    if (msgrcv (msqid, (msgbuf *) &buf, sizeof (buf.msgtext), 
                msg_type, 0) < 0)
    {
        printf ("\r [ERROR] C%d: Unable to recieve message from msg queue\r\n", index + 1);
        return FAILURE;
    }

    inp_string[index] = toupper (inp_string[index]); /* No problem, if strlen(inp_string) < index*/
    printf ("\r C%d: %s\r\n", index + 1, inp_string);
    return SUCCESS;
}
