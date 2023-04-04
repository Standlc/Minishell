/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:14 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 03:37:09 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	skip_spaces(char **line)
{
	while (is_white_space(**line))
		*line += 1;
}

void	get_operator(char **line, t_pipeline *pipeline)
{
	skip_spaces(line);
	if (!is_operator(*line))
	{
		pipeline->operator = NONE;
		return ;
	}
	if (!ft_strncmp(*line, "&&", 2))
		pipeline->operator = AND;
	else if (!ft_strncmp(*line, "||", 2))
		pipeline->operator = OR;
	*line += 2;
	skip_spaces(line);
}

int	get_pipeline_commands_amount(char *line)
{
	int	count;

	count = 0;
	while (*line && !is_operator(line))
	{
		while (*line && !is_operator(line) && !is_pipe(line))
			line++;
		if (is_pipe(line))
		{
			line += 1;
			count++;
		}
		else if (is_operator(line) || !*line)
			break ;
	}
	return (count + 1);
}

int	get_pipelines_amount(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (*line && !is_operator(line))
			line++;
		if (is_operator(line))
		{
			line += 2;
			count++;
		}
	}
	return (count + 1);
}