#include "minishell.h"

extern int	g_status;

void	set_position(t_command *commands)
{
	int	i;

	i = 0;
	commands->position = -1;
	while (commands[++i].is_end)
			commands[i].position = 0;
	commands[i - 1].position = 1;
}

void	set_pipe(t_command *command, int fd[2])
{
	int	i;

	i = 0;
	if (pipe(fd) == -1)
		return (ft_putstr_fd("pipe failed\n", 2));
	while (command[i].is_end)
	{
		if (i == 0 && command[i].output_file == 1)
		{
			command[i].output_file = fd[1];
			command[i].file_close = fd[0];
		}
		if (!command[i + 1].is_end && command[i].input_file == 0)
		{
			command[i].input_file = fd[0];
			command[i].file_close = -1;
		}
		i++;
	}
}

void	set_files(t_command *command, int link[2], int fd)
{
	if (command->input_file == 0)
		command->input_file = fd;
	if (command->output_file == 1)
		command->output_file = link[1];
	command->file_close = link[0];
}

int	multi_pipes(t_command *commands, int *fd)
{
	int	i;
	int	link[2];

	i = 1;
	while (commands[i].position == 0)
	{
		if (pipe(link) == -1)
			ft_putstr_fd("pipe failed\n", 2);
		set_files(&commands[i], link, *fd);
		fork_command(&commands[i]);
		if (dup2(link[0], *fd) == -1 || close(link[1]) == -1
			|| close(link[0]) == -1)
			ft_putstr_fd("error many pipes\n", 2);
		i++;
	}
	return (i);
}
