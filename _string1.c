#include "shell.h"

/**
 * string_cpy - copies a string
 * @dst: the dstination
 * @_src: the source
 *
 * Return: pointer to dstination
 */
char *string_cpy(char *dst, char *_src)
{
	int a = 0;

	if (dst == _src || _src == 0)
		return (dst);
	while (_src[a])
	{
		dst[a] = _src[a];
		a++;
	}
	dst[a] = 0;
	return (dst);
}

/**
 * string_dup - duplicates a string
 * @strng: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *string_dup(const char *strng)
{
	int length = 0;
	char *_ret;

	if (strng == NULL)
		return (NULL);
	while (*strng++)
		length++;
	_ret = malloc(sizeof(char) * (length + 1));
	if (!_ret)
		return (NULL);
	for (length++; length--;)
		_ret[length] = *--strng;
	return (_ret);
}

/**
 * _puts - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string)
{
	int a = 0;

	if (!string)
		return;
	while (string[a] != '\0')
	{
		_putchar(string[a]);
		a++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @d: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char d)
{
	static int a;
	static char buff[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buff, a);
		a = 0;
	}
	if (d != BUF_FLUSH)
		buff[a++] = d;
	return (1);
}
