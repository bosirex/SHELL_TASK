#include "shell.h"

/**
 * add_nd - adds a nd to the start of the list
 * @hd: address of pointer to hd nd
 * @str: str field of nd
 * @num: nd index used by history
 *
 * Return: size of list
 */
lst_t *add_nd(lst_t **hd, const char *str, int num)
{
	lst_t *new_hd;

	if (!hd)
		return (NULL);
	new_hd = malloc(sizeof(lst_t));
	if (!new_hd)
		return (NULL);
	mem_set((void *)new_hd, 0, sizeof(lst_t));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = string_dup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *hd;
	*hd = new_hd;
	return (new_hd);
}

/**
 * add_nd_end - adds a nd to the end of the list
 * @hd: address of pointer to hd nd
 * @str: str field of nd
 * @num: nd index used by history
 *
 * Return: size of list
 */
lst_t *add_nd_end(lst_t **hd, const char *str, int num)
{
	lst_t *new_nd, *nd;

	if (!hd)
		return (NULL);

	nd = *hd;
	new_nd = malloc(sizeof(lst_t));
	if (!new_nd)
		return (NULL);
	mem_set((void *)new_nd, 0, sizeof(lst_t));
	new_nd->num = num;
	if (str)
	{
		new_nd->str = string_dup(str);
		if (!new_nd->str)
		{
			free(new_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = new_nd;
	}
	else
		*hd = new_nd;
	return (new_nd);
}

/**
 * print_lst_str - prints only the string element linked list
 * @h: first node pointer
 *
 * Return: list size
 */
size_t print_lst_str(const lst_t *h)
{
	size_t j = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * delete_nd_at_index - deletes nd at given index
 * @hd: address of pointer to first nd
 * @index: index of nd to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_nd_at_index(lst_t **hd, unsigned int index)
{
	lst_t *nd, *prev_nd;
	unsigned int j = 0;

	if (!hd || !*hd)
		return (0);

	if (!index)
	{
		nd = *hd;
		*hd = (*hd)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *hd;
	while (nd)
	{
		if (j == index)
		{
			prev_nd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		j++;
		prev_nd = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * free_list - frees all nds of a list
 * @ptr_hd: address of pointer to hd nd
 *
 * Return: void
 */
void free_list(lst_t **ptr_hd)
{
	lst_t *nd, *next_nd, *hd;

	if (!ptr_hd || !*ptr_hd)
		return;
	hd = *ptr_hd;
	nd = hd;
	while (nd)
	{
		next_nd = nd->next;
		free(nd->str);
		free(nd);
		nd = next_nd;
	}
	*ptr_hd = NULL;
}
