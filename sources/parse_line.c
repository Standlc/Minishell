#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char *handle_env_var(char **line, char *str)
{
	int		i;
	char	*env_var_name;
	char	*env_var_value;
	char	*res;

	*line += 1;
	env_var_name = malloc(10 + 1);
	if (!env_var_name)
		return (NULL);
	i = 0;
	while (**line && **line != '"' && **line != ' ')
	{
		env_var_name[i] = **line;
		i++;
		*line += 1;
	}
	env_var_name[i] = '\0';
	env_var_value = getenv(env_var_name);
	res = ft_strjoin(str, env_var_value);
	free(env_var_name);
	free(str);
	if (!res)
		return (NULL);
	return (res);
}

int	is_env_var(char *line, char quote_type)
{
	return (*line == '$' && *(line + 1) && *(line + 1) != ' ' && *(line + 1) != '"' && quote_type != '\'');
}

char	*copy_line_word(char **line)
{
	char	quote_type;
	char	*str;
	int		i;

	quote_type = 0;
	skip_spaces(line);
	str = ft_calloc(20 + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (is_quote(**line))
	{
		quote_type = **line;
		*line += 1;
		while (**line && **line != quote_type)
		{
			if (is_env_var(*line, quote_type))
			{
				str[i] = 0;
				str = handle_env_var(line, str);
				i = ft_strlen(str);
				if (!**line || **line == quote_type)
					break ;
			}
			str[i] = **line;
			(*line)++;
			i++;
		}
		if (**line != quote_type)
			return (print_error("missing closing quote"), free(str), NULL);
		*line += 1;
	}
	else
	{
		while (**line && **line != ' ' && !is_quote(**line))
		{
			if (is_env_var(*line, quote_type))
			{
				str[i] = 0;
				str = handle_env_var(line, str);
				i = ft_strlen(str);
				if (!**line || **line == ' ' || is_quote(**line))
					break ;
			}
			str[i] = **line;
			(*line)++;
			i++;
		}
	}
	skip_spaces(line);
	return (str);
}

void	get_operator(char **line, t_pipeline *pipeline)
{
	if (!ft_strncmp(*line, "&&", 2))
		pipeline->operator = AND;
	else if (!ft_strncmp(*line, "||", 2))
		pipeline->operator = OR;
	*line += 2;
	skip_spaces(line);
}

int	is_pipe(char *line)
{
	return (*line == '|');
}

int	is_redirection(char *line)
{
	return (*line == '<' || *line == '>');
}

int	get_arguments(char **line, t_command *command)
{
	int	i;

	command->arguments = ft_calloc(10 + 1, sizeof(char *));
	if (!command->arguments)
		return (1);
	i = 0;
	while (**line && !is_operator(*line) && !is_pipe(*line))
	{
		if (is_redirection(*line))
		{
			if (get_redirections(line, command))
				return (1);
		}
		else
		{
			command->arguments[i] = copy_line_word(line);
			if (!command->arguments[i])
				return (1);
			i++;
		}
		skip_spaces(line);
	}
	return (0);
}

int	get_command(char **line, t_command *command)
{
	command->input_file = NULL;
	command->output_file = NULL;
	if (is_redirection(*line))
	{
		if (get_redirections(line, command))
			return (1);
	}
	command->name = copy_line_word(line);
	if (!command->name)
		return (1);
	// skip_spaces(line);
	if (!is_operator(*line) && !is_pipe(*line))
	{
		if (get_arguments(line, command))
			return (1);
	}
	if (**line == '|' && !is_operator(*line))
		*line += 1;
	skip_spaces(line);
	return (0);
}

int	get_pipeline(char **line, t_pipeline *pipeline)
{
	int	i;

	skip_spaces(line);
	if (is_operator(*line))
		get_operator(line, pipeline);
	pipeline->commands = ft_calloc((5 + 1), sizeof(t_command));
	if (!pipeline->commands)
		return (1);
	i = 0;
	while (**line && !is_operator(*line))
	{
		if (get_command(line, pipeline->commands + i))
			return (1);
		i++;
	}
	pipeline->last_pipeline_status = 0;
	return (0);
}

t_pipeline	*parse_line(char *line)
{
	t_pipeline	*pipelines;
	int			i;

	if (!line)
		return (NULL);
	// skip_spaces(&line);
	pipelines = ft_calloc((5 + 1), sizeof(t_pipeline));
	if (!pipelines)
		return (NULL);
	i = 0;
	while (*line)
	{
		if (get_pipeline(&line, pipelines + i))
			return (free_pipelines(pipelines), pipelines = NULL, NULL);
		i++;
	}
	return (pipelines);
}

// > "file" > "file" "command" arg < file arg | command " arg < file arg" && "command" arg arg > file | command " arg arg"
// rev | < a cat > b < 6.c > c | rev &&  < a echo yo > b > a | cat || ls
// echo "sdf$USER" -> sdfstde-la-
// echo "sdf$USERsdf" -> sdf
// echo "sdf$USER sdf" -> sdfstde-la-
// echo "sdf $USER" -> sdf stde-la-
