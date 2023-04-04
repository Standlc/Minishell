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

void	execute_pipeline(t_pipeline pipeline, t_blocks *blocks)
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
		free(blocks->line_ptr);
		close_heredoc_fds_ins(blocks->heredoc_ptr);
		free(blocks->heredoc_ptr);
		exit(g_status);
	}
}
