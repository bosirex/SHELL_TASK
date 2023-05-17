#include "shell.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * display_prompt - dispays the prompt
*/
void display_prompt() 
{
    printf("simple_shell$ ");
    fflush(stdout);
}
/**
 * handle_exit - Function to handle the exit built-in command
 * 
*/
void handle_exit() 
{
    exit(EXIT_SUCCESS);
}