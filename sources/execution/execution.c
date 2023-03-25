#include "minishell.h"

extern int	g_status;

void	execution_command(t_command *command, t_pipe *pipes)
{
	if (!command->arguments[0])
		return ;
	if (!strncmp(command->arguments[0], "echo", 5))
		return (echo_ms(command));
	if (!strncmp(command->arguments[0], "cd", 3))
		return (cd_ms(command));
	if (!strncmp(command->arguments[0], "pwd", 4))
		return (pwd_ms(command));
	if (!strncmp(command->arguments[0], "export", 7) && command->arguments[0])
		return (export_ms(command));
	if (!strncmp(command->arguments[0], "unset", 6))
		return (unset_ms(command));
	if (!strncmp(command->arguments[0], "env", 4))
		return (env_ms(command));
	if (!strncmp(command->arguments[0], "exit", 5))
		return (exit_ms(command));
	another_command(command, pipes);
}

void	execution_pipeline(t_command *commands)
{
	int			i;
	pid_t		pid;
	t_pipe		pipes;

	i = 0;
	set_position(commands);
	if (commands[1].is_end)
		set_pipe(commands, &pipes);
	else
		commands->position = 2;
	while (commands[i].is_end)
	{
		if (i == 1)
			close(pipes.fd[1]);
		if (commands[i].position == 0)
			if (pipe(pipes.link) == -1)
				return (ft_putstr_fd("error pipe\n", 2));
		pid = fork();
		if (pid == -1)
			ft_putstr_fd("fork failed\n", 2);
		if (pid == 0)
			execution_command(&(commands[i]), &pipes);
		if (commands[i].position == 0)
			if (dup2(pipes.link[0], pipes.fd[0]) == -1 || close(pipes.link[1]) == -1
				|| close(pipes.link[0]) == -1)
				return (ft_putstr_fd("error many pipes\n", 2));
		i++;
	}
	i = -1;
	if (commands[1].is_end && close(pipes.fd[0]) == -1)
		return (ft_putstr_fd("error close\n", 2));
	while (commands[++i].is_end)
		if (waitpid(-1, NULL, 0) == -1)
			ft_putstr_fd("error waitpid\n", 2);
}

int	check_last_status(t_pipeline last)
{
	if (last.operator == AND)
	{
		if (g_status)
			return (1);
		if (!g_status)
			return (0);
	}
	if (last.operator == OR)
	{
		if (g_status)
			return (0);
		if (!g_status)
			return (1);
	}
	return (-1);
}

void	execution_global(t_pipeline *pipelines)
{
	int	i;

	i = 0;
	while (pipelines[i].commands)
	{
		if (i == 0 || (i != 0 && !check_last_status(pipelines[i])))
			execution_pipeline(pipelines[i].commands);
		else if (pipelines[i + 1].commands && pipelines[i + 1].parenthesis > 0)
		{
			parenthesis(&pipelines[i], &i);
			i++;
		}
		i++;
	}
}
