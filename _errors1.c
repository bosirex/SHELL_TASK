#include "shell.h"

/**
 * _erratoi - string to integer converter
 * @s: converted string
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *z)
{
	int y = 0;
	unsigned long int _result = 0;

	if (*z == '+')
		z++;  
	for (y = 0;  z[y] != '\0'; y++)
	{
		if (z[y] >= '0' && z[y] <= '9')
		{
			_result *= 10;
			_result += (z[y] - '0');
			if (_result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (_result);
}

/**
 * error_print - prints an error message
 * @dat: the parameter & return dat struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void error_print(data_t *dat, char *_estr)
{
	_eputs(dat->fname);
	_eputs(": ");
	print_dec(dat->lenght_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(dat->argv[0]);
	_eputs(": ");
	_eputs(_estr);
}

/**
 * print_dec - function prints a decimal number
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dec(int _input, int file_desc)
{
	int (*__putchar)(char) = _putchar;
	int t, cnt = 0;
	unsigned int _abs, _current;

	if (file_desc == STDERR_FILENO)
		__putchar = _eputchar;
	if (_input < 0)
	{
		_abs = -_input;
		__putchar('-');
		cnt++;
	}
	else
		_abs = _input;
	_current = _abs;
	for (t = 1000000000; t > 1; t /= 10)
	{
		if (_abs / t)
		{
			__putchar('0' + _current / t);
			cnt++;
		}
		_current %= t;
	}
	__putchar('0' + _current);
	cnt++;

	return (cnt);
}

/**
 * convt_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convt_number(long int number, int _base, int _flags)
{
	static char *arry;
	static char _buffer[50];
	char _sign = 0;
	char *ptr;
	unsigned long n = number;

	if (!(_flags & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		_sign = '-';

	}
	arry = _flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &_buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arry[n % _base];
		n /= _base;
	} while (n != 0);

	if (_sign)
		*--ptr = _sign;
	return (ptr);
}

/**
 * comments_remove - replaces first instance of '#' with '\0'
 * @buf: string address to be modified
 *
 * Return: Always 0;
 */
void comments_remove(char *buff)
{
	int x;

	for (x = 0; buff[i] != '\0'; x++)
		if (buff[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buff[x] = '\0';
			break;
		}
}
