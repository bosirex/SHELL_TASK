#include "shell.h"

#define MAX_ARGUMENTS 10

char *argument;
pid_t pid;
int i;
int argument_index;
int command_length;
int in_quotes;
int start_index;

/**
 * parse_arguments - split the command line into separate arguments
 */
char **parse_arguments(char *command) {
    char **arguments = malloc(MAX_ARGUMENTS * sizeof(char *));
    if (!arguments) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    i = 0;
    argument_index = 0;
    command_length = strlen(command);
    in_quotes = 0;
    start_index = 0;
    while (i < command_length) {
        if (command[i] == '"' || command[i] == '\'') {
            in_quotes = !in_quotes;
            i++;
            continue;
        }

        if (command[i] == ' ' && !in_quotes) {
            argument = malloc((i - start_index + 1) * sizeof(char));
            if (!argument) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            strncpy(argument, command + start_index, i - start_index);
            argument[i - start_index] = '\0';
            arguments[argument_index++] = argument;

            start_index = i + 1;
        }

        i++;
    }

    /* Get the last argument */
    argument = malloc((i - start_index + 1) * sizeof(char));
    if (!argument) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strncpy(argument, command + start_index, i - start_index);
    argument[i - start_index] = '\0';
    arguments[argument_index++] = argument;

    arguments[argument_index] = NULL;

    return arguments;
}

/**
 * execute_command - execute the command using execvp()
 */
void execute_command(char **arguments) {
    execvp(arguments[0], arguments);
    fprintf(stderr, "./shell: No such file or directory %s\n", arguments[0]);
    exit(EXIT_FAILURE);
}

/**
 * main - parses the command arguments, executes the command,
 * and handles the end-of-file condition
 */
int main_3() 
{
    char *command = NULL;
    size_t command_size = 0;
    ssize_t user_input;

    while (1) {
        display_prompt();

        /* Read the user input command */
        user_input = getline(&command, &command_size, stdin);
        if (user_input == -1) {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the trailing newline character */
        command[strcspn(command, "\n")] = '\0';

        /* Fork a child process */
        pid = fork();

        if (pid < 0) {
            /* Error occurred while forking */
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */
            /* Parse the command arguments */
            char **arguments = parse_arguments(command);
            /* Execute the command */
            execute_command(arguments);
            /* This code is executed only if exec fails */
            exit(EXIT_SUCCESS);
        } else {
            /* Parent process */
            /* Wait for the child process to finish */
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
        }
    }
    free(command);
    return 0;
}
