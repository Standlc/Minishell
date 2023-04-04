/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:49 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 04:48:34 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_char(char **line, char **str, int is_str_arr)
{
	int		last_index;
	char	*join;

	join = ft_calloc(2, sizeof(char));
	if (!join)
		return (1);
	join[0] = **line;
	last_index = str_arr_size(str) * is_str_arr;
	if (last_index)
		last_index--;
	str[last_index] = strjoin_handler(str[last_index], join);
	*line += 1;
	free(join);
	return (str[last_index] == NULL);
}

char	*init_str_quotes(void)
{
	char	*str;

	str = malloc(1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*handle_quotes(char **line, char quote_type)
{
	char	*str;
	char	**env_var_value;

	str = init_str_quotes();
	if (!str)
		return (NULL);
	*line += 1;
	while (**line && **line != quote_type)
	{
		if (is_env_var(*line, quote_type))
		{
			env_var_value = handle_env_var(line, 1);
			if (!env_var_value)
				return (free(str), NULL);
			str = strjoin_handler(str, env_var_value[0]);
			free_str_arr(env_var_value);
			if (!str)
				return (NULL);
		}
		else if (add_char(line, &str, 0))
			return (free(str), NULL);
	}
	*line += 1;
	return (str);
}

int	line_arg_condition(char *line)
{
	return (!is_white_space(*line) && !is_pipe(line) && !is_operator(line)
		&& !is_redirection(line) && !is_parenthesis(line));
}

char	**get_line_args(char **line)
{
	char	**str_arr;

	str_arr = ft_calloc(2, sizeof(char **));
	if (!str_arr)
		return (NULL);
	while (**line && line_arg_condition(*line))
	{
		if (is_env_var(*line, 0))
		{
			str_arr = join_arr_strjoin(str_arr, handle_env_var(line, 0));
			if (!str_arr)
				return (NULL);
		}
		else if (is_quote(**line))
		{
			if (strjoin_str_arr(str_arr, handle_quotes(line, **line)))
				return (free_str_arr(str_arr), NULL);
		}
		else if (add_char(line, str_arr, 1))
				return (NULL);
	}
	return (str_arr);
}

// truc="s -a"
// l$truc != l"$truc"