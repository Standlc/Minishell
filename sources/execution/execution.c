#include "minishell.h"

extern int	g_status;

void	execution_command(t_command *command)
{
	if (!command->name)
		return (1);
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
	another_command(command);
}

// void	set_pipe(t_pipeline *pipeline, int fd[2], int i)
// {
// 	if (i == 0 && pipeline->output_file == 1)
// 		pipeline->output_file = fd[1];
// 	if (!pipeline->command[i + 1]->name && pipeline->input_file == 0)
// 		pipeline->input_file = fd[0];
// }

void	execution_pipeline(t_pipeline *pipeline)
{
	int		i;
	pid_t	pid;
	int		fd[2];

	i = 0;
	if (pipeline->command[1]->name)
		if (pipe(fd) == -1)
			ft_putstr_fd("pipe failed\n", 2);
	while (pipeline->commands[i].name)
	{
		//set_pipe(pipeline, fd, i);
		pid = fork();
		if (pid == -1)
			ft_putstr_fd("fork failed\n", 2);
		if (pid == 0)
			execution_command(&(pipeline->commands[i]));
		i++;
	}
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
			execution_pipeline(&pipelines[i]);
		else if (pipelines[i + 1].commands && pipelines[i + 1].start_priority)
		{
			parenthesis(&pipelines[i], &i);
			i++;
		}
		i++;
	}
}
