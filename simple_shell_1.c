#include "shell.h"
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

pid_t pid;

int main() {
    char *command = NULL;
    size_t buffer_size = 0;
    ssize_t read;

    while (1) 
    {
        display_prompt();

        /* Read the user input command */
        ssize_t read = getline(&command, &buffer_size, stdin);

        if (read == -1) 
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
            /* Execute the command */
            if (execlp(command, command, NULL) == -1) 
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

    free(command);

    return 0;
}
