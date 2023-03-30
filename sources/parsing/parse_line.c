#include "minishell.h"

char	**insert_str_arr_at_index(char **arr1, char **arr2, int index)
{
	char	**res;
	int		i;
	int		j;

	if (!arr2)
		return (NULL);
	res = ft_calloc(str_arr_size(arr1) + str_arr_size(arr2) + 1, sizeof(char **));
	if (!res)
		return (NULL);
	i = 0;
	while (i < index && arr1 && arr1[i])
	{
		res[i] = arr1[i];
		i++;
	}
	j = 0;
	while (arr2 && arr2[j])
	{
		res[index + j] = arr2[j];
		j++;
	}
	while (arr1 && arr1[i + 1])
	{
		res[index + j] = arr1[i + 1];
		i++;
		j++;
	}
	return (res);
}

int	index_of_arg(char **str_arr, char *str)
{
	int	i;
	int	str_len;

	str_len = ft_strlen(str);
	i = 0;
	while (str_arr && str_arr[i])
	{
		if (!ft_strncmp(str, str_arr[i], str_len + 1))
			return (i);
		i++;
	}
	return (i);
}

char	**handle_widlcards(char **args)
{
	char	**wildcard_matches;
	char	**new_args;
	int		i;

	new_args = args;
	i = 0;
	while (args[i])
	{
		if (is_wildcard(args[i]))
		{
			wildcard_matches = read_dir(args[i]);
			if (!wildcard_matches)
				return (NULL);
			if (wildcard_matches[0])
				new_args = insert_str_arr_at_index(new_args, wildcard_matches, index_of_arg(new_args, args[i]));
			if (!new_args)
				return (NULL);
		}
		i++;
	}
	if (!new_args)
		return (args);
	return (new_args);
}

int	str_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	get_arguments(char **line, t_command *command, int **heredoc_fds)
{
	while (**line && !is_pipe(*line) && !is_operator(*line) && !is_parenthesis(*line))
	{
		if (!is_redirection(*line))
		{
			command->arguments = join_str_arr(command->arguments, get_line_args(line));
			if (!command->arguments)
				return (write(1, "7\n", 2), 1);
		}
		else if (get_redirections(line, command, heredoc_fds))
				return (write(1, "6\n", 2), 1);
		skip_spaces(line);
	}
	return (0);
}

int	get_command(char **line, t_command *command, int **heredoc_fds)
{
	command->is_end = 1;
	command->output_file = 1;
	if (get_arguments(line, command, heredoc_fds))
		return (write(1, "5\n", 2), 1);	
	if (command->arguments)
	{
		command->arguments = handle_widlcards(command->arguments);
		if (file_or_dir_check(command->arguments[0]))
			return (1);
	}
	*line += is_pipe(*line);
	skip_spaces(line);
	return (0);
}

void	handle_parenthesis(char **line, t_pipeline *pipeline, char parenthesis_type, int increment)
{
	if (**line == parenthesis_type)
	{
		skip_spaces(line);
		while (**line == parenthesis_type)
		{
			*line += 1;
			pipeline->parenthesis += increment;
			skip_spaces(line);
		}
	}
}

int	get_pipeline(char **line, t_pipeline *pipeline, int **heredoc_fds)
{
	int	i;

	get_operator(line, pipeline);
	handle_parenthesis(line, pipeline, '(', 1);
	pipeline->commands = ft_calloc(get_pipeline_commands_amount(*line) + 1, sizeof(t_command));
	if (!pipeline->commands)
		return (1);
	i = 0;
	while (**line && !is_operator(*line))
	{
		if (get_command(line, pipeline->commands + i, heredoc_fds))
			return (write(1, "2\n", 2), 1);
		handle_parenthesis(line, pipeline, ')', -1);
		i++;
	}
	return (0);
}

t_pipeline	*parse_line(char *line, int *heredoc_fds)
{
	char		*line_ptr;
	t_pipeline	*pipelines;
	int			i;

	line_ptr = line;
	if (check_syntax(line, 0))
		return (ft_calloc(1, sizeof(t_pipeline)));
	pipelines = ft_calloc(get_pipelines_amount(line) + 1, sizeof(t_pipeline));
	if (!pipelines)
		return (free(line_ptr), NULL);
	i = 0;
	while (*line)
	{
		if (get_pipeline(&line, pipelines + i, &heredoc_fds))
			return (free(line_ptr), free_pipelines(pipelines), NULL);
		i++;
	}
	return (free(line_ptr), pipelines);
}

// :
// #
// $'' $: $=
//"$'"

// cat a || (cat a && (cat b || cat a) || cat b)
// cat a || (cat a || ((cat b && cat a) || cat b))

// > "file" > "file" "command" arg < file arg | command " arg < file arg" && "command" arg arg > file | command " arg arg"
// rev | < a cat > b < 6.c > c | rev &&  < a echo yo > b > a | cat || ls
// echo "sdf$USER" -> sdfstde-la-
// echo "sdf$USERsdf" -> sdf
// echo "sdf$USER sdf" -> sdfstde-la-
// echo "sdf $USER" -> sdf stde-la- 
// com arg"$USER" -> argstan
// a"$USER"a"$USER" -> astanastan
// $USER"$USER"$USER -> stanstanstan
