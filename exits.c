#include "shell.h"

/**
 **str_copy - copies a string
 *@dest: string estination 
 *@src: string source
 *@n: characters amount copied
 *Return: concatenated string
 */
char *str_copy(char *dest, char *src, int n)
{
	int p, q;
	char *z = dest;

	p = 0;
	while (src[p] != '\0' && p < n - 1)
	{
		dest[p] = src[p];
		p++;
	}
	if (p < n)
	{
		q = p;
		while (q < n)
		{
			dest[q] = '\0';
			q++;
		}
	}
	return (z);
}

/**
 **string_concatenate - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *string_concatenate(char *dest, char *src, int n)
{
	int p, q;
	char *z = dest;

	p = 0;
	q = 0;
	while (dest[p] != '\0')
		p++;
	while (src[q] != '\0' && q < n)
	{
		dest[q] = src[q];
		p++;
		q++;
	}
	if (q < n)
		dest[p] = '\0';
	return (z);
}

/**
 **string_character - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *string_character(char *z, char c)
{
	do {
		if (*z == c)
			return (z);
	} while (*z++ != '\0');

	return (NULL);
}
