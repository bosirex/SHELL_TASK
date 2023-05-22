#include "shell.h"
#include <stdbool.h>

#define MAXIMUM_COMMANDS 100 /* maximum number of commands */

/**
 * shell_prompt - fn for executing terminal command
 * @av: argument vector (string array)
 * @env: argument vector (string array)
 */
void shell_prompt(char **av, char **env)
{
    char *user_input = NULL;
    int k, p, child_status;
    size_t m = 0;
    ssize_t input_char;
    char *argv[MAXIMUM_COMMANDS];
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
        p = 0;
        argv[p] = strtok(user_input, " ");
        while (argv[p])
        {
            p++;
            argv[p] = strtok(NULL, " ");
        }

        bool command_found = false;
        char *path = getenv("PATH");
        if (path != NULL)
        {
            char *path_token = strtok(path, ":");
            while (path_token)
            {
                char command_path[100];
                sprintf(command_path, "%s/%s", path_token, argv[0]);
                if (access(command_path, X_OK) == 0)
                {
                    command_found = true;
                    argv[0] = command_path;
                    break;
                }
                path_token = strtok(NULL, ":");
            }
        }

        if (command_found)
        {
            child_pid = fork();
            if (child_pid == -1)
            {
                free(user_input);
                exit(EXIT_FAILURE);
            }
            if (child_pid == 0)
            {
                if (execve(argv[0], argv, env) == -1)
                    printf("%s: No such file or directory\n", av[0]);
            }
            else
                wait(&child_status);
        }
        else
        {
            printf("%s: Command not found\n", argv[0]);
        }
    }
}

int main(int ac, char **av, char **env)
{
    if (ac == 1)
        shell_prompt(av, env);
    return 0;
}
