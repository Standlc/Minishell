#include "minishell.h"

extern int	g_status;

int	add_char(char **line, char **str)
{
	int		i;
	int		size;
	char	*res;

	size = ft_strlen(*str) + 2;
	res = ft_calloc(size, sizeof(char));
	if (!res)
		return (free(*str), 1);
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
	while (**line && (ft_isalnum(**line) || **line == '?'))
	{
		if (add_char(line, &env_var_name))
			return (NULL);
	}
	return (env_var_name);
}

char	**recursivity(char *env_var_value)
{
	char	**res;
	int		i;
	char	**str_arr;

	res = ft_calloc(1, sizeof(char **));
	if (!res)
		return (free(env_var_value), NULL);
	str_arr = ft_split(env_var_value, ' ');
	if (!str_arr)
		return (NULL);
	free(env_var_value);
	i = 0;
	while (str_arr[i])
	{
		res = join_str_arr(res, get_line_args(str_arr + i));
		i++;
	}
	return (res);
}

char	**handle_env_var(char **line, int is_inside_quotes)
{
	char	*env_var_value;
	char	*env_var_name;

	*line += 1;
	env_var_name = get_env_var_name(line);
	if (!env_var_name)
		return (NULL);
	printf("var name: %s\n", env_var_name);
	if (env_var_name[0] == '?')
		env_var_value = ft_itoa(g_status);
	else
		env_var_value = getenv_ms(env_var_name);
	printf("var name: %s\n", env_var_value);
	if (!env_var_value && errno == ENOMEM)
		return (free(env_var_name), NULL);
	if (!env_var_value)
		return (ft_calloc(1, sizeof(char **)));
	if (is_inside_quotes)
		return (ft_split(env_var_value, '\0'));
	return (ft_split(env_var_value, ' '));
	// return (recursivity(env_var_value));
}

char	**handle_quotes_copy(char **line, char quote_type)
{
	char	**env_var_values;
	char	**quotes_str;

	quotes_str = ft_calloc(2, sizeof(char **));
	if (!quotes_str)
		return (NULL);
	*line += 1;
	while (**line && **line != quote_type)
	{
		if (is_env_var(*line, quote_type))
		{
			env_var_values = handle_env_var(line, 1);
			if (!env_var_values)
				return (free(quotes_str), NULL);
			quotes_str[0] = strjoin_handler(quotes_str[0], env_var_values[0]);
			free_str_arr(env_var_values);
			if (!quotes_str[0])
				return (NULL);
		}
		else if (add_char(line, quotes_str))
			return (NULL);
	}
	*line += 1;
	return (quotes_str);
}

char	**get_line_args(char **line)
{
	char	**str_arr;

	str_arr = ft_calloc(2, sizeof(char **));
	if (!str_arr)
		return (NULL);
	skip_spaces(line);
	while (**line && **line != ' ' && !is_pipe(*line) && !is_operator(*line) && !is_redirection(*line))
	{
		if (is_env_var(*line, 0))
		{
			printf("var\n");
			str_arr = join_arr_strjoin(str_arr, handle_env_var(line, 0));
			if (!str_arr)
				return (NULL);
		}
		else if (is_quote(**line))
		{
			printf("quotes\n");
			str_arr = join_arr_strjoin(str_arr, handle_quotes_copy(line, **line));
			if (!str_arr)
				return (NULL);
		}
		else 
		{
			printf("char\n");
			if (add_char(line, str_arr))
			return (NULL);
		}
	}
	skip_spaces(line);
	return (str_arr);
}

// truc="s -a"
// l$truc != l"$truc"