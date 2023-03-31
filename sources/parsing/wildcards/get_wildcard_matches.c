#include "minishell.h"

int	is_match(char *curr_dir_wildcard, int is_directory_match, char *file)
{
	if (is_directory_match && !is_directory(file))
			return (0);
	if (curr_dir_wildcard[0] != '.' && file[0] == '.')
		return (0);
	if (curr_dir_wildcard[0] != '*')
		return (compare(curr_dir_wildcard, file));
	while (*file && !compare(curr_dir_wildcard, file))
		file++;
	return (*file);
}

int	add_match(char **match, int is_directory_match, char *entry_name)
{
	if (is_directory_match)
		*match = strjoin_handler(ft_strdup(entry_name), "/");
	else
		*match = ft_strdup(entry_name);
	return (*match == NULL);
}

char	**read_dir(char *wildcard, char **matches, int is_directory_match)
{
	DIR				*directory;
	struct dirent	*entry;
	int				i;

	directory = opendir(".");
	if (!directory)
		return (print_error("error while opening directory\n", NULL), NULL);
	entry = readdir(directory);
	i = 0;
	while (entry)
	{
		if (is_match(wildcard, is_directory_match, entry->d_name))
		{
			if (add_match(matches + i, is_directory_match, entry->d_name))
				return (NULL);
			i++;
		}
		entry = readdir(directory);
	}
	return (matches);
}

char	**get_wildcard_matches(char *wildcard)
{
	int		is_directory_match;
	char	*curr_dir_wildcard;
	char	**matches;

	curr_dir_wildcard = get_curr_dir_wildcard(wildcard, &is_directory_match);
	if (!curr_dir_wildcard)
		return (NULL);
	matches = ft_calloc(wildcard_matches_amount(curr_dir_wildcard, is_directory_match) + 1, sizeof(char **));
	if (!matches)
		return (free(curr_dir_wildcard), NULL);
	matches = read_dir(curr_dir_wildcard, matches, is_directory_match);
	free(curr_dir_wildcard);
	if (!matches)
		return (NULL);
	sort(matches, str_arr_size(matches));
	return (matches);
}
