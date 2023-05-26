#include "shell.h"

/**
 * _iscmd - determines if a file is an executable command
 * @dat: the dat struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _iscmd(data_t *dat, char *path)
{
	struct stat st;

	(void)dat;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * _findpath - finds this cmd in the PATH string
 * @dat: the dat struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_findpath(data_t *dat, char *pathstr, char *cmd)
{
	int n = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string_len(cmd) > 2) && _startswith(cmd, "./"))
	{
		if (_iscmd(dat, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[n] || pathstr[n] == ':')
		{
			path = dup_chars(pathstr, curr_pos, n);
			if (!*path)
				string_cat(path, cmd);
			else
			{
				string_cat(path, "/");
				string_cat(path, cmd);
			}
			if (_iscmd(dat, path))
				return (path);
			if (!pathstr[n])
				break;
			curr_pos = n;
		}
		n++;
	}
	return (NULL);
}
