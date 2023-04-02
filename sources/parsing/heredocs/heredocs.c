/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:36 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/02 14:29:06 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

char	*get_heredoc_limit(char **line, char *heredoc_limit)
{
	skip_spaces(line);
	heredoc_limit = dup_line_word(line);
	return (heredoc_limit);
}

char	**get_heredoc_limits(char *line, char **limits)
{
	int	i;

	limits = malloc((get_heredoc_amount(line) + 1) * sizeof(char **));
	if (!limits)
		return (NULL);
	i = 0;
	while (*line)
	{
		if (is_quote(*line))
			check_quotes(&line);
		else if (is_heredoc(line))
		{
			line += 2;
			limits[i] = get_heredoc_limit(&line, limits[i]);
			if (!limits[i])
				return (free_str_arr(limits), NULL);
			i++;
		}
		else
			line++;
	}
	limits[i] = NULL;
	return (limits);
}

t_heredoc_fds *get_heredoc_fds(char *line, t_heredoc_fds *heredoc_fds)
{
	int	i;
	int	size;

	size = get_heredoc_amount(line);
	heredoc_fds = malloc((size + 1) * sizeof(t_heredoc_fds));
	if (!heredoc_fds)
		return (NULL);
	heredoc_fds[size].fds[0] = -1;
	i = 0;
	while (*line)
	{
		if (is_quote(*line))
			check_quotes(&line);
		else if (is_heredoc(line))
		{
			if (pipe(heredoc_fds[i].fds) == -1)
				return (free(heredoc_fds), NULL);
			line += 2;
			while (*line && !is_heredoc(line) && !is_quote(*line))
				line++;
			i++;
		}
		else
			line++;
	}
	return (heredoc_fds);
}

int	heredoc_child(t_heredoc_fds *heredoc_fds, char **limits)
{
	signal(SIGINT, SIG_DFL);
	do_the_heredoc(heredoc_fds, limits);
	exit(g_status);
}

t_heredoc_fds	*handle_heredocs(char *line, t_heredoc_fds *heredoc_fds)
{
	pid_t	pid;
	char	**limits;
	int		status_waitpid;

	heredoc_fds = get_heredoc_fds(line, heredoc_fds);
	if (!heredoc_fds)
		return (NULL);
	limits = NULL;
	limits = get_heredoc_limits(line, limits);
	if (!limits)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);

	if (pid == 0)
	{
		heredoc_child(heredoc_fds, limits);
	}

	for (int x= 0; heredoc_fds[x].fds[0] != -1; x++)
		close (heredoc_fds[x].fds[1]);

	if (waitpid(pid, &status_waitpid, 0) == -1)
		return (NULL);

	// if (WIFSIGNALED(status_waitpid))
	// 	g_status = 128 + WTERMSIG(status_waitpid);
	// else if (WIFEXITED(status_waitpid))
	// 	g_status = WEXITSTATUS(status_waitpid);

	free_str_arr(limits);
	return (heredoc_fds);
}

// << a"s" -> limit: as