/*
 * P2
 * Done on 01-Sep-2013; Gandhi Jayanthi ME CSE linux system call assignment;
 *
 * A program accepts user input as cmd1|cmd2|cmd3|...|cmdn, where cmd1 . 
 * cmdn indicates n different commands where n is unknown at the compile time. 
 * Input for Cmdi is the output of the cmdi-1. 
 * The program runs each command in a child process and directs the input and 
 * output using the appropriate IPC mechanisms (only pipe/FIFO). 
 * Write a complete program for the above.
 *
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LEN 100
#define MAX_CMD_ARGS 10
enum
{
    SUCCESS = 0,
    FAILURE = -1
};

int main()
{
    pid_t child_pid;
    int i, j, len, n_pipes, nul_flag = 0;
    int *old_pipe_fd, *pipe_fd;
    char inp_cmd[MAX_CMD_LEN];
    char *args[MAX_CMD_ARGS], buf;

    printf ("\r Input: ");
    scanf ("%[^\n]s", inp_cmd);

    /* Input length validation */
    if (strlen (inp_cmd) >= MAX_CMD_LEN)
    {
        printf ("\r [ERROR] Input too large to process\r\n");
        return FAILURE;
    }

    /* Removes extra spaces to avoid exec failures */
    for (i = 0; inp_cmd[i] != '\0'; i++)
    {
        if (inp_cmd[i] == ' ' && (inp_cmd[i + 1] == ' ' || inp_cmd[i + 1] == '|'))
        {
            for (j = i; inp_cmd[j] != '\0'; j++)
            {
                inp_cmd[j] = inp_cmd[j + 1];
            }
            inp_cmd[j] = '\0';
            i--;
        }
        else if (inp_cmd[i] == '|' && inp_cmd[i + 1] == ' ')
        {
            for (j = i + 1; inp_cmd[j] != '\0'; j++)
            {
                inp_cmd[j] = inp_cmd [j + 1];
            }
            inp_cmd[j] = '\0';
            i--;
        }
    }

    /* Removing white space found at first char */
    if (inp_cmd[0] == ' ')
    {
        for (i = 0; inp_cmd[i] != '\0'; i++)
        {
            inp_cmd[i] = inp_cmd[i + 1];
        }
        inp_cmd[i] = '\0';
    }

    /* Truncating the last white space */
    len = strlen (inp_cmd);
    if (inp_cmd[len - 1] == ' ')
    {
        inp_cmd[len - 1] = '\0';
    }


    old_pipe_fd = NULL;
    i = j = 0;
    args[j++] = &(inp_cmd[0]);
    while (1)
    {
        if (inp_cmd[i] == ' ') 
        {
            inp_cmd[i] = '\0';
            args[j++] = &(inp_cmd[i + 1]);
            i++;
            continue;
        }
        else if (inp_cmd[i] == '|' || inp_cmd[i] == '\0')
        {
            if (inp_cmd[i] == '\0')
            {
                nul_flag = 1;
            }
            inp_cmd[i] = '\0';
            args[j++] = NULL;

            pipe_fd = (int *) malloc (sizeof (int) * 2);
            if (pipe_fd == NULL)
            {
                printf ("\r [ERROR] Memory allocation failed\r\n");
                return FAILURE;
            }

            if (pipe (pipe_fd) < 0)
            {
                printf ("\r [ERROR] Pipe creation failed\r\n");
                return FAILURE;
            }


            child_pid = fork();
            if (child_pid == 0)
            {
                /* Child process */

                if (close (1) < 0)     /* closing STDOUT */
                {
                    printf ("\r [ERROR] Close(1) failed\r\n");
                    return FAILURE;
                }

                if (dup2 (pipe_fd[1], 1) < 0) /* associating pipefd[1] for STDOUT */
                {
                    printf ("\r [ERROR] dup failed\r\n");
                    return FAILURE;
                }
                
                if (close (pipe_fd[0]) < 0)   /* closing the other end of pipe */
                {
                    printf ("\r [ERROR] pipe Close failed\r\n");
                    return FAILURE;
                }

                if (execvp (args[0], args) < 0) /* Executes the parsed command */
                {
                    printf ("\r [ERROR] Exec failed\r\n");
                    return FAILURE;
                }

                return SUCCESS; /* exec command will hijack the child 
                                 * this line won't hit.
                                 * But for self-satisfaction its added 
                                 */
            }

            if (close (0) < 0) /* closing STDIN */
            {
                printf ("\r [ERROR] Close STDIN failed\r\n");
                return FAILURE;
            }

            if (dup2 (pipe_fd[0], 0) < 0) /* associating pipefd[0] for STDIN */
            {
                printf ("\r [ERROR] pipe dup failed\r\n");
                return FAILURE;
            }

            if (close (pipe_fd[1]) < 0)
            {
                printf ("\r [ERROR] Pipe Close failed\r\n");
                return FAILURE;
            }

            wait (NULL);
            if (old_pipe_fd != NULL)
            {
                free (old_pipe_fd);
            }

            old_pipe_fd = pipe_fd;
            
            j = 0;
            args[j++] = &(inp_cmd[i + 1]);

            if (nul_flag == 1)
            {
                break;
            }
        }
        i++;
   } 

    while (read (0, &buf, 1) > 0)
    {
        while (write (1, &buf, 1) <= 0);
    }

    free (old_pipe_fd);

    return SUCCESS;
}
