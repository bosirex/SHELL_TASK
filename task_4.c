#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int argument_count, exit_code, status;
pid_t pid;

int main_4() 
{
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    char *token;

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

        /* Tokenize the command to separate command and arguments */
        argument_count = 0;
        token = strtok(command, " ");
        while (token != NULL && argument_count < MAX_ARGUMENTS) 
        {
            arguments[argument_count++] = token;
            token = strtok(NULL, " ");
        }
        arguments[argument_count] = NULL;

        /* Handle the exit built-in command */
        if (strcmp(arguments[0], "exit") == 0) 
        {
            /* Check if any argument was provided */
            if (argument_count > 1) 
            {
                /* Convert the argument to an integer */
                exit_code = atoi(arguments[1]);
                exit(exit_code);
            } 
            else 
            {
                exit(EXIT_SUCCESS);
            }
        }

        /* Fork a child process */
        pid = fork();

        if (pid < 0) 
        {
            /* Error occurred while forking */
            perror("fork");
            exit(EXIT_FAILURE);
        } 
        else if (pid == 0) 
        {
            /* Child process */
            /* Execute the command */
            if (execvp(arguments[0], arguments) == -1) 
            {
                /* Executable not found */
                perror("execvp");
                exit(EXIT_FAILURE);
            }

            /* This code is executed only if exec fails */
            exit(EXIT_SUCCESS);
        } 
        else 
        {
            /* Parent process */
            /* Wait for the child process to finish */
            if (waitpid(pid, &status, 0) == -1) 
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
