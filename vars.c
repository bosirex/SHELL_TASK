#include "shell.h"

/**
 * _ischain - test for a chain delimeter
 * @dat: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 
 */
int _ischain(info_t *dat, char *buf, size_t *m)
{
	size_t x = *m;

	if (buf[x] == '|' && buf[x + 1] == '|')
	{
		buf[x] = 0;
		x++;
		dat->cmd_buf_type = CMD_OR;
	}
	else if (buf[x] == '&' && buf[x + 1] == '&')
	{
		buf[x] = 0;
		x++;
		dat->cmd_buf_type = CMD_AND;
	}
	else if (buf[x] == ';') 
	{
		buf[x] = 0; 
		dat->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*m = x;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @dat: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *dat, char *buf, size_t *p, size_t i, size_t len)
{
	size_t m = *p;

	if (dat->cmd_buf_type == CMD_AND)
	{
		if (dat->status)
		{
			buf[i] = 0;
			m = len;
		}
	}
	if (dat->cmd_buf_type == CMD_OR)
	{
		if (!dat->status)
		{
			buf[i] = 0;
			m = len;
		}
	}

	*p = m;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @dat: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *dat)
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
 * vars_replace - replaces vars in the tokenized string
 * @dat: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vars_replace(info_t *dat)
{
	int k = 0;
	lst_t *nd;

	for (k = 0; dat->argv[k]; k++)
	{
		if (dat->argv[k][0] != '$' || !dat->argv[k][1])
			continue;

		if (!_strcmp(dat->argv[k], "$?"))
		{
			_replacestring(&(dat->argv[k]),
					string_dup(convt_number(dat->status, 10, 0)));
			continue;
		}
		if (!_strcmp(dat->argv[k], "$$"))
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
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replacestring(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
