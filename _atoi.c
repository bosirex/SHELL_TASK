#include "shell.h"

/**
 * interactiv - returns true if shell is interactive mode
 * @dat: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactiv(data_t *dat)
{
	return (isatty(STDIN_FILENO) && dat->_readfd <= 2);
}

/**
 * _isdelim - checks if character is a delimeter
 * @d: the char to check
 * @delm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int _isdelim(char d, char *delm)
{
	while (*delm)
		if (*delm++ == d)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @k: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int k)
{
	if ((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @z: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *z)
{
	int x, _sign = 1, _flag = 0, _output;
	unsigned int _result = 0;

	for (x = 0; z[x] != '\0' && _flag != 2; x++)
	{
		if (z[x] == '-')
			_sign *= -1;

		if (z[x] >= '0' && z[x] <= '9')
		{
			_flag = 1;
			_result *= 10;
			_result += (z[x] - '0');
		}
		else if (_flag == 1)
			_flag = 2;
	}

	if (_sign == -1)
		_output = -_result;
	else
		_output = _result;

	return (_output);
}
