#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_pipe(char *line)
{
	return (*line == '|' && *(line + 1) != '|');
}

int	is_redirection(char *line)
{
	if (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2))
		return (2);
	if (*line == '<' || *line == '>')
		return (1);
	return (0);
}

int	is_parenthesis(char *line)
{
	return (*line == '(' || *line == ')');
}

int	is_env_var(char *line, char quote_type)
{
	return (*line == '$' && *(line + 1) && *(line + 1) != ' ' && *(line + 1) != '"' && quote_type != '\'');
}

void	*ft_realloc_args(char **ptr, int nmemb, int size)
{
	char	**res;
	int		i;

	res = ft_calloc(nmemb, size);
	if (!res || !ptr)
		return (res);
	i = 0;
	while (i < nmemb - 1)
	{
		res[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (res);
}

void	*ft_realloc_commands(t_command *ptr, int nmemb, int size)
{
	t_command	*res;
	int			i;

	res = ft_calloc(nmemb, size);
	if (!res || !ptr)
		return (res);
	i = 0;
	while (i < nmemb - 1)
	{
		res[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (res);
}

void	*ft_realloc(t_pipeline *ptr, int nmemb, int size)
{
	t_pipeline	*res;
	int			i;

	res = ft_calloc(nmemb, size);
	if (!res || !ptr)
		return (res);
	i = 0;
	while (i < nmemb - 1)
	{
		res[i] = ptr[i];
		// *(char *)(res + i) = *(char *)(ptr + i);
		i++;
	}
	free(ptr);
	return (res);
}

void	get_operator(char **line, t_pipeline *pipeline)
{
	skip_spaces(line);
	if (!is_operator(*line))
		return ;
	if (!ft_strncmp(*line, "&&", 2))
		pipeline->operator = AND;
	else if (!ft_strncmp(*line, "||", 2))
		pipeline->operator = OR;
	*line += 2;
	skip_spaces(line);
}

char	*get_env_var_name(char **line)
{
	int		i;
	char	*env_var_name;

	env_var_name = malloc(10 + 1);
	if (!env_var_name)
		return (NULL);
	i = 0;
	while (**line && **line != '$' && !is_quote(**line) && **line != ' ')
	{
		env_var_name[i] = **line;
		i++;
		*line += 1;
	}
	env_var_name[i] = '\0';
	return (env_var_name);
}

char	*handle_env_var(char **line, char *str)
{
	char	*env_var_value;
	char	*env_var_name;
	char	*res;

	*line += 1;
	env_var_name = get_env_var_name(line);
	env_var_value = getenv(env_var_name);
	res = ft_strjoin(str, env_var_value);
	free(env_var_name);
	free(str);
	if (!res)
		return (NULL);
	return (res);
}

char *handle_quotes_copy(char **line, char *str, char quote_type)
{
	int		i;

	*line += 1;
	i = ft_strlen(str);
	while (**line && **line != quote_type)
	{
		if (is_env_var(*line, quote_type))
		{
			str[i] = 0;
			str = handle_env_var(line, str);
			if (!str)
				return (NULL);
			i = ft_strlen(str);
			if (!**line || **line == quote_type)
				break ;
		}
		str[i] = **line;
		(*line)++;
		i++;
	}
	*line += 1;
	return (str);
}

char	*copy_line_word(char **line)
{
	char	*str;
	int		i;

	skip_spaces(line);
	str = ft_calloc(100 + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (**line && **line != ' ' && !is_operator(*line) && !is_pipe(*line) && !is_redirection(*line))
	{
		if (is_env_var(*line, 0))
		{
			str = handle_env_var(line, str);
			if (!str)
				return (NULL);
			i = ft_strlen(str);
		}
		else if (is_quote(**line))
		{
			str = handle_quotes_copy(line, str, **line);
			if (!str)
				return (free(str), NULL);
			i = ft_strlen(str);
		}
		else
		{
			str[i] = **line;
			(*line)++;
			i++;
		}
	}
	skip_spaces(line);
	return (str);
}

int	get_arguments(char **line, t_command *command)
{
	int	i;

	i = 0;
	while (**line && !is_operator(*line) && !is_pipe(*line) && **line != '&' && !is_parenthesis(*line))
	{
		command->arguments = ft_realloc_args(command->arguments, (i + 2), sizeof(char *));
		if (!command->arguments)
			return (1);
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
	if (get_redirections(line, command))
		return (1);
	command->name = copy_line_word(line);
	if (!command->name)
		return (1);
	if (get_arguments(line, command))
		return (1);
	*line += is_pipe(*line);
	skip_spaces(line);
	return (0);
}

int	get_pipeline(char **line, t_pipeline *pipeline)
{
	int	i;

	get_operator(line, pipeline);
	// if (**line == '(')
	// {
	// 	while (**line == '(')
	// 		*line += 1;
	// 	pipeline->start_priority = 1;
	// }
	i = 0;
	while (**line && !is_operator(*line))
	{
		pipeline->commands = ft_realloc_commands(pipeline->commands, (i + 2), sizeof(t_command));
		if (!pipeline->commands)
			return (1);
		if (get_command(line, pipeline->commands + i))
			return (1);
		i++;
	}
	return (0);
}

t_pipeline	*parse_line(char *line)
{
	t_pipeline	*pipelines;
	int			i;

	if (!line || check_syntax(line))
		return (NULL);
	pipelines = NULL;
	i = 0;
	while (*line)
	{
		pipelines = ft_realloc(pipelines, i + 2, sizeof(t_pipeline));
		if (!pipelines)
			return (NULL);
		if (get_pipeline(&line, pipelines + i))
			return (free_pipelines(pipelines), pipelines = NULL, NULL);
		i++;
	}
	return (pipelines);
}

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