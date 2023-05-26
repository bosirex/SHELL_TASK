#include "shell.h"

/**
 * string_len - returns the length of a string
 * @z: the string whose length to check
 *
 * Return: integer length of string
 */
int string_len(char *z)
{
	int x = 0;

	if (!z)
		return (0);

	while (*z++)
		x++;
	return (x);
}

/**
 * str_comparison - performs lexicogarphic comparison of two strangs.
 * @z1: the first strang
 * @z2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int str_comparison(char *z1, char *z2)
{
	while (*z1 && *z2)
	{
		if (*z1 != *z2)
			return (*z1 - *z2);
		z1++;
		z2++;
	}
	if (*z1 == *z2)
		return (0);
	else
		return (*z1 < *z2 ? -1 : 1);
}

/**
 * _startswith - checks if needle starts with haystack
 * @_haystack: string to search
 * @_needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *_startswith(const char *_haystack, const char *_needle)
{
	while (*_needle)
		if (*_needle++ != *_haystack++)
			return (NULL);
	return ((char *)_haystack);
}

/**
 * string_cat - concatenates two strings
 * @dst: the dstination buffer
 * @_src: the source buffer
 *
 * Return: pointer to dstination buffer
 */
char *string_cat(char *dst, char *_src)
{
	char *_ret = dst;

	while (*dst)
		dst++;
	while (*_src)
		*dst++ = *_src++;
	*dst = *_src;
	return (_ret);
}
