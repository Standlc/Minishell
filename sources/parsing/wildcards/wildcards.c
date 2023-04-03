/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:10 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/02 23:56:19 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**insert_str_arr_at_index(char **arr1, char **arr2, int index)
{
	char	**res;
	int		i;
	int		j;

	res = ft_calloc(str_arr_size(arr1) + str_arr_size(arr2) + 1, sizeof(char **));
	if (!res)
		return (NULL);
	i = 0;
	while (i < index && arr1 && arr1[i])
	{
		res[i] = arr1[i];
		i++;
	}
	free(arr1[i]);
	j = 0;
	while (arr2 && arr2[j])
	{
		res[index + j] = arr2[j];
		j++;
	}
	while (arr1 && arr1[i + 1])
	{
		res[index + j] = arr1[i + 1];
		i++;
		j++;
	}
	free(arr1);
	return (res);
}

char	**replace_wildcard(char **args, char *wildcard, int *insert_index)
{
	int		wildcard_matches_size;
	char	**wildcard_matches = NULL;

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

char	**handle_widlcards(char **args)
{
	char	**new_args;
	int		i;
	int		insert_index;

	if (!args)
		return (NULL);
	new_args = str_arr_dup(args);
	if (!new_args)
		return (free_str_arr(args), NULL);
	insert_index = 0;
	i = 0;
	while (args[i])
	{
		if (is_wildcard(args[i]))
		{
			new_args = replace_wildcard(new_args, args[i], &insert_index);
			if (!new_args)
				return (NULL);
		}
		else
			insert_index++;
		i++;
	}
	free_str_arr(args);
	return (new_args);
}
