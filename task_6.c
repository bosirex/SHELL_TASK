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
 * read_command - reads the user input command,
 * and the find_executable() function searches for 
 * the executable in the PATH environment variable
*/
char* read_command() 
{
    static char command[MAX_COMMAND_LENGTH];
    int index = 0;
    char c;

    while ((c = getchar()) != '\n') 
    {
        if (index >= MAX_COMMAND_LENGTH - 1) 
        {
            fprintf(stderr, "Command too long\n");
            exit(EXIT_FAILURE);
        }

        command[index++] = c;
    }

    command[index] = '\0';

    return command;
}

char* find_executable(char* command) 
{
    char* path = getenv("PATH");
    char* token = strtok(path, ":");
    char* executable = (char*)malloc(MAX_COMMAND_LENGTH);

    while (token != NULL) 
    {
        snprintf(executable, MAX_COMMAND_LENGTH, "%s/%s", token, command);

        if (access(executable, X_OK) == 0) 
        {
            return executable;
        }

        token = strtok(NULL, ":");
    }

    free(executable);
    return NULL;
}
/**
 * execute_command - forks a child process, finds the executable, 
 * and executes it using execve()
*/
int execute_command(char* command) 
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {
        // Child process
        char* executable = find_executable(command);

        if (executable == NULL) 
        {
            fprintf(stderr, "./shell: No such file or directory %s\n", command);
            exit(EXIT_FAILURE);
        }

        if (execve(executable, (char* const*)&command, environ) == -1) 
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
        // This code is executed only if exec fails
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        // Parent process
        int status;
        if (waitpid(pid, &status, 0) == -1) 
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        return status;
    }
}
/**
 * main - checks for the built-in commands "exit" and "env" and 
 * executes them accordingly
*/
int main() 
{
    while (1) 
    {
        display_prompt();
        char* command = read_command();

        if (strcmp(command, "exit") == 0) 
        {
            exit(EXIT_SUCCESS);
        } 
        else if (strcmp(command, "env") == 0) 
        {
            extern char** environ;
            for (char** env = environ; *env != NULL; env++) 
            {
                printf("%s\n", *env);
            }
        } 
        else 
        {
            int status = execute_command(command);
            printf("Exit status: %d\n", status);
        }
    }

    return 0;
}
