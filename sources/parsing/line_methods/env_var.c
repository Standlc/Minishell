#include "minishell.h"

extern int	g_status;

int	env_var_name_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && (ft_isalnum(line[len]) || line[len] == '?'))
		len++;
	return (len);
}

char	*get_env_var_name(char **line)
{
	int		i;
	char	*env_var_name;

	env_var_name = ft_calloc(env_var_name_len(*line) + 1, sizeof(char));
	if (!env_var_name)
		return (NULL);
	i = 0;
	while (**line && (ft_isalnum(**line) || **line == '?'))
	{
		env_var_name[i] = **line;
		*line += 1;
		if (env_var_name[i] == '?')
			break ;
		i++;
	}
	return (env_var_name);
}

char	**var_concatenation(char **split)
{
	char	**env_var_values;
	int		i;

	env_var_values = ft_calloc(1, sizeof(char **));
	if (!env_var_values)
		return (NULL);
	i = 0;
	while (split[i])
	{
		env_var_values = join_str_arr(env_var_values, get_line_args(split + i));
		if (!env_var_values)
			return (NULL);
		i++;
	}
	return (env_var_values);
}

char	**split_handler(char *s, char c)
{
	char	**split;

	if (!s)
		return (ft_calloc(1, sizeof(char **)));
	split = ft_split(s, c);
	free(s);
	return (split);
}

char	**handle_env_var(char **line, int is_inside_quotes)
{
	char	*env_var_value;
	char	*env_var_name;

	*line += 1;
	env_var_name = get_env_var_name(line);
	if (!env_var_name)
		return (NULL);
	if (env_var_name[0] == '?')
		env_var_value = ft_itoa(g_status);
	else
		env_var_value = getenv_ms(env_var_name);
	if (!env_var_value && errno == ENOMEM)
		return (free(env_var_name), NULL);
	if (is_inside_quotes)
		return (split_handler(env_var_value, '\0'));
	return (var_concatenation(split_handler(env_var_value, ' ')));
}
