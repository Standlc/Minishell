/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:24 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/03 03:54:51 by stde-la-         ###   ########.fr       */
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

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	if (str_arr)
		free(str_arr);
}

void	free_pipeline(t_pipeline pipeline)
{
	int	j;

	j = 0;
	while (pipeline.commands[j].is_end)
	{
		free_str_arr(pipeline.commands[j].arguments);
		if (pipeline.commands[j].input_file > 2)
			close(pipeline.commands[j].input_file);
		if (pipeline.commands[j].output_file > 2)
			close(pipeline.commands[j].output_file);
		j++;
	}
	free(pipeline.commands);
}

void	free_pipelines(t_pipeline *pipelines)
{
	int	i;

	i = 0;
	while (pipelines[i].commands)
	{
		free_pipeline(pipelines[i]);
		i++;
	}
	free(pipelines);
}