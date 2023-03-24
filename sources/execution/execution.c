#include "minishell.h"

extern int	g_status;

void	execution_command(t_command *command, int fd[2])
{
	if (!command->name)
		return ;
	if (!strncmp(command->name, "echo", 5))
		return (echo_ms(command));
	if (!strncmp(command->name, "cd", 3))
		return (cd_ms(command));
	if (!strncmp(command->name, "pwd", 4))
		return (pwd_ms(command));
	if (!strncmp(command->name, "export", 7) && command->arguments[0])
		return (export_ms(command));
	if (!strncmp(command->name, "unset", 6))
		return (unset_ms(command));
	if (!strncmp(command->name, "env", 4))
		return (env_ms(command));
	if (!strncmp(command->name, "exit", 5))
		return (exit_ms(command));
	another_command(command, fd);
}

void	set_pipe(t_command *command, int fd[2])
{
	int	i;

	i = -1;
	while (command[++i].name)
		command[i].position = 0;
	command->position = -1;
	while (command[i].name)
	{
		if (i != 0 && command[i].input_file == 0)
			command[i].input_file = fd[0];
		if (command[i + 1].name && command[i].output_file == 1)
			command[i].output_file = fd[1];
		i++;
	}
	i--;
	command[i].position = 1;
}

void	execution_pipeline(t_command *commands)
{
	int		i;
	pid_t	pid;
	int		fd[2];

	i = 0;
	if (commands[1].name)
	{
		if (pipe(fd) == -1)
			ft_putstr_fd("pipe failed\n", 2);
		set_pipe(commands, fd);
	}
	while (commands[i].name)
	{
		pid = fork();
		if (pid == -1)
			ft_putstr_fd("fork failed\n", 2);
		if (pid == 0)
			execution_command(&(commands[i]), fd);
		i++;
	}
	i = -1;
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		return (ft_putstr_fd("error close\n", 2));
	while (commands[++i].name)
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
		else if (pipelines[i + 1].commands && pipelines[i + 1].start_priority)
		{
			parenthesis(&pipelines[i], &i);
			i++;
		}
		i++;
	}
}
