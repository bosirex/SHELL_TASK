#include "shell.h"

/**
 * _eputs - prints an input string
 * @string: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *string)
{
	int x = 0;

	if (!string)
		return;
	while (string[x] != '\0')
	{
		_eputchar(string[x]);
		x++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @b: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char b)
{
	static int x;
	static char buff[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buff, x);
		x = 0;
	}
	if (b != BUF_FLUSH)
		buff[x++] = b;
	return (1);
}

/**
 * fd_put - writes the character c to given fd
 * @b: The character to print
 * @file_desc: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int fd_put(char b, int file_desc)
{
	static int x;
	static char buff[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(file_desc, buff, x);
		x = 0;
	}
	if (b != BUF_FLUSH)
		buff[x++] = b;
	return (1);
}

/**
 * putsfile_desc - prints an input string
 * @string: the string to be printed
 * @file_desc: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int putsfile_desc(char *string, int file_desc)
{
	int x = 0;

	if (!string)
		return (0);
	while (*string)
	{
		x += fd_put(*string++, file_desc);
	}
	return (x);
}
