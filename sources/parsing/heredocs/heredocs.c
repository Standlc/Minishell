/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:36 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/03 02:19:42 by stde-la-         ###   ########.fr       */
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
	heredoc_fds[size].is_end = 1;
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

void	heredoc_signal_handler(int sig, siginfo_t *sact, void *ptr)
{
	t_heredoc_data	*heredoc;

	(void)sig;
	(void)sact;
	heredoc = (t_heredoc_data *)ptr;
	heredoc->data->env = *(environnement(NULL));
	free_str_arr(heredoc->data->env);
	free(heredoc->heredoc_fds);
	free_str_arr(heredoc->limits);
	close_heredoc_fds(heredoc->heredoc_fds);
	// rl_clear_history();
	exit(g_status);
}

int	heredoc_child(t_heredoc_data *heredoc)
{
	struct sigaction	sact;

    sact.sa_flags = 0;
    sigemptyset(&sact.sa_mask);
	sact.sa_sigaction = heredoc_signal_handler;
	sigaction(SIGINT, &sact, NULL);
	do_the_heredoc(heredoc->heredoc_fds, heredoc->limits);
	free(heredoc->heredoc_fds);
	free_str_arr(heredoc->limits);
	close_heredoc_fds(heredoc->heredoc_fds);
	exit(g_status);
}

t_heredoc_fds	*handle_heredocs(t_data *data, char *line)
{
	t_heredoc_data	heredoc;
	pid_t			pid;
	int				status_waitpid;

	heredoc.data = data;
	heredoc.heredoc_fds = get_heredoc_fds(line, heredoc.heredoc_fds);
	if (!heredoc.heredoc_fds)
		return (NULL);
	heredoc.limits = NULL;
	heredoc.limits = get_heredoc_limits(line, heredoc.limits);
	if (!heredoc.limits)
		return (free(heredoc.heredoc_fds), NULL);
	if (!heredoc.heredoc_fds[0].is_end)
	{
		pid = fork();
		if (pid == -1)
			return (NULL);
		if (pid == 0)
			return (heredoc_child(&heredoc), NULL);
		else
			wait(&status_waitpid);
		if (WIFSIGNALED(status_waitpid))
			g_status = 128 + WTERMSIG(status_waitpid);
		else if (WIFEXITED(status_waitpid))
			g_status = WEXITSTATUS(status_waitpid);
		close_heredoc_fds_ins(heredoc.heredoc_fds);
	}
	free_str_arr(heredoc.limits);
	return (heredoc.heredoc_fds);
}

// << a"s" -> limit: as