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

int	is_builtins(t_command command)
{
	if (!strncmp(command->arguments[0], "cd", 3))
		return (1);
	if (!strncmp(command->arguments[0], "export", 7))
		return (1);
	if (!strncmp(command->arguments[0], "unset", 6))
		return (1);
	if (!strncmp(command->arguments[0], "exit", 5))
		return (1);
	if (!strncmp(command->arguments[0], "echo", 5))
		return (1);
	if (!strncmp(command->arguments[0], "pwd", 4))
		return (1);
	if (!strncmp(command->arguments[0], "env", 4))
		return (1);
	return (0);
}

void	set_pipe(t_command *command, int fd[2])
{
	int	i;

	i = 0;
	if (pipe(fd) == -1)
		return (g_status = errno, perror("minishell: pipe function"));
	while (command[i].is_end)
	{
		if (is_builtin(command[i]))
		{
			if (i == 0)
			{
				if (!is_standard(command[i].output_file))
					command[i].output_file = fd[1];
				command[i].file_close = fd[0];
			}
			else if (!command[i + 1].is_end && !is_builtin(command[i]))
			{
				command[i].input_file = fd[0];
				command[i].file_close = -1;
			}
			else if (!command[i + 1].is_end && is_builtin(command[i]))
			{
				command[i].input_file = fd[0];
				command[i].file_close = fd[0];
			}
		}
		else
		{

		}
		i++;
	}
}

int	multi_pipes(t_command *commands, int *fd)
{
	int	i;
	int	link[2];

	i = 1;
	while (commands[i].position == 0)
	{
		if (pipe(link) == -1)
			(g_status = errno, perror("minishell: close"));
		set_files(&commands[i], link, *fd);
		fork_command(&commands[i], i);
		if (dup2(link[0], *fd) == -1 || close(link[1]) == -1
			|| close(link[0]) == -1)
			(g_status = errno, perror("minishell: multi pipe"));
		i++;
	}
	return (i);
}
