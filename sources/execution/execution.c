#include "minishell.h"

extern int	g_status;

void	execution_pipeline(t_command *commands)
{
	int	i;
	int	fd[2];
	int	flag;

	i = 0;
	flag = g_status;
	set_position(commands);
	pipeline_start(commands, fd);
	if (g_status != flag)
		return ;
	while (commands[i].is_end)
	{
		if (i == 1)
			i = until_last_command(commands, fd);
		flag = fork_command(&commands[i]);
		if (flag == 1)
			return (end_of_pipeline(commands, fd, i));
		i++;
	}
	end_of_pipeline(commands, fd, i);
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
		if (!strncmp("exit", pipelines[i].commands->arguments[0], 5) && !pipelines[i].commands[1].is_end)
			exit_pipeline(pipelines, i);
		else if (i == 0 || !check_last_status(pipelines[i]))
			execution_pipeline(pipelines[i].commands);
		else if (pipelines[i + 1].commands && pipelines[i + 1].parenthesis > 0)
		{
			parenthesis(&pipelines[i], &i);
			i++;
		}
		i++;
	}
}
