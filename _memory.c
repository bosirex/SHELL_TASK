#include "shell.h"

/**
 * ptr_free - NULLs the pointer address
 * @pt: pointer address to be freed
 *
 * Return: 1 if freed, otherwise 0.
 */
int ptr_free(void **pt)
{
	if (pt && *pt)
	{
		free(*pt);
		*pt = NULL;
		return (1);
	}
	return (0);
}
