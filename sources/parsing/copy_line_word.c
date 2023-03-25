#include "minishell.h"

int	add_char(char **line, char **str)
{
	int		i;
	int		size;
	char	*res;

	size = ft_strlen(*str) + 2;
	res = ft_calloc(size, sizeof(char));
	if (!res)
		return (free(str), 1);
	i = 0;
	while (*str && i < size - 2)
	{
		res[i] = (*str)[i];
		i++;
	}
	if (line)
	{
		res[i] = **line;
		*line += 1;
	}
	else
		res[i] = '\0';
	if (*str)
		free(*str);
	return (*str = res, 0);
}

char	*get_env_var_name(char **line)
{
	char	*env_var_name;

	env_var_name = NULL;
	if (add_char(NULL, &env_var_name))
		return (NULL);
	while (**line && ft_isalnum(**line))
	{
		if (add_char(line, &env_var_name))
			return (NULL);
	}
	return (env_var_name);
}

char	*handle_env_var(char **line, char *str)
{
	char	*env_var_value;
	char	*env_var_name;

	*line += 1;
	env_var_name = get_env_var_name(line);
	if (!env_var_name)
		return (NULL);
	if (env_var_name[0] == '?')
		env_var_value = ft_itoa(0);
	else
		env_var_value = getenv(env_var_name);
	if (!env_var_value && errno == ENOMEM)
		return (free(env_var_name), free(str), NULL);
	str = strjoin_handler(str, env_var_value);
	free(env_var_name);
	return (str);
}

int	handle_quotes_copy(char **line, char **str, char quote_type)
{
	*line += 1;
	if (add_char(NULL, str))
		return (1);
	while (**line && **line != quote_type)
	{
		if (is_env_var(*line, quote_type))
		{
			*str = handle_env_var(line, *str);
			if (!*str)
				return (1);
		}
		else if (add_char(line, str))
			return (1);
	}
	*line += 1;
	return (0);
}

char	*copy_line_word(char **line)
{
	char	*str;

	skip_spaces(line);
	str = NULL;
	while (**line && **line != ' ' && !is_pipe(*line) && !is_operator(*line) && !is_redirection(*line) && !is_parenthesis(*line))
	{
		if (is_env_var(*line, 0))
		{
			str = handle_env_var(line, str);
			if (!str)
				return (NULL);
		}
		else if (is_quote(**line) && handle_quotes_copy(line, &str, **line))
				return (NULL);
		else if (add_char(line, &str))
			return (NULL);
	}
	skip_spaces(line);
	return (str);
}