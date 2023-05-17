#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

pid_t pid;
int i;
int main_exit() {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_ARGUMENTS];
    char *path = getenv("PATH");
    char *token;
    int status;

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

        /* Split the command line into arguments */
        i = 0;
        token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGUMENTS - 1) 
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        /* Check for the exit built-in command */
        if (strcmp(args[0], "exit") == 0) 
        {
            break;
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
            /* Find the executable in the PATH */
            char *executable = args[0];
            char *full_path = NULL;

            if (strchr(executable, '/') != NULL) 
            {
                /* The executable path is specified */
                full_path = executable;
            } 
            else 
            {
                /* Search the PATH for the executable */
                token = strtok(path, ":");
                while (token != NULL) 
                {
                    snprintf(command, sizeof(command), "%s/%s", token, executable);
                    if (access(command, X_OK) == 0) 
                    {
                        full_path = command;
                        break;
                    }
                    token = strtok(NULL, ":");
                }
            }

            if (full_path == NULL) 
            {
                /* Executable not found */
                printf("%s ./shell: No such file or directory\n", executable);
                exit(EXIT_FAILURE);
            }

            /* Execute the command */
            if (execve(full_path, args, NULL) == -1) 
            {
                /* Exec failed */
                perror("execve");
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
