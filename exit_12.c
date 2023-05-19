#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_PATH_LENGTH 100


/* Function to execute a command */
void execute_command(char* command) 
{
    pid_t pid;
    int status;
    
    pid = fork();
    if (pid < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {
        /* Child process */
        char path[MAX_PATH_LENGTH];
        char *arguments [2];
        *arguments[1] = command;
        *arguments[2] = NULL;
        /* Check if the command is available in the PATH */
        char *path_env = getenv("PATH");
        char *token = strtok(path_env, ":");
        while (token != NULL) 
        {
            snprintf(path, sizeof(path), "%s/%s", token, command);
            if (access(path, X_OK) == 0) 
            {
                execv(path, arguments);
                break;
            }
            token = strtok(NULL, ":");
        }
        
        /* If the loop completes without finding the command, print an error */
        printf("./shell: No such file or directory %s\n", command);
        exit(EXIT_FAILURE);
    } 
    else 
    {
        /* Parent process */
        waitpid(pid, &status, 0);
    }
}

int main_12() 
{
    char command[MAX_COMMAND_LENGTH];
    
    while (1) 
    {
        /* Display prompt */
        printf("simple_shell$ ");
        
        /* Read command from user */
        if (fgets(command, sizeof(command), stdin) == NULL) 
        {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }
        
        /* Remove trailing newline character */
        command[strcspn(command, "\n")] = '\0';
        
        /* Check if the user wants to exit the shell */
        if (strcmp(command, "exit") == 0) 
        {
            break;
        }
        
        /* Execute the command */
        execute_command(command);
    }
    
    return 0;
}
