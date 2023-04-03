#include "minishell.h"

extern int	g_status;

void	execution_while(t_command *commands, int fd[2])
{
	int	i;
	int	flag;

	i = 0;
	while (commands[i].is_end)
	{
		if (i == 1)
		{
			i = until_last_command(commands, fd);
			if (i == -1)
				return (commands->is_end = 2, (void)0);
			if (commands[i + 1].is_end)
				return (end_of_pipeline(commands, fd, i));
		}
		flag = fork_command(&commands[i], i);
		if (flag == 1)
			return (end_of_pipeline(commands, fd, i));
		if (flag == 2)
			return (commands->is_end = 2, (void)0);
		i++;
	}
	end_of_pipeline(commands, fd, i);
}

void	execution_pipeline(t_command *commands)
{
	int	fd[2];
	int	flag;

	flag = g_status;
	set_position(commands);
	pipeline_start(commands, fd);
	if (g_status != flag)
		return ;
	return (execution_while(commands, fd));
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

void	execute_pipeline(t_pipeline pipeline)
{
	char	**env;

	// if (!strncmp("exit", pipeline.commands->arguments[0], 5) && !pipeline.commands[1].is_end)
	// 			exit_pipeline(pipeline);
	execution_pipeline(pipeline.commands);
	if (pipeline.commands->is_end == 2)
	{
		free_pipeline(pipeline);
		env = *(environnement(NULL));
		free_str_arr(env);
		rl_clear_history();
		exit(g_status);
	}
}

void	execution_global(t_pipeline *pipelines)
{
	int		i;
	char	**env;

	i = 0;
	while (pipelines[i].commands)
	{
		if ((pipelines[i].commands->arguments && pipelines[i].commands->arguments[0] && pipelines[i].commands->arguments[0][0]) && !strncmp("exit", pipelines[i].commands->arguments[0], 5) && !pipelines[i].commands[1].is_end)
			exit_pipeline(pipelines, i);
		else if (i == 0 || !check_last_status(pipelines[i]))
		{
			execution_pipeline(pipelines[i].commands);
			if (pipelines[i].commands->is_end == 2)
				(env = *(environnement(NULL)), free_pipelines(pipelines), free_dup(env), rl_clear_history(), exit(g_status));
		}
		else if (pipelines[i + 1].commands && pipelines[i + 1].parenthesis > 0)
		{
			parenthesis(&pipelines[i], &i);
			i++;
		}
		i++;
	}
}
