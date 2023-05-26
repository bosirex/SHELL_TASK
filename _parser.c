#include "shell.h"

/**
 * _iscmd - determines if a file is an executable command
 * @dat: the dat struct
 * @_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _iscmd(data_t *dat, char *_path)
{
	struct stat st;

	(void)dat;
	if (!_path || stat(_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @_pathstr: the PATH string
 * @_start: starting index
 * @_stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *_pathstr, int _start, int _stop)
{
	static char buff[1024];
	int x = 0, j = 0;

	for (j = 0, x = _start; x < _stop; x++)
		if (_pathstr[x] != ':')
			buff[j++] = _pathstr[x];
	buff[j] = 0;
	return (buff);
}

/**
 * _findpath - finds this cmd in the PATH string
 * @dat: the dat struct
 * @_pathstr: the PATH string
 * @_cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *_findpath(data_t *dat, char *_pathstr, char *_cmd)
{
	int m = 0, current_pos = 0;
	char *_path;

	if (!_pathstr)
		return (NULL);
	if ((string_len(_cmd) > 2) && _startswith(_cmd, "./"))
	{
		if (_iscmd(dat, _cmd))
			return (_cmd);
	}
	while (1)
	{
		if (!_pathstr[m] || _pathstr[m] == ':')
		{
			_path = dup_chars(_pathstr, current_pos, m);
			if (!*_path)
				string_cat(_path, _cmd);
			else
			{
				string_cat(_path, "/");
				string_cat(_path, _cmd);
			}
			if (_iscmd(dat, _path))
				return (_path);
			if (!_pathstr[m])
				break;
			current_pos = m;
		}
		m++;
	}
	return (NULL);
}
