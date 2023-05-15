#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int sum(int a, int b);
void remove_newline(char* str);
void execute_command(char* command);
char **parse_arguments(char *command);
void execute_command(char **arguments);
int execute_command(char *command);
void execute_command(char *command, char *args[]);
char* read_command();
char* find_executable(char* command);
int execute_command(char* command);




#endif