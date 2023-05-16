#include "shell.h"

#define MAX_COMMAND_LENGTH 100

pid_t pid;
int status;

/**
 * handle_exit - Function to handle the exit built-in command
 * 
*/
void handle_exit() 
{
    exit(EXIT_SUCCESS);
}

int main_44() {
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

        /* Handle the exit command */
        if (strcmp(command, "exit") == 0) 
        {
            handle_exit();
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
            if (execlp(command, command, NULL) == -1) 
            {
                /* Executable not found */
                perror("execlp");
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
