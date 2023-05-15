#include "shell.h"

#define MAX_COMMAND_LENGTH 100


pid_t pid;


/**
 * remove_newline - removes new line
*/
void remove_newline(char* str) 
{
    int length = strlen(str);
    if (str[length - 1] == '\n') 
    {
        str[length - 1] = '\0';
    }
}
/**
 * execute_command - 
*/
void execute_command(char* command) 
{
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
        char* args[3];
        args[0] = command;
        args[1] = NULL;

        /* Execute the command */
        if (execvp(command, args) == -1) 
        {
            /* Executable not found */
            fprintf(stderr, "./shell: No such file or directory %s\n", command);
            exit(EXIT_FAILURE);
        }

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

        remove_newline(command);

        /* Execute the command */
        execute_command(command);
    }

    return 0;
}
