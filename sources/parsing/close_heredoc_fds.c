/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc_fds.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:51:18 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 15:51:29 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc_fds_ins(t_heredoc_fds *heredoc_fds)
{
	if (!heredoc_fds)
		return ;
	while (!heredoc_fds->is_end)
	{
		if (heredoc_fds->fds[1] > 2)
			close(heredoc_fds->fds[1]);
		heredoc_fds->fds[1] = 0;
		heredoc_fds++;
	}
}

void	close_heredoc_fds_outs(t_heredoc_fds *heredoc_fds)
{
	if (!heredoc_fds)
		return ;
	while (!heredoc_fds->is_end)
	{
		if (heredoc_fds->fds[0] > 2)
			close(heredoc_fds->fds[0]);
		heredoc_fds->fds[0] = 0;
		heredoc_fds++;
	}
}

void	close_heredoc_fds(t_heredoc_fds *heredoc_fds)
{
	if (!heredoc_fds)
		return ;
	while (!heredoc_fds->is_end)
	{
		if (heredoc_fds->fds[0] > 2)
			close(heredoc_fds->fds[0]);
		heredoc_fds->fds[0] = 0;
		if (heredoc_fds->fds[1] > 2)
			close(heredoc_fds->fds[1]);
		heredoc_fds->fds[1] = 0;
		heredoc_fds++;
	}
}
