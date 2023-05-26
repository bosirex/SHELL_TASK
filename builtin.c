#include "shell.h"

/**
 * _exits - exits the shell
 * @dat: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if dat.argv[0] != "exit"
 */
int _exits(info_t *dat)
{
	int exitcheck;

	if (dat->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = _erratoi(dat->argv[1]);
		if (exitcheck == -1)
		{
			dat->status = 2;
			error_print(dat, "Illegal number: ");
			_eputs(dat->argv[1]);
			_eputchar('\n');
			return (1);
		}
		dat->err_num = _erratoi(dat->argv[1]);
		return (-2);
	}
	dat->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the current drectory of the process
 * @dat: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _cd(info_t *dat)
{
	char *s, *dr, buffer[1024];
	int chdr_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!dat->argv[1])
	{
		dr = get_env(dat, "HOME=");
		if (!dr)
			chdr_ret = /* TODO: what should this be? */
				chdir((dr = get_env(dat, "PWD=")) ? dr : "/");
		else
			chdr_ret = chdr(dr);
	}
	else if (_strcmp(dat->argv[1], "-") == 0)
	{
		if (!get_env(dat, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(dat, "OLDPWD=")), _putchar('\n');
		chdr_ret = /* TODO: what should this be? */
			chdr((dr = get_env(dat, "OLDPWD=")) ? dr : "/");
	}
	else
		chdr_ret = chdr(dat->argv[1]);
	if (chdr_ret == -1)
	{
		error_print(dat, "can't cd to ");
		_eputs(dat->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(dat, "OLDPWD", get_env(dat, "PWD="));
		_setenv(dat, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help - changes the current drectory of the process
 * @dat: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _help(info_t *dat)
{
	char **arg_array;

	arg_array = dat->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
