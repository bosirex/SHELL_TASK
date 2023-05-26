#include "shell.h"

/**
 * _env - prints the current environment
 * @dat: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _env(info_t *dat)
{
	print_lst_str(dat->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @dat: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *get_env(info_t *dat, const char *name)
{
	lst_t *nd = dat->env;
	char *p;

	while (nd)
	{
		p = _startswith(nd->str, name);
		if (p && *p)
			return (p);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * _setenviron - Initialize a new environment variable,
 *             or modify an existing one
 * @dat: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _setenviron(info_t *dat)
{
	if (dat->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(dat, dat->argv[1], dat->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenviron - Remove an environment variable
 * @dat: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _unsetenviron(info_t *dat)
{
	int i;

	if (dat->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= dat->argc; i++)
		_unsetenv(dat, dat->argv[i]);

	return (0);
}

/**
 * env_list_populate - populates env linked list
 * @dat: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int env_list_populate(info_t *dat)
{
	lst_t *nd = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nd_end(&nd, environ[i], 0);
	dat->env = nd;
	return (0);
}
