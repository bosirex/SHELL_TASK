#include "shell.h"

#define MAX_COMMAND_LENGTH 100


void execute_command(char *command) 
{
    pid_t pid;
    int status;
    char *args[] = {command, NULL};

    pid = fork();

    if (pid < 0) 
    {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) 
    {

        if (execvp(command, args) < 0) 
        {
            perror("Command execution failed");
            exit(1);
        }
    } 
    else 
    {
        while (wait(&status) != pid);
    }
}

int main_exit() 
{
    char command[MAX_COMMAND_LENGTH];
    char *path = getenv("PATH");
    char *token;
    char command_path[MAX_COMMAND_LENGTH + 50];

    while (1) 
    {
        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL) 
        {
            printf("\n");
            break;  /* Exit loop on EOF (Ctrl+D) */
        }

        /* Remove trailing newline character */
        command[strcspn(command, "\n")] = '\0';

        /* Check if the command is "exit" */
        if (strcmp(command, "exit") == 0) 
        {
            break;
        }

        /* Tokenize the PATH variable */
        token = strtok(path, ":");

        while (token != NULL) 
        {
            sprintf(command_path, "%s/%s", token, command);

            if (access(command_path, X_OK) == 0) 
            {
                execute_command(command_path);
                break;
            }

            token = strtok(NULL, ":");
        }

        if (token == NULL) 
        {
            printf("./shell: No such file or directory %s\n", command);
        }
    }

    return 0;
}
