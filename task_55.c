#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int i, status;
pid_t pid;
/**
 * handle_exit - Function to handle the built-in exit command
*/
void handle_exit() 
{
    exit(EXIT_SUCCESS);
}

/**
 * handle_en - Function to handle the built-in env command
 */ 
void handle_env(char **environ) 
{
    /* Print each environment variable */
    for (i = 0; environ[i] != NULL; i++) 
    {
        printf("%s\n", environ[i]);
    }
}

int main_55(int argc, char *argv[], char *environ[]) 
{
    char command[MAX_COMMAND_LENGTH];
    (void)argc;

    while (1) 
    {
        void display_prompt();

        /* Read the user input command */
        if (fgets(command, sizeof(command), stdin) == NULL) 
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the trailing newline character */
        command[strcspn(command, "\n")] = '\0';

        /* Check if the command is exit */
        if (strcmp(command, "exit") == 0) 
        {
            handle_exit();
        }

        /* Check if the command is env */
        if (strcmp(command, "env") == 0) {
            handle_env(environ);
            continue;
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
            if (execvp(command, argv) == -1) 
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
