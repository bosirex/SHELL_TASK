#include "shell.h"

#define MAX_COMMAND_LENGTH 100

pid_t pid;


/**
 * execute_command - handles the execution of the command
*/
int execute_command_4(char *command) 
{
    /* Fork a child process */
    pid = fork();

    if (pid < 0) 
    {
        /* Error occurred while forking */
        perror("fork");
        return -1;
    } 
    else if (pid == 0) 
    {
        /* Child process */

        /* Execute the command */
        if (execvp(command, NULL) == -1) 
        {
            /* Executable not found */
            fprintf(stderr, "./shell: No such file or directory %s\n", command);
            return -1;
        }

        /* This code is executed only if exec fails */
        return 0;
    } 
    else 
    {
        /* Parent process */
        /* Wait for the child process to finish */
        int status;
        if (waitpid(pid, &status, 0) == -1) 
        {
            perror("waitpid");
            return -1;
        }
        return status;
    }
}
/**
 * main - parses the command arguments, executes the command, 
 * and handles the end-of-file condition
*/
int main() 
{
    char command[MAX_COMMAND_LENGTH];

    while (1) 
    {
        display_prompt();

        /* Read the user input command */
        if (fgets(command, sizeof(command), stdin) == NULL) 
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the trailing newline character */
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) 
        {
            // Exit the shell if the command is "exit"
            break;
        }

        int status = execute_command(command);
        if (status == -1) 
        {
            /* An error occurred, display the prompt again */
            continue;
        }
    }

    return 0;
}
