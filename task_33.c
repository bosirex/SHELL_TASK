#include "shell.h"
#include <sys/wait.h>

#define BUFSIZE 1024

void display_prompt(void);
char *read_line(void);
int execute_command(char *command, char **args);

int main_33(int argc, char **argv, char **envp) {
    char *line;
    char *args[BUFSIZE/2 + 1]; /* maximum number of arguments is BUFSIZE/2 */
    int status;

    do {
        display_prompt();
        line = read_line();
        status = execute_command(line, args);
        free(line);
    } while (status);

    return 0;
}


char *read_line(void) {
    static char buf[BUFSIZE];
    static int pos = 0;
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        buf[pos++] = c;
        if (pos >= BUFSIZE) {
            fprintf(stderr, "Error: command too long\n");
            exit(EXIT_FAILURE);
        }
    }

    if (c == EOF && pos == 0) {
        return NULL;
    }

    buf[pos] = '\0';
    pos = 0;
    return strdup(buf);
}

int execute_command_33(char *command, char **args) {
    int i = 0;
    char *path;
    pid_t pid;

    if (command == NULL) {
        exit(EXIT_SUCCESS);
    }

    args[i++] = strtok(command, " ");
    while ((args[i++] = strtok(NULL, " ")) != NULL);

    if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "env") == 0) {
        char **env;
        for (env = environ; *env != NULL; env++) {
            printf("%s\n", *env);
        }
        return 1;
    }

    path = getenv("PATH");

    if (path == NULL) {
        fprintf(stderr, "Error: PATH environment variable not set\n");
        return 1;
    }

    char *token, *p;
    char fullpath[BUFSIZE];
    int found = 0;
    token = strtok(path, ":");
    while (token != NULL) {
        snprintf(fullpath, BUFSIZE, "%s/%s", token, args[0]);
        if (access(fullpath, X_OK) == 0) {
            found = 1;
            break;
        }
        token = strtok(NULL, ":");
    }

    if (!found) {
        fprintf(stderr, "./shell: No such file or directory %s\n", args[0]);
        return 1;
    }

    pid = fork();
    if (pid == -1) {
        perror("Error: fork");
        return 1;
    } else if (pid == 0) {
        if (execve(fullpath, args, environ) == -1) {
            perror("Error: execve");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }

    return 1;
}
