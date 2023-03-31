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

int	get_index_str_arr(char **str_arr, char *str)
{
	int	i;
	int	str_len;

	str_len = ft_strlen(str);
	i = 0;
	while (str_arr && str_arr[i])
	{
		if (!ft_strncmp(str, str_arr[i], str_len + 1))
			return (i);
		i++;
	}
	return (i);
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
	if (!res[i])
		return (free(arr1), free_str_arr(arr2), NULL);
	j = 1;
	while (arr2 && arr2[j])
	{
		res[j + i] = arr2[j];
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
