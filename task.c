#include "shell.h"
#include <stdio.h>
#include <sys/wait.h>

/**
 * display_prompt - dispays the prompt
*/
void display_prompt() 
{
    printf("simple_shell$ ");
    fflush(stdout);
}