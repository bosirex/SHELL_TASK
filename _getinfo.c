#include "shell.h"

/**
 * clear_dat - initializes info_t struct
 * @dat: struct address
 */
void clear_dat(info_t *dat)
{
	dat->arg = NULL;
	dat->argv = NULL;
	dat->path = NULL;
	dat->argc = 0;
}

/**
 * set_dat - initializes info_t struct
 * @dat: struct address
 * @av: argument vector
 */
void set_dat(info_t *dat, char **av)
{
	int i = 0;

	dat->fname = av[0];
	if (dat->arg)
	{
		dat->argv = string_word(dat->arg, " \t");
		if (!dat->argv)
		{
			dat->argv = malloc(sizeof(char *) * 2);
			if (dat->argv)
			{
				dat->argv[0] = string_dup(dat->arg);
				dat->argv[1] = NULL;
			}
		}
		for (i = 0; dat->argv && dat->argv[i]; i++)
			;
		dat->argc = i;

		replace_alias(dat);
		vars_replace(dat);
	}
}

/**
 * free_dat - frees info_t struct fields
 * @dat: struct address
 * @all: true if freeing all fields
 */
void free_dat(info_t *dat, int all)
{
	f_free(dat->argv);
	dat->argv = NULL;
	dat->path = NULL;
	if (all)
	{
		if (!dat->cmd_buf)
			free(dat->arg);
		if (dat->env)
			free_list(&(dat->env));
		if (dat->history)
			free_list(&(dat->history));
		if (dat->alias)
			free_list(&(dat->alias));
		f_free(dat->environ);
			dat->environ = NULL;
		ptr_free((void **)dat->cmd_buf);
		if (dat->readfd > 2)
			close(dat->readfd);
		_putchar(BUF_FLUSH);
	}
}
