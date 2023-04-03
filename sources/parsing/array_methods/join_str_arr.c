/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_str_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:30 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/03 03:13:01 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**str_arr_dup(char **src)
{
	char	**res;
	int		i;

	res = malloc((str_arr_size(src) + 1) * sizeof(char **));
	if (!res)
		return (NULL);
	i = 0;
	while (src[i])
	{
		res[i] = ft_strdup(src[i]);
		if (!res[i])
			return (free_str_arr(res), NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**join_arr_strjoin(char **arr1, char **arr2)
{
	int		i;
	int		j;
	char	**res;

	if (!arr2)
		return (NULL);
	res = ft_calloc(str_arr_size(arr1) + str_arr_size(arr2) + 2, sizeof(char **));
	if (!res)
		return (free_str_arr(arr1), free_str_arr(arr2), NULL);
	i = 0;
	while (arr1 && arr1[i + 1])
	{
		res[i] = arr1[i];
		i++;
	}
	res[i] = strjoin_handler(arr1[i], arr2[0]);
	free(arr2[0]);
	if (!res[i] && errno == ENOMEM)
		return (free(arr1), free_str_arr(res), free_str_arr(arr2), NULL);
	j = 1;
	while (arr2[j])
	{
		if (arr2[j][0])
			res[j + i] = arr2[j];
		else
			free(arr2[j]);
		j++;
	}
	return (free(arr1), free(arr2), res);
}

char	**join_str_arr(char **dest, char **arr2)
{
	int		dest_size;
	int		i;

	if (!arr2)
		return (NULL);
	dest_size = str_arr_size(dest);
	dest = ft_realloc(dest, dest_size, dest_size + str_arr_size(arr2) + 2);
	if (!dest)
		return (free_str_arr(arr2), NULL);
	i = 0;
	while (arr2[0] && arr2[i])
	{
		dest[dest_size + i] = arr2[i];
		i++;
	}
	return (free(arr2), dest);
}
