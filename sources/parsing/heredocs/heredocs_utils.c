/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:33 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:46:08 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_heredoc_limit(char **line, char *heredoc_limit)
{
	skip_spaces(line);
	heredoc_limit = dup_line_word(line);
	return (heredoc_limit);
}

int	write_to_heredoc_fd(int fd, char *heredoc_line)
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
			continue ;
		}
		write(fd, heredoc_line, 1);
		heredoc_line++;
	}
	write(fd, "\n", 1);
	return (0);
}

int	read_user_input(int fd, char *limit)
{
	int		limit_len;
	char	*heredoc_line;

	limit_len = ft_strlen(limit);
	heredoc_line = readline("> ");
	while (heredoc_line)
	{
		if (!ft_strncmp(limit, heredoc_line, limit_len + 1))
			return (0);
		else if (write_to_heredoc_fd(fd, heredoc_line))
			return (free(heredoc_line), ENOMEM);
		free(heredoc_line);
		heredoc_line = readline("> ");
	}
	return (-1);
}

int	do_the_heredocs(t_heredoc_fds *heredoc_fds, char **limits, int *i)
{
	int		status;

	status = 0;
	while (limits[*i] && status != -1)
	{
		status = read_user_input(heredoc_fds[*i].fds[1], limits[*i]);
		if (status == ENOMEM)
			return (ENOMEM);
		close(heredoc_fds[*i].fds[1]);
		close(heredoc_fds[*i].fds[0]);
		heredoc_fds[*i].fds[1] = 0;
		heredoc_fds[*i].fds[0] = 0;
		*i += 1;
	}
	return (status);
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
