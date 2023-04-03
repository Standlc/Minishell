/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:49 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/03 03:13:09 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_char(char **line, char **str)
{
	int		i;
	int		len;
	char	*res;

	len = ft_strlen(*str);
	res = ft_calloc(len + 2, sizeof(char));
	if (!res)
		return (free(*str), 1);
	i = 0;
	while (*str && i < len)
	{
		res[i] = (*str)[i];
		i++;
	}
	res[i] = **line;
	*line += 1;
	free(*str);
	return (*str = res, 0);
}

char	**handle_quotes_copy(char **line, char quote_type)
{
	char	**str_arr;

	str_arr = ft_calloc(2, sizeof(char **));
	if (!str_arr)
		return (NULL);
	*line += 1;
	while (**line && **line != quote_type)
	{
		if (is_env_var(*line, quote_type))
		{
			str_arr = join_arr_strjoin(str_arr, handle_env_var(line, 1));
			if (!str_arr)
				return (NULL);
		}
		else if (add_char(line, str_arr))
			return (NULL);
	}
	*line += 1;
	return (str_arr);
}

char	**get_line_args(char **line)
{
	char	**str_arr;

	str_arr = ft_calloc(2, sizeof(char **));
	if (!str_arr)
		return (NULL);
	skip_spaces(line);
	while (**line && **line != ' ' && !is_pipe(*line) && !is_operator(*line) && !is_redirection(*line) && !is_parenthesis(*line))
	{
		if (is_env_var(*line, 0))
		{
			str_arr = join_arr_strjoin(str_arr, handle_env_var(line, 0));
			if (!str_arr)
				return (NULL);
		}
		else if (is_quote(**line))
		{
			str_arr = join_arr_strjoin(str_arr, handle_quotes_copy(line, **line));
			if (!str_arr)
				return (NULL);
		}
		else if (add_char(line, str_arr))
				return (NULL);
	}
	skip_spaces(line);
	// return (ft_calloc(2, sizeof(char **)));
	return (str_arr);
}

// truc="s -a"
// l$truc != l"$truc"