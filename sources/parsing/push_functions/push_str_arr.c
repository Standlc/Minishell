#include "minishell.h"

char	**join_arr_strjoin(char **arr1, char **arr2)
{
	int		i;
	int		j;
	char	**res;

	if (!arr2)
		return (NULL);
	res = ft_calloc((str_arr_size(arr1) + str_arr_size(arr2) + 1), sizeof(char **));
	if (!res)
		return (free_str_arr(arr1), free_str_arr(arr2), NULL);
	i = 0;
	while (arr1 && arr1[i + 1])
	{
		res[i] = arr1[i];
		i++;
	}
	res[i] = ft_strjoin(arr1[i], arr2[0]);
	if (!res[i])
		return (free_str_arr(arr1), free_str_arr(arr2), NULL);
	j = 1;
	while (arr2 && arr2[0] && arr2[j])
	{
		res[j + i] = arr2[j];
		j++;
	}
	return (free_str_arr(arr1), free_str_arr(arr2), res);
}

char	**join_str_arr(char **dest, char **arr2)
{
	int		dest_size;
	int		arr2_size;
	int		i;

	if (!arr2)
		return (NULL);
	dest_size = str_arr_size(dest);
	arr2_size = str_arr_size(arr2);
	dest = ft_realloc(dest, dest_size, dest_size + arr2_size + 1, STR_ARR);
	if (!dest)
		return (free_str_arr(arr2), NULL);
	i = 0;
	while (arr2[0] && arr2[i])
	{
		dest[dest_size + i] = arr2[i];
		i++;
	}
	return (free_str_arr(arr2), dest);
}
