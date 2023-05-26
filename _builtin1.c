#include "shell.h"

/**
 * _history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @dat: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _history(info_t *dat)
{
	print_list(dat->history);
	return (0);
}

/**
 * alias_unset - sets alias to string
 * @dat: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_unset(info_t *dat, char *str)
{
	char *p, c;
	int ret;

	p = string_character(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_nd_at_index(&(dat->alias),
		get_nd_index(dat->alias, nd_startswith(dat->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * alias_set - sets alias to string
 * @dat: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(info_t *dat, char *str)
{
	char *p;

	p = string_character(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_unset(dat, str));

	alias_unset(dat, str);
	return (add_nd_end(&(dat->alias), str, 0) == NULL);
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
int _alias(info_t *dat)
{
	int i = 0;
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
	for (i = 1; dat->argv[i]; i++)
	{
		p = string_character(dat->argv[i], '=');
		if (p)
			alias_set(dat, dat->argv[i]);
		else
			alias_print(nd_startswith(dat->alias, dat->argv[i], '='));
	}

	return (0);
}
