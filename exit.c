#include "shell.h"
#define MAX_COMMAND_LENGTH 100

int status;
pid_t pid;
char *args[] = {command, NULL};

int execute_command(char *command) 
{
    pid = fork();

    if (pid < 0) 
    {
        /* Error occurred while forking */
        perror("fork");
        return 1;
    } 
    else if (pid == 0) 
    {
        /* Child process */
        /* Execute the command */
        if (execvp(command, args) == -1) 
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

    return 0;
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) 
    {
        printf("$ ");

        /* Read the user input command */
        if (fgets(command, sizeof(command), stdin) == NULL) 
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the trailing newline character */
        command[strcspn(command, "\n")] = '\0';

        /* Check if the command is the exit built-in */
        if (strcmp(command, "exit") == 0) 
        {
            printf("Exiting the shell...\n");
            break;
        }

        /* Fork a child process to execute the command */
        execute_command(command);
    }

    return 0;
}
