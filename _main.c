#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	data_t dat[] = { DAT_INIT };
	int file_desc = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_desc)
			: "r" (file_desc));

	if (ac == 2)
	{
		file_desc = open(av[1], O_RDONLY);
		if (file_desc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		dat->_readfd = file_desc;
	}
	env_list_populate(dat);
	history_read(dat);
	main_shell(dat, av);
	return (EXIT_SUCCESS);
}
