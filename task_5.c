#include "shell.h"

#define MAX_COMMAND_LENGTH 100

/**
 * display_prompt - dispays the prompt
*/
void display_prompt() 
{
    printf("simple_shell$ ");
    fflush(stdout);
}
/**
 * execute_command - handles the execution of the command
*/
void execute_command(char *command, char *args[]) 
{
    pid_t pid = fork();

    if (pid < 0) 
    {
        // Error occurred while forking
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {
        // Child process

        // Execute the command
        if (execvp(command, args) == -1) 
        {
            // Executable not found
            fprintf(stderr, "./shell: No such file or directory %s\n", command);
            exit(EXIT_FAILURE);
        }

        // This code is executed only if exec fails
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        // Parent process

        // Wait for the child process to finish
        int status;
        if (waitpid(pid, &status, 0) == -1) 
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
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

        // Read the user input command
        if (fgets(command, sizeof(command), stdin) == NULL) 
        {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Check if the command is exit
        if (strcmp(command, "exit") == 0) 
        {
            break;
        }

        // Check if the command is env
        if (strcmp(command, "env") == 0) 
        {
            extern char **environ;
            for (int i = 0; environ[i] != NULL; i++) 
            {
                printf("%s\n", environ[i]);
            }
            continue;
        }

        // Fork a child process to execute the command
        char *args[] = {command, NULL};
        execute_command(command, args);
    }

    return 0;
}
