#include "minishell.h"

void	open_files(t_command *command, int *fd_out)
{
	if (command->output_file != NULL && command->output_file != 2 && command->output_file != 0)
	{
		*fd_out = open(command->output_file, O_WRONLY
				| O_CREATE | O_TRUNC, 0664);
		if (*fd_out == -1)
			exit(g_status);
	}
	else if (command->output_file == 2)
		*fd_out = 2;
	else if (command->output_file == 0)
		*fd_out = 0;
	else
		*fd_out = 1;
}

void	close_files(int *fd_out)
{
	if (*fd_out == 1 || *fd_out == 2 || *fd_out == 0)
		return ;
	else (close(*fd_out) == -1)
		exit(g_status);
}

void	echo_ms(t_command *command, int option)
{
	int	i;
	int	fd_out;

	i = 0;
	open_files(command, &fd_out);
	if (option)
		while (!strncmp(command->arguments[i], "-n", 3))
			i++;
	while (command->argument[i])
	{
		ft_putstr_fd(command->argument[i], fd_out);
		i++;
	}
	if (option == 1)
		ft_putchar_fd('\n', fd_out);
	close_files(&fd_out);
}
