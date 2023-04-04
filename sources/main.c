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

char	***environnement(char **new_env)
{
	static char	**env = NULL;

	if (new_env)
		env = new_env;
	return (&env);
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

int	execute_command_line(char *line)
{
	int				pipeline_error;
	t_pipeline		pipeline;
	char			*line_ptr;
	t_heredoc_fds	*heredocs_ptr;
	t_heredoc_fds	*heredoc_fds;

	heredoc_fds = handle_heredocs(line);
	if (!heredoc_fds)
		return (free(line), 1);
	heredocs_ptr = heredoc_fds;
	line_ptr = line;
	while (*line)
	{
		pipeline_error = get_pipeline(&line, &pipeline, &heredoc_fds);
		if (pipeline_error && errno == ENOMEM)
			break ;
		else if (!pipeline_error)
		{
			show_data(pipeline);
			// execute_pipeline(pipeline);
		}
		skip_pipelines_to_not_execute(&line, pipeline, heredoc_fds);
		free_pipeline(pipeline);
	}
	close_heredoc_fds_outs(heredocs_ptr);
	free(heredocs_ptr);
	free(line_ptr);
	return (0);
}

int	start_minishell(void)
{
	char			*line;

	line = readline_handler();
	while (line)
	{
		if (*line)
			add_history(line);
		if (!check_syntax(line))
		{
			if (execute_command_line(line))
				return (1);
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

// WILDCARDS REDIRECTIONS
// CHECK REDIRECTIONS FILE
// EXIT: SORTIE STD OU ERROR?


// int	get_line(t_data *data)
// {
// 	t_heredoc_fds	*heredoc_fds;
// 	char			*line;

// 	line = readline_handler();
// 	while (line)
// 	{
// 		if (*line)
// 			add_history(line);
// 		if (!check_syntax(line))
// 		{
// 			heredoc_fds = handle_heredocs(data, line);
// 			if (!heredoc_fds)
// 				return (free(line), 1);
// 			data->pipelines = parse_line(line, heredoc_fds);
// 			if (!data->pipelines)
// 				return (free(line), 1);
// 			close_heredoc_fds_outs(heredoc_fds);
// 			free(heredoc_fds);
// 			free(line);
// 			show_data(data->pipelines);
// 			// execution_global(data->pipelines);
// 			free_pipelines(data->pipelines);
// 		}
// 		line = readline_handler();
// 	}
// 	return (0);
// }