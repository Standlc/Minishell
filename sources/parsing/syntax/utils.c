/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:03 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/02 13:10:03 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_special_symbol(char **line)
{
	if (is_operator(*line) || is_redirection(*line) == 2)
		*line += 2;
	else if (is_pipe(*line) || **line == '&' || is_redirection(*line) == 1 || is_parenthesis(*line))
		*line += 1;
}

int	check_for_missing_quote(char *line)
{
	while (line && *line)
	{
		if (is_quote(*line))
		{
			if (check_quotes(&line))
				return (1);
		}
		else
			line++;
	}
	return (0);
}

int	check_quotes(char **line)
{
	char	quote_type;

	if (!is_quote(**line))
		return (0);
	quote_type = **line;
	*line += 1;
	while (**line && **line != quote_type)
		*line += 1;
	if (!**line)
		return (1);
	skip_spaces(line);
	*line += 1;
	return (0);
}

int	is_last_special_symbol(char *line)
{
	if (is_operator(line) || is_pipe(line) || is_redirection(line))
	{
		skip_special_symbol(&line);
		skip_spaces(&line);
		if (*line == '\0')
			return (1);
	}
	return (0);
}

int	check_operator_error(char **line)
{
	if ((**line == '&' && !is_operator(*line)) || is_last_special_symbol(*line))
		return (1);
	if (!is_pipe(*line) && !is_operator(*line) && **line != '&')
		return (0);
	skip_special_symbol(line);
	skip_spaces(line);
	return (is_pipe(*line) || is_operator(*line) || **line == '&' || **line == ')');
}

int	check_redirection_error(char **line)
{
	if (!is_redirection(*line))
		return (0);
	skip_special_symbol(line);
	skip_spaces(line);
	return ((is_meta_char(*line) && !is_quote(**line) && **line != '*') || !**line);
}
