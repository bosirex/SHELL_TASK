#include "shell.h"

/**
 * mem_set - fill the memory 
 * @s: pointer to memory
 * @b: the byte to fill *s with
 * @n: amount of bytes
 * Return: (s) a pointer to memory area
 */
char *mem_set(char *t, char k, unsigned int m)
{
	unsigned int j;

	for (j = 0; j < m; j++)
		t[j] = k;
	return (t);
}

/**
 * f_free - freeing string of strings
 * @pp: string of strings
 */
void f_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * real_loc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @oldsize: byte size of previous block
 * @newsize: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *real_loc(void *ptr, unsigned int oldsize, unsigned int newsize)
{
	char *v;

	if (!ptr)
		return (malloc(newsize));
	if (!newsize)
		return (free(ptr), NULL);
	if (newsize == oldsize)
		return (ptr);

	v = malloc(newsize);
	if (!v)
		return (NULL);

	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		v[oldsize] = ((char *)ptr)[oldsize];
	free(ptr);
	return (v);
}
