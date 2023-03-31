#include "minishell.h"

int	is_matching_chunk(char *wildcard, char *file)
{
	int	i;

	i = 0;
	while (wildcard[i] && file[i] && wildcard[i] != '*' && file[i] == wildcard[i])
		i++;
	return (wildcard[i] == '*' || wildcard[i] == '\0');
}

int	stuff_stuff(char *wildcard, char *file)
{
	while (*file && !is_matching_chunk(wildcard, file))
		file++;
	while (*wildcard && *file && *wildcard == *file)
	{
		file++;
		wildcard++;
	}
	if (*wildcard == '*')
		return (compare(wildcard, file));
	return (*file == *wildcard);
}

int	compare(char *wildcard, char *file)
{
	if (*wildcard == '*')
	{
		while (*wildcard == '*')
			wildcard++;
		if (!*wildcard)
			return (1);
		while (*file && !stuff_stuff(wildcard, file))
			file++;
		return (*file);
	}
	if (!is_matching_chunk(wildcard, file))
		return (0);
	while (*wildcard && *file && *wildcard == *file)
	{
		file++;
		wildcard++;
	}
	if (*wildcard == '*')
		return (compare(wildcard, file));
	return (*file == *wildcard);
}

int	wildcard_matches_amount(char *curr_dir_wildcard, int is_directory_match)
{
	struct dirent	*entry;
	int				count;
	DIR				*directory;

	directory = opendir(".");
	if (!directory)
		return (printf("error\n"), 1);
	count = 0;
	entry = readdir(directory);
	while (entry)
	{
		if (is_match(curr_dir_wildcard, is_directory_match, entry->d_name))
			count++;
		entry = readdir(directory);
	}
	closedir(directory);
	return (count);
}

char	*get_curr_dir_wildcard(char *wildcard, int *is_directory_match)
{
	int		i;
	char	*res;

	res = malloc(ft_strlen(wildcard) + 1);
	if (!res)
		return (NULL);
	i = 0;
	if (!ft_strncmp(wildcard, "./", 2))
		wildcard += 2;
	while (wildcard[i] && wildcard[i] != '/')
	{
		res[i] = wildcard[i];
		i++;
	}
	*is_directory_match = wildcard[i] == '/';
	res[i] = '\0';
	return (res);
}

void	sort(char **arr, int size)
{
	char	*temp;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < size)
	{
		j = 1;
		while (j < size - i)
		{
			k = 0;
			while (arr[j - 1][k] && arr[j][k] && arr[j - 1][k] == arr[j][k])
				k++;
			if (arr[j - 1][k] > arr[j][k])
			{
				temp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}