#include "minishell.h"

extern int	g_status;

void	execution_pipeline(t_command *commands)
{
	int		i;
	int		fd[2];

	i = 0;
	set_position(commands);
	pipeline_start(commands, fd);
	while (commands[i].is_end)
	{
		if (i == 1)
			i = until_last_command(commands, fd);
		fork_command(&commands[i]);
		// if (g_status == ECHILD)
		// 	return (end_of_pipeline());
		i++;
	}
	end_of_pipeline(commands, fd);
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
