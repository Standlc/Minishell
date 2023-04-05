#include "minishell.h"

int	g_status;

void	show_data(t_pipeline pipeline)
{
	int	j = 0;
	int	k = 0;

	if (pipeline.commands)
	{
		while (pipeline.commands[j].is_end)
		{
			printf("{\n");
			if (pipeline.commands[j].arguments)
				printf("\tname: %s\n", pipeline.commands[j].arguments[0]);
			k = 1;
			printf("\targuments: [");
			while (pipeline.commands[j].arguments && pipeline.commands[j].arguments[k])
			{
				printf("%s, ", pipeline.commands[j].arguments[k]);
				k++;
			}
			printf("]\n");
			printf("\tinput: %d\n", pipeline.commands[j].input_file);
			printf("\touput: %d\n", pipeline.commands[j].output_file);
			printf("\tis_end: %d\n", pipeline.commands[j].is_end);
			printf("}\n");
			j++;
		}
	}
	printf("parenthesis: %d\n", pipeline.parenthesis);
	printf("operator: %d\n", pipeline.operator);
}

char	*readline_handler(void)
{
	char	*prompt;
	char	*line;

	if (g_status)
		prompt = PROMPT_ERROR;
	else
		prompt = PROMPT;
	line = readline(prompt);
	return (line);
}

int	check_signal_stop(t_pipeline *pipeline)
{
	int	i;
	
	if (!pipeline->commands)
		return (0);
	i = 0;
	while (pipeline->commands[i].is_end)
	{
		if (pipeline->commands[i].signal_stop)
			return (1);
		i++;
	}
	return (0);
}

int	execute_command_line(char *line, t_heredoc_fds *heredoc_fds)
{
	int				pipeline_error;
	t_pipeline		pipeline;
	char			*line_ptr;
	t_heredoc_fds	*heredocs_ptr;

	heredocs_ptr = heredoc_fds;
	line_ptr = line;
	while (*line)
	{
		pipeline_error = get_pipeline(&line, &pipeline, &heredoc_fds);
		if (pipeline_error == ENOMEM)
			return (ENOMEM);
		if (pipeline.commands)
			execute_pipeline(pipeline, &(t_blocks){line_ptr, heredocs_ptr});
		if (check_signal_stop(&pipeline))
			return (free_pipeline(pipeline), 0);
		skip_pipelines_to_not_execute(&line, pipeline, heredoc_fds);
		free_pipeline(pipeline);
	}
	return (0);
}

int	start_minishell(void)
{
	char			*line;
	t_heredoc_fds	*heredoc_fds;

	line = readline_handler();
	while (line)
	{
		if (*line)
			add_history(line);
		if (!check_syntax(line))
		{
			heredoc_fds = handle_heredocs(line);
			if (!heredoc_fds)
				return (free(line), 1);
			if (g_status == SIGINT_HEREDOC)
				g_status = 130;
			else if (execute_command_line(line, heredoc_fds))
				return (close_heredoc_fds(heredoc_fds), free(heredoc_fds), 1);
			close_heredoc_fds_outs(heredoc_fds);
			free(heredoc_fds);
			free(line);
		}
		hook_signals();
		line = readline_handler();
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	**minishell_env;

	(void)argc;
	(void)argv;
	// if (!isatty(0) || !isatty(1) || !isatty(2))
	// {
	// 	ft_putstr_fd("stdin, stdout or stderr have been changed\n", 2);
	// 	return (ENOTTY);
	// }
	hook_signals();
	g_status = 0;
	minishell_env = duplicate_bigarray(env);
	if (g_status != 0)
		exit(g_status);
	(void)environnement(minishell_env);
	start_minishell();
	minishell_env = *(environnement(NULL));
	free_str_arr(minishell_env);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	return (g_status);
}

// export GHOST=123 | env | grep GHOST

// void rl_clear_history(void){}
// void rl_replace_line(char *s, int n){(void)s;(void)n;}