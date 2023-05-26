#include "shell.h"

/**
 * _history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @dat: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _history(data_t *dat)
{
	print_list(dat->history);
	return (0);
}

/**
 * alias_unset - sets alias to string
 * @dat: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_unset(data_t *dat, char *string)
{
	char *p, c;
	int _ret;

	p = string_character(string, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	_ret = delete_nd_at_index(&(dat->alias),
		get_nd_index(dat->alias, nd_startswith(dat->alias, string, -1)));
	*p = c;
	return (_ret);
}

/**
 * alias_set - sets alias to string
 * @dat: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(data_t *dat, char *string)
{
	char *p;

	p = string_character(string, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_unset(dat, string));

	alias_unset(dat, str);
	return (add_nd_end(&(dat->alias), string, 0) == NULL);
}

/**
 * alias_print - prints an alias string
 * @nd: the alias nd
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_print(lst_t *nd)
{
	char *p = NULL, *a = NULL;

	if (nd)
	{
		p = string_character(nd->str, '=');
		for (a = nd->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin (man alias)
 * @dat: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _alias(data_t *dat)
{
	int x = 0;
	char *p = NULL;
	lst_t *nd = NULL;

	if (dat->argc == 1)
	{
		nd = dat->alias;
		while (nd)
		{
			alias_print(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (x = 1; dat->argv[x]; x++)
	{
		p = string_character(dat->argv[x], '=');
		if (p)
			alias_set(dat, dat->argv[x]);
		else
			alias_print(nd_startswith(dat->alias, dat->argv[x], '='));
	}

	return (0);
}
