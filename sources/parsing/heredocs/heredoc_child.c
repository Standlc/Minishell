/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svan-de- <svan-de-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 22:07:13 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:45:26 by svan-de-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

void	exit_heredoc(int sig)
{
	t_heredoc_data	heredoc;

	(void)sig;
	heredoc = get_heredoc_data(NULL);
	free_str_arr(*(environnement(NULL)));
	close_heredoc_fds(heredoc.heredoc_fds);
	free(heredoc.heredoc_fds);
	heredoc.heredoc_fds = NULL;
	free_str_arr(heredoc.limits);
	rl_clear_history();
	exit(0);
}

void	heredoc_child(t_heredoc_data *heredoc)
{
	int	status;
	int	i;

	i = 0;
	get_heredoc_data(heredoc);
	signal(SIGINT, exit_heredoc);
	status = do_the_heredocs(heredoc->heredoc_fds, heredoc->limits, &i);
	if (status == ENOMEM)
		perror("minishell: malloc");
	else if (status == -1)
	{
		ft_putstr_fd("\nminishell: warning: ", 2);
		ft_putstr_fd("here-document delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(heredoc->limits[i - 1], 2);
		ft_putstr_fd("')\n", 2);
	}
	exit_heredoc(0);
}
