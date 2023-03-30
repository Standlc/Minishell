#include "minishell.h"

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