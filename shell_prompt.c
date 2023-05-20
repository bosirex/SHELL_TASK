#include "shell.h"
#include <sys/wait.h>


/**
 * shell_prompt - fn for executing terminal command
 * @av: argument vector (string array)
 * @env: argument vector (string array)
*/

void shell_prompt(char **av, char **env)
{
    char *user_input = NULL;
    int k, child_status;
    size_t m = 0;
    ssize_t input_char;
    char *argv[] = {NULL, NULL};
    pid_t child_pid;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("simple_shell$ ");
        input_char = getline(&user_input, &m, stdin);
        if (input_char == -1)
        {
            free(user_input);
            exit(EXIT_FAILURE);
        }
        k = 0;
        while (user_input[k])
        {
            if (user_input[k] == '\n')
                user_input[k] = 0;
            k++;
        }
        argv[0] = user_input;
        child_pid = fork();
        if (child_pid == -1)
        {
            free(user_input);
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
            if (execve(argv[0], argv, env) == -1)
                printf("%s: ./shell: No such file or directory\n", av[0]);
            
        }
        else
            wait(&child_status);
    }
}
