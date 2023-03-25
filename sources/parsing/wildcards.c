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

// int	check_slash()
// {
// }

char	**read_dir(char *wildcard, char **arguments, int size)
{
	int				i;
	struct dirent	*directory_content;
	DIR				*directory;

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
				return (NULL);
			arguments[i] = NULL;
			arguments[i] = strjoin_handler(arguments[i], directory_content->d_name);
			if (!arguments[i])
				return (NULL);
			// ADD TO END "/" IF NEEDED
			i++;
		}
		directory_content = readdir(directory);
	}
	closedir(directory);
	//SORT
	if (i == size)
	{
		arguments = ft_realloc(arguments, i + 2, sizeof(char *), ARGUMENTS);
		if (!arguments)
			return (NULL);
		arguments[i] = NULL;
		arguments[i] = strjoin_handler(arguments[i], wildcard);
		if (!arguments[i])
			return (NULL);
	}
	return (arguments);
}
