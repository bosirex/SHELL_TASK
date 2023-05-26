#include "shell.h"

/**
 * add_nd - adds a nd to the start of the list
 * @hd: address of pointer to hd nd
 * @string: str field of nd
 * @_num: nd index used by history
 *
 * Return: size of list
 */
lst_t *add_nd(lst_t **hd, const char *string, int _num)
{
	lst_t *_newhd;

	if (!hd)
		return (NULL);
	_newhd = malloc(sizeof(lst_t));
	if (!_newhd)
		return (NULL);
	mem_set((void *)_newhd, 0, sizeof(lst_t));
	_newhd->num = _num;
	if (string)
	{
		_newhd->str = string_dup(string);
		if (!_newhd->str)
		{
			free(_newhd);
			return (NULL);
		}
	}
	_newhd->next = *hd;
	*hd = _newhd;
	return (_newhd);
}

/**
 * add_nd_end - adds a nd to the end of the list
 * @_hd: address of pointer to hd nd
 * @string: str field of nd
 * @_num: nd index used by history
 *
 * Return: size of list
 */
lst_t *add_nd_end(lst_t **_hd, const char *string, int _num)
{
	lst_t *_newnd, *nd;

	if (!_hd)
		return (NULL);

	nd = *_hd;
	_newnd = malloc(sizeof(lst_t));
	if (!_newnd)
		return (NULL);
	mem_set((void *)_newnd, 0, sizeof(lst_t));
	_newnd->num = _num;
	if (string)
	{
		_newnd->str = string_dup(string);
		if (!_newnd->str)
		{
			free(_newnd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = _newnd;
	}
	else
		*_hd = _newnd;
	return (_newnd);
}

/**
 * print_lst_str - prints only the string element linked list
 * @h: first node pointer
 *
 * Return: list size
 */
size_t print_lst_str(const lst_t *k)
{
	size_t m = 0;

	while (k)
	{
		_puts(k->str ? k->str : "(nil)");
		_puts("\n");
		k = k->next;
		m++;
	}
	return (m);
}

/**
 * delete_nd_at_index - deletes nd at given index
 * @_hd: address of pointer to first nd
 * @indx: index of nd to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_nd_at_index(lst_t **_hd, unsigned int indx)
{
	lst_t *_prevnd, *nd;
	unsigned int k = 0;

	if (!_hd || !*_hd)
		return (0);

	if (!indx)
	{
		nd = *_hd;
		*_hd = (*_hd)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *_hd;
	while (nd)
	{
		if (k == indx)
		{
			_prevnd->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		k++;
		_prevnd = nd;
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
	lst_t *_nextnd, *nd, *_hd;

	if (!ptr_hd || !*ptr_hd)
		return;
	_hd = *ptr_hd;
	nd = _hd;
	while (nd)
	{
		_nextnd = nd->next;
		free(nd->str);
		free(nd);
		nd = _nextnd;
	}
	*ptr_hd = NULL;
}
