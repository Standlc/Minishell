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

int	check(char *wildcard, char *file)
{
	if (*file == '*')
	{
		while (*file)
		{
			if (compare(wildcard, file))
				return (1);
			file++;
		}
	}
	else
	{
		if (wildcard[0] != '.' && file[0] == '.')
			return (0);
		if (compare(wildcard, file))
				return (1);
	} 
	return (0);
}

char	*clean_wildcard(char *wildcard)
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

char	**read_dir(char *arg, char **arguments, int size)
{
	int				i;
	char			*wildcard;
	struct dirent	*directory_content;
	DIR				*directory;

	wildcard = clean_wildcard(arg);
	directory = opendir("./");
	if (!directory)
		return (printf("error\n"), NULL);
	directory_content = readdir(directory);
	i = size;
	while (directory_content)
	{
		if (check(wildcard, directory_content->d_name))
		{
			arguments = ft_realloc(arguments, i + 2, sizeof(char *), ARGUMENTS);
			if (!arguments)
				return (free(wildcard), NULL);
			arguments[i] = strjoin_handler(arguments[i], directory_content->d_name);
			if (!arguments[i])
				return (free(wildcard), NULL);
			// ADD TO END "/" IF NEEDED
			i++;
		}
		directory_content = readdir(directory);
	}
	closedir(directory);
	sort(arguments + size, arguments_count(arguments + size));
	return (free(wildcard), arguments);
}
