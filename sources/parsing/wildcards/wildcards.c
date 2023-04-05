/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:10 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 15:39:50 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**replace_wildcard(char **args, char *wildcard, int *insert_index)
{
	int		wildcard_matches_size;
	char	**wildcard_matches;

	wildcard_matches = get_wildcard_matches(wildcard);
	if (!wildcard_matches)
		return (free_str_arr(args), NULL);
	wildcard_matches_size = str_arr_size(wildcard_matches);
	if (wildcard_matches[0])
		args = insert_str_arr_at_index(args, wildcard_matches, *insert_index);
	*insert_index += (!wildcard_matches_size + wildcard_matches_size);
	free(wildcard_matches);
	return (args);
}

char	**handle_widlcards(char **curr_args)
{
	char	**new_args;
	int		i;
	int		insert_index;

	if (!curr_args)
		return (NULL);
	new_args = str_arr_dup(curr_args);
	if (!new_args)
		return (free_str_arr(curr_args), NULL);
	insert_index = 0;
	i = 0;
	while (curr_args[i])
	{
		if (is_wildcard(curr_args[i]))
		{
			new_args = replace_wildcard(new_args, curr_args[i], &insert_index);
			if (!new_args)
				return (free_str_arr(curr_args), NULL);
		}
		else
			insert_index++;
		i++;
	}
	return (free_str_arr(curr_args), new_args);
}

// echo "*"