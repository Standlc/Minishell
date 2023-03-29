#include "minishell.h"

int	stuff(char *wildcard, char *file)
{
	int	i;

	i = 0;
	while (wildcard[i] && file[i] && wildcard[i] != '*' && file[i] == wildcard[i])
		i++;
	return (wildcard[i] == '*' || wildcard[i] == '\0');
}

int	compare(char *wildcard, char *file)
{
	if (*wildcard == '*')
	{
		while (*wildcard == '*')
			wildcard++;
		if (*wildcard)
		{
			while (*file && !stuff(wildcard, file))
				file++;
			while (*wildcard && *file && *wildcard == *file)
			{
				file++;
				wildcard++;
			}
			if (*wildcard == '*')
				return (compare(wildcard, file));
			return (*file == '\0' && *wildcard == '\0');
		}
	}
	else
	{
		if (!stuff(wildcard, file))
			return (0);
		while (*wildcard && *file && *wildcard == *file)
		{
			file++;
			wildcard++;
		}
		if (*wildcard == '*')
			return (compare(wildcard, file));
		return (*file == '\0' && *wildcard == '\0');	
	}
	return (1);
}

int	check_is_directory(char *file)
{
	DIR				*directory;

	directory = opendir(file);
	if (directory)
		return (closedir(directory), 1);
	return (0);
}

char	*clean_wildcard(char *wildcard, int *directory_wildcard)
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
	*directory_wildcard = wildcard[i] == '/';
	res[i] = '\0';
	return (res);
}

int	check(char *wildcard, char *file)
{
	int 	directory_wildcard;
	char	*current_dir_wildcard;

	current_dir_wildcard = clean_wildcard(wildcard, &directory_wildcard);
	if (directory_wildcard)
	{
		if (!check_is_directory(file))
			return (0);
	}
	if (current_dir_wildcard[0] != '.' && file[0] == '.')
		return (0);
	if (compare(current_dir_wildcard, file))
			return (1);
	return (0);
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

char	**read_dir(char *wildcard)
{
	char			**matches;
	int				i;
	struct dirent	*directory_content;
	DIR				*directory;

	matches = NULL;
	directory = opendir("./");
	if (!directory)
		return (printf("error\n"), NULL);
	directory_content = readdir(directory);
	i = 0;
	while (directory_content)
	{
		if (check(wildcard, directory_content->d_name))
		{
			matches = ft_realloc(matches, i, i + 2, STR_ARR);
			if (!matches)
				return (NULL);
			matches[i] = ft_strdup(directory_content->d_name);
			if (!matches[i])
				return (NULL);
			i++;
		}
		directory_content = readdir(directory);
	}
	if (matches)
		sort(matches, str_arr_size(matches));
	else
		matches = ft_calloc(1, sizeof(char **));
	return (closedir(directory), matches);
}
