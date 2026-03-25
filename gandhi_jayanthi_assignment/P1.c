/*
 * P1
 * Done on 01-Sep-2013; Gandhi Jayanthi ME CSE linux system call assignment;
 *
 * You are required to create your own version of a UNIX shell. 
 * It repeatedly accepts input from the user and performs necessary steps to execute them. 
 * Write a complete program P1.c that conforms to the following specifications [3]
 * Your shell must run an infinite loop accepting input from the user and running commands 
 * until the user requests to exit by specifying .exit. as input. 
 * Each user input should be treated as a command to be executed. 
 * However, there will be a few special cases that the shell will treat differently described below. 
 * For each command, the shell should spawn a child process to run the command. 
 * The shell should try to run the command exactly as typed. 
 * The shell should notify the user if the requested command is not found and cannot be run. 
 * For each spawned child, print the process ID (PID) before executing the specified command. 
 * It should only be printed once and it should be printed before the output from the command. 
 * By default, the shell should block (wait for the child to exit) for each command. 
 * The shell should evaluate the exit status of the child process and print the conditions under which it exited. 
 * If the last character in the user input was the ampersand (&), the child should be run in the background. 
 * When your background process exits you must print its status like you do for foreground processes. 
 * The shell should take care of leaving no zombie processes in the system.
 * The following commands are special commands (also called built-in commands) that are not to be treated 
 * as programs to be launched. No child process should be spawned.
 * exit . the shell should terminate and accept no further input from the user . 
 * While exiting waits until all children have done their execution.
 * info . the shell should print it.s own process ID, the process ID of it.s parent , 
 * the real user id, the effective user id, the current working directory
 * jobs . outputs the pid and name of each task running in the background.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INP_LEN 80
#define MAX_CMD_ARGS 10
#define MAX_CHILDS 10

enum 
{
    SUCCESS = 0,
    FAILURE = -1
};

typedef struct 
{
    pid_t job_pid;
    char job_cmd[MAX_INP_LEN];
}joblist;

int no_childs = 0;
joblist jobs[MAX_CHILDS];

int del_jobs_table_entry(pid_t pid);
int list_jobs();
int update_jobs_table_entry(pid_t pid, char *cmd);


int main()
{
    char inp_cmd[MAX_INP_LEN], orig_cmd[MAX_INP_LEN], *args[MAX_CMD_ARGS];
    int i, j, k, len, status, bg_flag = 0;
    pid_t child_pid, ret_pid;

    while (1)
    {
        memset (inp_cmd, 0, MAX_INP_LEN);
        bg_flag = 0;    /* resettign bg flag */
        k = 0;          /* index to be used for framing args array*/

        printf ("\r# ");
        scanf ("%[^\n]", inp_cmd);

        getc (stdin);   /* to read the stray '\n' */

        /* Input length validation */
        len = strlen (inp_cmd);
        if (len >= MAX_INP_LEN)
        {
            printf ("\r [ERROR] Input too large to process\r\n");
            return FAILURE;
        }

        strcpy (orig_cmd, inp_cmd);

        /* To detect '&' at end of cmd (background process) */
        for (i = len - 1; i >= 0; i--)
        {
            if (inp_cmd[i] == '&')
            {
                inp_cmd[i] = ' '; /* removing & */
                bg_flag = 1;      /* enabling bg flag */
                break;
            }
            else if (inp_cmd[i] == ' ')
            {
                continue;
            }
            else
            {
                bg_flag = 0;
                break;
            }
        }

        /* Removes extra spaces to avoid exec failures */
        for (i = 0; inp_cmd[i] != '\0'; i++)
        {
            if (inp_cmd[i] == ' ' && (inp_cmd[i + 1] == ' '))
            {
                for (j = i; inp_cmd[j] != '\0'; j++)
                {
                    inp_cmd[j] = inp_cmd[j + 1];
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
        
        /* Parsing input command */
        i = k = 0; 
        args[k++] = inp_cmd;
        while (1)
        {
            if (inp_cmd[i] == ' ' || inp_cmd[i] == '\0')
            {
                if (inp_cmd[i] == '\0')
                {
                    args[k] = NULL; 
                    break;
                }

                args[k++] = &(inp_cmd[i + 1]);

                if (k > MAX_CMD_ARGS)
                {
                    printf ("\r [ERROR] Too many tokens to process\r\n");
                    k--; 
                    break; 
                }

                args[k] = NULL; 
                inp_cmd[i] = '\0';
            }
            
            i++;
        }

        if (strcmp (args[0], "exit") == 0)
        {
            while (no_childs > 0)
            {
                child_pid = wait(&status);
                printf ("\r [END] process: %d Return status: %d\r\n", child_pid, status);
                del_jobs_table_entry(child_pid);
            }
            return SUCCESS;
        }
        else if (strcmp (args[0], "info") == 0)
        {
            printf ("\r Own PID          : %d\r\n", getpid());
            printf ("\r Parent PID       : %d\r\n", getppid());
            printf ("\r Real user ID     : %d\r\n", getuid());
            printf ("\r Relative user ID : %d\r\n", geteuid());
            getcwd(inp_cmd, MAX_INP_LEN);
            printf ("\r Working directory: %s\r\n", inp_cmd);
        }
        else if (strcmp (args[0], "jobs") == 0)
        {
            list_jobs ();
        }
        else
        {
            while ((child_pid = waitpid (-1, &status, WNOHANG)) > 0)
            {
                printf ("\r [END] process: %d Return status: %d\r\n", child_pid, status);
                del_jobs_table_entry(child_pid);
            }
       
            /* incase the user just presses enter without doing anything */
            if (strlen (inp_cmd) == 0)
            {
                continue; 
            }

            child_pid = fork();
            if (child_pid == 0)
            {
                /* Spawn child */

                if (execvp (args[0], args) < 0)
                {
                    printf ("\r [ERROR] Exec failed. Error no: %d\r\n", errno);
                    return FAILURE;
                }

                return SUCCESS;
            }
            else
            {
                printf ("\r [NEW] Child Spawned. PID: %d\r\n", child_pid);

                if (bg_flag == 1)
                {
                    /* background flag is enabled 
                     * no need to wait for child to return.
                     * Just update the job table.
                     */ 
                    update_jobs_table_entry(child_pid, orig_cmd);
                }
                else
                {
                    while (1) /* to wait till we recieve the correct process's status */
                    {
                        ret_pid = wait (&status);

                        if (ret_pid == child_pid)
                        {
                           /* matches our process */
                            printf ("\r [END] process: %d Return status: %d\r\n", child_pid, status);
                            
                            break; /* to escape from blocking wait() */
                        }
                        else
                        {
                            /* some background process has terminated */
                            printf ("\r [END] process: %d Return status: %d\r\n", child_pid, status);
                            del_jobs_table_entry(child_pid);
                        }
                    }
                }

            }

        }
    }

    return SUCCESS;
}

/* lists the jobs */
int list_jobs ()
{
    int i;

    printf ("\r PID\t COMMAND\r\n");
    for (i = 0; i < no_childs; i++)
    {
        printf ("\r %d\t%s\r\n", jobs[i].job_pid, jobs[i].job_cmd);
    }
    printf ("\r %d jobs in queue\r\n", no_childs);

    return SUCCESS;
}

/* deletes an entry in job table */
int del_jobs_table_entry(pid_t pid)
{
    int i, j = no_childs, k;

    for (i = 0; i < j; i++)
    {
        if (jobs[i].job_pid == pid)
        {
            for (k = i; k < j; k++)
            {
                jobs[i].job_pid = jobs[i + 1].job_pid;
                strcpy (jobs[i].job_cmd, jobs[i + 1].job_cmd);
            }
            jobs[no_childs - 1].job_pid = 0;
            memset (jobs[no_childs - 1].job_cmd, 0, MAX_INP_LEN); 
            no_childs--;
            return SUCCESS;
         }
    }
    return FAILURE;
}

int update_jobs_table_entry(pid_t pid, char *cmd)
{
    int i;

    if (no_childs >= MAX_CHILDS)
    {
            printf ("\r [ERROR] JOB queue is full\r\n");
            return FAILURE;
    }

    jobs[no_childs].job_pid = pid;
    strcpy (jobs[no_childs].job_cmd, cmd);
    no_childs++;
    return SUCCESS;
}
