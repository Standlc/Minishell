/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:33 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/02 13:09:33 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_write(int fd, char *heredoc_line)
{
	char	**env_var_values;

	while (*heredoc_line)
	{
		if (is_env_var(heredoc_line, 0))
		{
			env_var_values = handle_env_var(&heredoc_line, 1);
			if (!env_var_values)
				return (1);
			write(fd, env_var_values[0], ft_strlen(env_var_values[0]));
			free_str_arr(env_var_values);
		}
		else
		{
			write(fd, heredoc_line, 1);
			heredoc_line++;
		}
	}
	write(fd, "\n", 1);
	return (0);
}

int	read_heredoc(int fd, char *limit)
{
	int		limit_len;
	char	*heredoc_line;

	limit_len = ft_strlen(limit);
	heredoc_line = readline("> ");
	while (heredoc_line)
	{
		if (!ft_strncmp(limit, heredoc_line, limit_len + 1))
			return (0);
		else if (handle_write(fd, heredoc_line))
			return (1);
		free(heredoc_line);
		heredoc_line = readline("> ");
	}
	return (0);
}

t_heredoc_fds	*do_the_heredoc(t_heredoc_fds *heredoc_fds, char **limits)
{
	int		size;
	int		i;

	size = str_arr_size(limits);
	i = 0;
	while (limits[i])
	{
		if (read_heredoc(heredoc_fds[i].fds[1], limits[i]))
			return (close_heredoc_fds(heredoc_fds), free(heredoc_fds), NULL);
		close(heredoc_fds[i].fds[1]);
		close(heredoc_fds[i].fds[0]);
		i++;
	}
	return (heredoc_fds);
}

int	get_heredoc_amount(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (is_heredoc(line))
		{
			line += 2;
			while (*line && !is_heredoc(line))
				line++;
			count++;
		}
		else
			line++;
	}
	return (count);
}
