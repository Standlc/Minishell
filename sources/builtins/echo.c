#include "minishell.h"

extern int	g_status;

int	validate_flag(t_command *command, int *i)
{
	int	j;

	j = 0;
	if (!strncmp(command->arguments[*i], "-n", 2))
	{
		while (command->arguments[*i][j] && command->arguments[*i][j] == 'n')
			j++;
		if (command->arguments[*i][j] != '\0')
			return (0);
		else
			return (++(*i), 1);
	}
	return (0);
}

void	validate_n(t_command *command, int *i)
{
	int	j;

	while (command->arguments[*i])
	{
		j = 0;
		if (!strncmp(command->arguments[*i], "-n", 2))
		{
			while (command->arguments[*i][j] && command->arguments[*i][j] == 'n')
				j++;
			if (command->arguments[*i][j] != '\0')
				break ;
		}
		else
			break ;
		(*i)++;
	}
}


void	open_files(t_command *command, int *fd_out)
{
	if (command->output_file != NULL && strncmp(command->output_file) != 2 && command->output_file != 0)
	{
		*fd_out = open(command->output_file, O_WRONLY
				| O_CREAT | O_TRUNC, 0664);
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
	else if (close(*fd_out) == -1)
		exit(g_status);
}

void	echo_ms(t_command *command)
{
	int	i;
	int	fd_out;
	int	option;

	i = 0;
	open_files(command, &fd_out);
	option = validate_option(command, &i);
	if (option == 1)
		validate_n(command, &i);
	while (command->arguments[i])
	{
		ft_putstr_fd(command->arguments[i], fd_out);
		if (command->arguments[i + 1])
			ft_putchar_fd(' ', fd_out);
		i++;
	}
	if (option == 1)
		ft_putchar_fd('\n', fd_out);
	close_files(&fd_out);
}
