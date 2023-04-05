/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:36 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 19:47:36 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

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

t_heredoc_fds	*get_heredoc_fds(char *line, t_heredoc_fds *heredoc_fds)
{
	int	i;
	int	size;

	size = get_heredoc_amount(line);
	heredoc_fds = malloc((size + 1) * sizeof(t_heredoc_fds));
	if (!heredoc_fds)
		return (NULL);
	heredoc_fds[size].is_end = 1;
	i = 0;
	while (*line)
	{
		if (is_quote(*line))
			check_quotes(&line);
		else if (is_heredoc(line))
		{
			heredoc_fds[i].is_end = 0;
			if (pipe(heredoc_fds[i].fds) == -1)
				return (free(heredoc_fds), NULL);
			line += 2;
			i++;
		}
		else
			line++;
	}
	return (heredoc_fds);
}

void	handle_sigint_parent(int sig)
{
	(void)sig;
	ft_putstr_fd("^C\n", 1);
	g_status = -1;
}

int	fork_and_wait(t_heredoc_data *heredoc)
{
	int				status_waitpid;
	pid_t			pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		heredoc_child(heredoc);
	signal(SIGINT, handle_sigint_parent);
	waitpid(pid, &status_waitpid, 0);
	hook_signals();
	close_heredoc_fds_ins(heredoc->heredoc_fds);
	return (0);
}

t_heredoc_fds	*handle_heredocs(char *line)
{
	t_heredoc_data	heredoc;

	heredoc.heredoc_fds = NULL;
	heredoc.heredoc_fds = get_heredoc_fds(line, heredoc.heredoc_fds);
	if (!heredoc.heredoc_fds)
		return (NULL);
	heredoc.limits = NULL;
	heredoc.limits = get_heredoc_limits(line, heredoc.limits);
	if (!heredoc.limits)
		return (free(heredoc.heredoc_fds), NULL);
	if (!heredoc.heredoc_fds[0].is_end)
	{
		if (fork_and_wait(&heredoc))
		{
			free_str_arr(heredoc.limits);
			free(heredoc.heredoc_fds);
			return (NULL);
		}
	}
	free_str_arr(heredoc.limits);
	return (heredoc.heredoc_fds);
}
