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
		if (!*wildcard)
			return (1);
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

int	is_match(char *curr_dir_wildcard, int is_directory_match, char *file)
{
	if (is_directory_match && !is_directory(file))
			return (0);
	if (curr_dir_wildcard[0] != '.' && file[0] == '.')
		return (0);
	while (*file)
	{
		if (compare(curr_dir_wildcard, file))
				return (1);
		file++;
	}
	return (0);
}

char	**get_matches(DIR *directory, char *wildcard, char **matches)
{
	char			*curr_dir_wildcard;
	struct dirent	*entry;
	int				i;
	int				is_directory_match;

	curr_dir_wildcard = get_curr_dir_wildcard(wildcard, &is_directory_match);
	if (!curr_dir_wildcard)
		return (closedir(directory), NULL);
	matches = ft_calloc(wildcard_matches_amount(curr_dir_wildcard, is_directory_match) + 1, sizeof(char **));
	if (!matches)
		return (free(curr_dir_wildcard), closedir(directory), NULL);
	entry = readdir(directory);
	i = 0;
	while (entry)
	{
		if (is_match(curr_dir_wildcard, is_directory_match, entry->d_name))
		{
			if (is_directory_match)
				matches[i] = strjoin_handler(ft_strdup(entry->d_name), "/");
			else
				matches[i] = ft_strdup(entry->d_name);
			if (!matches[i])
				return (free_str_arr(matches), NULL);
			i++;
		}
		entry = readdir(directory);
	}
	return (matches);
}

char	**read_dir(char *wildcard)
{
	char	**matches;
	DIR		*directory;

	directory = opendir(".");
	if (!directory)
		return (printf("error\n"), NULL);
	matches = NULL;
	matches = get_matches(directory, wildcard, matches);
	if (!matches)
		return (closedir(directory), NULL);
	sort(matches, str_arr_size(matches));
	return (closedir(directory), matches);
}
