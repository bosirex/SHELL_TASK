#include "shell.h"
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

char *argument;
pid_t pid;
int i;

/**
 * parse_arguments - split the command line into separate arguments
*/
char **parse_arguments(char *command) 
{
    char **arguments = malloc(MAX_ARGUMENTS * sizeof(char *));
    if (!arguments) 
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(argument, strtok(command, " "));
    i = 0;
    while (argument != NULL) 
    {
        arguments[i++] = argument;
        argument = strtok(NULL, " ");
    }
    arguments[i] = NULL;

    return arguments;
}
/**
 * execute_command - execute the command using execvp()
*/
void execute_command_3(char **arguments) 
{
    execvp(arguments[0], arguments);
    fprintf(stderr, "./shell: No such file or directory %s\n", arguments[0]);
    exit(EXIT_FAILURE);
}
/**
 * main - parses the command arguments, executes the command, 
 * and handles the end-of-file condition
*/
int main_3() 
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
            /* Parse the command arguments */
            char **arguments = parse_arguments(command);
            /* Execute the command */
            execute_command(arguments);
            /* This code is executed only if exec fails */
            exit(EXIT_SUCCESS);
        } 
        else 
        {
            /* Parent process */
            /* Wait for the child process to finish */
            int status;
            if (waitpid(pid, &status, 0) == -1) 
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }

    return 0;
}
