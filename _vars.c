#include "shell.h"

/**
 * _ischain - test for a chain delimeter
 * @dat: the parameter struct
 * @buff: the char buffer
 * @m: address of current position in buf
 *
 * Return: 1 
 */
int _ischain(data_t *dat, char *buff, size_t *m)
{
	size_t x = *m;

	if (buff[x] == '|' && buff[x + 1] == '|')
	{
		buff[x] = 0;
		x++;
		dat->cmd_buf_type = CMD_OR;
	}
	else if (buff[x] == '&' && buff[x + 1] == '&')
	{
		buff[x] = 0;
		x++;
		dat->cmd_buf_type = CMD_AND;
	}
	else if (buff[x] == ';') 
	{
		buff[x] = 0; 
		dat->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*m = x;
	return (1);
}

/**
 * check_chain - checks for continue chaining
 * @dat: the  struct parameter
 * @buf: the char buffer
 * @a: current position address
 * @j: starting position 
 * @_len: buf length 
 *
 * Return: Void
 */
void check_chain(data_t *dat, char *buf, size_t *a, size_t j, size_t _len)
{
	size_t m = *a;

	if (dat->cmd_buf_type == CMD_AND)
	{
		if (dat->status)
		{
			buf[j] = 0;
			m = _len;
		}
	}
	if (dat->cmd_buf_type == CMD_OR)
	{
		if (!dat->status)
		{
			buf[j] = 0;
			m = _len;
		}
	}

	*a = m;
}

/**
 * replace_alias - replaces an aliases
 * @dat: the  struct parameter
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(data_t *dat)
{
	int k;
	lst_t *nd;
	char *p;

	for (k = 0; k < 10; k++)
	{
		nd = nd_startswith(dat->alias, dat->argv[0], '=');
		if (!nd)
			return (0);
		free(dat->argv[0]);
		p = string_character(nd->str, '=');
		if (!p)
			return (0);
		p = string_dup(p + 1);
		if (!p)
			return (0);
		dat->argv[0] = p;
	}
	return (1);
}

/**
 * vars_replace - replaces vars 
 * @dat: the struct parameter 
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vars_replace(data_t *dat)
{
	int k = 0;
	lst_t *nd;

	for (k = 0; dat->argv[k]; k++)
	{
		if (dat->argv[k][0] != '$' || !dat->argv[k][1])
			continue;

		if (!str_comparison(dat->argv[k], "$?"))
		{
			_replacestring(&(dat->argv[k]),
					string_dup(convt_number(dat->status, 10, 0)));
			continue;
		}
		if (!str_comparison(dat->argv[k], "$$"))
		{
			_replacestring(&(dat->argv[k]),
					string_dup(convt_number(getpid(), 10, 0)));
			continue;
		}
		nd = nd_startswith(dat->env, &dat->argv[k][1], '=');
		if (nd)
		{
			_replacestring(&(dat->argv[k]),
					string_dup(string_character(nd->str, '=') + 1));
			continue;
		}
		_replacestring(&dat->argv[k], string_dup(""));

	}
	return (0);
}

/**
 * _replacestring - replaces string
 * @_old: address of old string
 * @_new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replacestring(char **_old, char *_new)
{
	free(*_old);
	*_old = _new;
	return (1);
}
