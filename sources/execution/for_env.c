#include <minishell.h>

void	free_dup(char **env_dup)
{
	int	i;

	i = 0;
	while (env_dup[i])
		i++;
	i--;
	while (i <= 0)
	{
		free(env_dup[i]);
		i--;
	}
	free(env_dup);
}

char	**duplicate_env(char **env)
{
	char	**dup_env;
	int		i;

	i = 0;
	dup_env = malloc(sizeof(char *) * (ft_strlen((const char *)env) + 1));
	if (!dup_env)
		(ft_putstr_fd("Cannot allocate memory\n", 2), exit(errno));
	while (env[i])
	{
		// if (!strncmp(env[i], "SHELL=", 6))
		// 	dup_env[i] = ft_strdup("chemin pour minishell");
		// else
		dup_env[i] = ft_strdup(env[i]);
		if (!dup_env[i])
			(free_dup(dup_env), ft_putstr_fd("Cannot allocate memory\n", 2), exit(errno));
	}
	dup_env[i] = NULL;
	return (dup_env);
}

// void	for_env(t_pipeline *pipelines)
// {
// 	int			i;
// 	int			j;

// 	i = 0;
// 	j = 0;
// 	while (pipelines[i].commands)
// 	{
// 		while (pipelines[i].commands[j].name)
// 		{
// 			pipelines[i].commands[j].env = env;
// 			j++;
// 		}
// 		i++;
// 	}
// }
