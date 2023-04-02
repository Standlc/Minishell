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

char	*get_heredoc_limit(char **line, char *heredoc_limit)
{
	skip_spaces(line);
	heredoc_limit = dup_line_word(line);
	return (heredoc_limit);
}

char	**get_heredoc_limits(char *line, char **limits)
{
	int	i;

	limits = ft_calloc(get_heredoc_amount(line) + 1, sizeof(char **));
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
				return (free(limits), NULL);
			i++;
		}
		else
			line++;
	}
	return (limits);
}

int	*handle_heredocs(char *line, int *heredoc_fds)
{
	char	**limits;

	if (check_for_missing_quote(line))
		return (malloc(0));
	limits = NULL;
	limits = get_heredoc_limits(line, limits);
	if (!limits)
		return (NULL);
	heredoc_fds = do_the_heredoc(heredoc_fds, limits);
	return (free_str_arr(limits), heredoc_fds);
}

// << a"s" -> limit: as