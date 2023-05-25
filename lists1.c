#include "shell.h"

/**
 * length_list - determines length of linked list
 * @h: pointer to first nd
 *
 * Return: size of list
 */
size_t length_list(const lst_t *d)
{
	size_t a = 0;

	while (d)
	{
		d = d->next;
		a++;
	}
	return (a);
}

/**
 * lst_to_str - array of strings is returned
 * @hd: pointer to first nd
 *
 * Return: array of strings
 */
char **lst_to_str(lst_t *hd)
{
	lst_t *nd = hd;
	size_t a = length_list(hd), b;
	char **strs;
	char *str;

	if (!hd || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; nd; nd = nd->next, a++)
	{
		str = malloc(string_len(nd->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = string_copy(str, nd->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a lst_t linked list
 * @h: pointer to first nd
 *
 * Return: size of list
 */
size_t print_list(const lst_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convt_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nd_startswith - returns nd whose string starts with prefix
 * @nd: pointer to list hd
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match nd or null
 */
lst_t *nd_startswith(lst_t *nd, char *prefix, char c)
{
	char *p = NULL;

	while (nd)
	{
		p = _startswith(nd->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * get_nd_index - gets the index of a nd
 * @hd: pointer to list hd
 * @nd: pointer to the nd
 *
 * Return: index of nd or -1
 */
ssize_t get_nd_index(lst_t *hd, lst_t *nd)
{
	size_t i = 0;

	while (hd)
	{
		if (hd == nd)
			return (i);
		hd = hd->next;
		i++;
	}
	return (-1);
}
