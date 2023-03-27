#include "minishell.h"

extern int	g_status;

void	pipeline_start(t_command *commands, int fd[2])
{
	if (commands[1].is_end)
		set_pipe(commands, fd);
	else
	{
		commands->position = 2;
		commands->file_close = -1;
	}
}

void	fork_command(t_command *command)
{
	pid_t	pid;

	if (!execution_env(command))
	{
		pid = fork();
		if (pid == -1)
			return (g_status = ECHILD, ft_putstr_fd("fork failed\n", 2));
		if (pid == 0)
			execution_command(command);
	}
}

int	until_last_command(t_command *commands, int fd[2])
{
	int	i;

	i = 1;
	if (close(fd[1]) == -1)
		ft_putstr_fd("error close\n", 2);
	if (commands[i].position == 0)
		i = multi_pipes(commands, &fd[0]);
	return (i);
}

int	is_child(t_command command)
{
	if (!command.arguments[0])
		return (g_status = 0, 0);
	if (!strncmp(command.arguments[0], "cd", 3))
		return (g_status = 0, 0);
	if (!strncmp(command.arguments[0], "export", 7))
		return (g_status = 0, 0);
	if (!strncmp(command.arguments[0], "unset", 6))
		return (g_status = 0, 0);
	if (!strncmp(command.arguments[0], "exit", 5))
		return (g_status = 0, 0);
	return (1);
}

void	end_of_pipeline(t_command *commands, int fd[2])
{
	int	i;

	i = -1;
	if (commands[1].is_end && close(fd[0]) == -1)
		ft_putstr_fd("error close\n", 2);
	while (commands[++i].is_end)
		if (is_child(commands[i]) && waitpid(-1, &g_status, 0) == -1)
			ft_putstr_fd("error waitpid\n", 2);
}