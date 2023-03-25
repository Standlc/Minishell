#include "minishell.h"

void    set_position(t_command *commands)
{
	int i;

	if (!commands[1].name)
		return ;
	i = 0;
	commands->position = -1;
	while (commands[++i].name)
			commands[i].position = 0;
	commands[i - 1].position = 1;
}

void	set_pipe(t_command *command, t_pipe *pipes)
{
	int	i;

	i = 0;
	if (pipe(pipes->fd) == -1)
		return (ft_putstr_fd("pipe failed\n", 2));
	while (command[i].name)
	{
		if (i != 0 && command[i].input_file == 0)
			command[i].input_file = pipes->fd[0];
		if (command[i + 1].name && command[i].output_file == 1)
			command[i].output_file = pipes->fd[1];
		if (command[i].position == 0)
		{
			if (command[i].input_file == 0)
				command[i].input_file = pipes->fd[0];
			if (command[i].output_file == 1)
				command[i].output_file = pipes->link[1];
		}
		i++;
	}
}
