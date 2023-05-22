#include "shell.h"

#include <stdbool.h>
#include <unistd.h>

#define MAXIMUM_COMMANDS 100 /* maximum number of commands */

/**
 * shell_prompt - function for executing terminal command
 * @av: argument vector (string array)
 * @env: environment vector (string array)
 */
void shell_prompt(char **av, char **env)
{
    char *user_input = NULL;
    size_t m = 0;
    ssize_t input_char;
    char *argv[MAXIMUM_COMMANDS];

    while (true)
    {
        if (isatty(STDIN_FILENO))
            printf("simple_shell$ ");
        input_char = getline(&user_input, &m, stdin);
        if (input_char == -1)
        {
            free(user_input);
            exit(EXIT_FAILURE);
        }

        /* Remove the trailing newline character */
        user_input[strcspn(user_input, "\n")] = '\0';

        int p = 0;
        argv[p] = strtok(user_input, " ");
        while (argv[p])
        {
            p++;
            argv[p] = strtok(NULL, " ");
        }

        if (argv[0] != NULL)
        {
            /* Check if the command exists */
            char *command_path = find_command(argv[0], env);
            if (command_path != NULL)
            {
                pid_t child_pid = fork();
                if (child_pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                if (child_pid == 0)
                {
                    if (execve(command_path, argv, env) == -1)
                    {
                        perror("execve");
                        exit(EXIT_FAILURE);
                    }
                }
                else
                {
                    int child_status;
                    if (wait(&child_status) == -1)
                    {
                        perror("wait");
                        exit(EXIT_FAILURE);
                    }
                }
                free(command_path);
            }
            else
            {
                printf("%s: command not found\n", argv[0]);
            }
        }
    }
}

/**
 * find_command - find the command in the PATH environment variable
 * @command: command to find
 * @env: environment vector (string array)
 * Return: full path to the command if found, otherwise NULL
 */
char *find_command(char *command, char **env)
{
    char *path = getenv("PATH");
    if (path == NULL)
    {
        printf("PATH environment variable not set\n");
        return NULL;
    }

    char *dir = strtok(path, ":");
    while (dir)
    {
        char *command_path = build_command_path(dir, command);
        if (access(command_path, X_OK) == 0)
            return command_path;

        free(command_path);
        dir = strtok(NULL, ":");
    }

    return NULL;
}

/**
 * build_command_path - build the full path to the command
 * @dir: directory in the PATH
 * @command: command name
 * Return: full path to the command
 */
char *build_command_path(char *dir, char *command)
{
    size_t path_len = strlen(dir);
    size_t command_len = strlen(command);
    char *command_path = malloc(path_len + command_len + 2); /* +2 for '/' and null terminator */

    if (command_path == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strcpy(command_path, dir);
    command_path[path_len] = '/';
    strcpy(command_path + path_len + 1, command);
    command_path[path_len + command_len + 1] = '\0';

    return command_path;
}

int main(int ac, char **av, char **env)
{
    if (ac == 1)
        shell_prompt(av, env);
    return 0;
}
