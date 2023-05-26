#include "shell.h"

/**
 * _exits - exits the shell
 * @dat: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if dat.argv[0] != "exit"
 */
int _exits(data_t *dat)
{
	int _exitcheck;

	if (dat->argv[1]) /* If there is an exit arguement */
	{
		_exitcheck = _erratoi(dat->argv[1]);
		if (_exitcheck == -1)
		{
			dat->status = 2;
			error_print(dat, "Illegal number: ");
			_eputs(dat->argv[1]);
			_eputchar('\n');
			return (1);
		}
		dat->err_number = _erratoi(dat->argv[1]);
		return (-2);
	}
	dat->err_number = -1;
	return (-2);
}

/**
 * _cd - changes the current drectory of the process
 * @dat: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _cd(data_t *dat)
{
	char *z, *_dr, buff[1024];
	int chdr_ret;

	z = getcwd(buff, 1024);
	if (!z)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!dat->argv[1])
	{
		_dr = get_env(dat, "HOME=");
		if (!_dr)
			chdr_ret = /* TODO: what should this be? */
				chdir((_dr = get_env(dat, "PWD=")) ? _dr : "/");
		else
			chdr_ret = chdir(_dr);
	}
	else if (str_comparison(dat->argv[1], "-") == 0)
	{
		if (!get_env(dat, "OLDPWD="))
		{
			_puts(z);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(dat, "OLDPWD=")), _putchar('\n');
		chdr_ret = /* TODO: what should this be? */
			chdir((_dr = get_env(dat, "OLDPWD=")) ? dr : "/");
	}
	else
		chdr_ret = chdir(dat->argv[1]);
	if (chdr_ret == -1)
	{
		error_print(dat, "can't cd to ");
		_eputs(dat->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(dat, "OLDPWD", get_env(dat, "PWD="));
		_setenv(dat, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _help - changes the current drectory of the process
 * @dat: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _help(data_t *dat)
{
	char **arg_array;

	arg_array = dat->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
