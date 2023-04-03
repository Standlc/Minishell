/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:14 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/03 16:08:10 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
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

int	file_or_dir_check(char *str)
{
	DIR				*directory;

	if (!str || !str[0] || (str[0] != '.' && str[0] != '/'))
		return (0);
	if (!access(str, F_OK))
	{
		if (access(str, X_OK))
		{
			g_status = 126;
			print_error("permission denied: ", str);
			return (1);
		}
		directory = opendir(str);
		if (directory)
		{
			g_status = 126;
			print_error("is a directory: ", str);
			return (closedir(directory), 1);
		}
		return (0);
	}
	g_status = 127;
	return (print_error("no such file or directory: ", str), 1);
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