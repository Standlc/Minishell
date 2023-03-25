#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
			i++;
		i--;
		while (i >= 0)
		{
			free(split[i]);
			i--;
		}
		free(split);
	}
}

void	*free_path(char **paths, char *fill_path, char *final_path)
{
	if (fill_path)
		free(fill_path);
	if (final_path)
		free(final_path);
	free_split(paths);
	return (NULL);
}

char	*good_path(char **paths, char *fill_path, char *final_path, char *cmd)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(final_path);
		free(fill_path);
		fill_path = ft_strjoin(paths[i], "/");
		if (!fill_path)
			return (free_path(paths, NULL, final_path));
		final_path = ft_strjoin(fill_path, cmd);
		if (!final_path)
			return (free_path(paths, fill_path, NULL));
		if (!access(final_path, X_OK))
			return (free_path(paths, fill_path, NULL), final_path);
		i++;
	}
	free_path(paths, fill_path, final_path);
	return (NULL);
}

char	*find_path(char	*env, char *cmd)
{
	char	**paths;
	char	*final_path;

	paths = NULL;
	paths = ft_split(&env[5], ':');
	if (!paths)
		return (NULL);
	final_path = good_path(paths, NULL, NULL, cmd);
	if (final_path)
		return (final_path);
	return (NULL);
}

char	*path_for_execve(char **env, char *cmd)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
			return (find_path(env[i], cmd));
		i++;
	}
	return (NULL);
}
