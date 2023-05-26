#include "shell.h"

/**
 * input_buffer - buffers chained commands
 * @dat: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buffer(data_t *dat, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*ptr_free((void **)dat->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_line(dat, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			dat->line_count_flag = 1;
			comments_remove(*buf);
			build_history_list(dat, *buf, dat->histcount++);
			/* if (string_character(*buf, ';')) is this a command chain? */
			{
				*len = r;
				dat->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * input_get - gets a line minus the newline
 * @dat: parameter struct
 *
 * Return: bytes read
 */
ssize_t input_get(data_t *dat)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t y, j, len;
	ssize_t r = 0;
	char **buf_p = &(dat->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buffer(dat, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = y; /* init new iterator to current buf position */
		p = buf + y; /* get pointer for return */

		check_chain(dat, buf, &j, y, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (_ischain(dat, buf, &j))
				break;
			j++;
		}

		y = j + 1; /* increment past nulled ';'' */
		if (y >= len) /* reached end of buffer? */
		{
			y = len = 0; /* reset position and length */
			dat->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (string_len(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from get_line() */
	return (r); /* return length of buffer from get_line() */
}

/**
 * read_buf - reads a buffer
 * @dat: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(data_t *dat, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(dat->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - gets the next line of input from STDIN
 * @dat: struct parameter 
 * @ptr:  buffer pointer address.
 * @length: preallocated ptr buffer size
 *
 * Return: s
 */
int get_line(data_t *dat, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(dat, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = string_character(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = real_loc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		string_concatenate(new_p, buf + i, k - i);
	else
		str_copy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
