#include "minishell.h"

extern int	g_status;

int	validate_flag(t_command *command, int *i)
{
	int	j;

	j = 0;
	if (command->arguments[*i] && !strncmp(command->arguments[*i], "-n", 2))
	{
		j++;
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
			j++;
			while (command->arguments[*i][j]
				&& command->arguments[*i][j] == 'n')
				j++;
			if (command->arguments[*i][j] != '\0')
				break ;
		}
		else
			break ;
		(*i)++;
	}
}

void	close_file(int fd)
{
	if (fd < 3)
		return ;
	if (close(fd) == -1)
		perror("minishell: close");
}

void	echo_ms(t_command *command)
{
	int	i;
	int	option;

	i = 1;
	g_status = 0;
	option = validate_flag(command, &i);
	if (option == 1)
		validate_n(command, &i);
	while (command->arguments[i])
	{
		ft_putstr_fd(command->arguments[i], command->output_file);
		if (command->arguments[i + 1])
			ft_putchar_fd(' ', command->output_file);
		i++;
	}
	if (option == 0)
		ft_putchar_fd('\n', command->output_file);
}
