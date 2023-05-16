#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10


pid_t pid;
char *token;
char *path;
char *path_copy;
char *dir;
int command_found;
/**
 * main - parses the command arguments, executes the command, 
 * and handles the end-of-file condition
*/
int main_33() {
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];

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

        /* Parse the command line into arguments */
        *token = strtok(command, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGUMENTS - 1) 
        {
            arguments[i++] = token;
            token = strtok(NULL, " ");
        }
        arguments[i] = NULL;

        /* Check if the command exists in the PATH */
        *path = getenv("PATH");
        *path_copy = strdup(path);
        *dir = strtok(path_copy, ":");
        command_found = 0;
        while (dir != NULL) {
            char command_path[MAX_COMMAND_LENGTH];
            sprintf(command_path, "%s/%s", dir, command);

            if (access(command_path, X_OK) == 0) {
                command_found = 1;

                /* Fork a child process */
                pid_t pid = fork();

                if (pid < 0) 
                {
                    /* Error occurred while forking */
                    perror("fork");
                    exit(EXIT_FAILURE);
                } 
                else if (pid == 0) 
                {
                    /* Child process */
                    /* Execute the command with arguments */
                    if (execv(command_path, arguments) == -1) 
                    {
                        perror("execv");
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

                    break;
                }
            }

            dir = strtok(NULL, ":");
        }

        if (!command_found) 
        {
            /* Command not found */
            printf("./shell: No such file or directory %s\n", command);
        }

        free(path_copy);
    }

    return 0;
}
