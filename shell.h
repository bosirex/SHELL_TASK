#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void display_prompt();
int main(int ac, char **av, char **env);

#endif