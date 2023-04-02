/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:24 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/02 14:56:39 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_heredoc_fds(t_heredoc_fds *heredoc_fds)
{
	if (!heredoc_fds)
		return ;
	while (heredoc_fds->fds[0] != -1)
	{
		// printf("%d\n", heredoc_fds->fds[0]);
		// if (*heredoc_fds > 2)
		// 	close(*heredoc_fds);
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

void	free_pipelines(t_pipeline *pipelines)
{
	int	i = 0;
	int	j = 0;

	while (pipelines[i].commands)
	{
		j = 0;
		while (pipelines[i].commands[j].is_end)
		{
			free_str_arr(pipelines[i].commands[j].arguments);
			if (pipelines[i].commands[j].input_file > 2)
				close(pipelines[i].commands[j].input_file);
			if (pipelines[i].commands[j].output_file > 2)
				close(pipelines[i].commands[j].output_file);
			j++;
		}
		free(pipelines[i].commands);
		i++;
	}
	free(pipelines);
}