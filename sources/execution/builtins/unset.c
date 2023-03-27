#include "minishell.h"

extern int	g_status;

void	delete_variable(char **env, int j)
{
	char	**new;
	char	**tmp;
	int		i;
	int		index_new;

	i = 0;
	index_new = 0;
	new = malloc(sizeof(char *) * bigarray_len(env));
	if (!new)
		return (ft_putstr_fd("Cannot allocate memory\n", 2), g_status = 12, (void)0);
	while (env[i])
	{
		if (i != j)
		{
			new[index_new] = ft_strdup(env[i]);
			if (!new)
				return (ft_putstr_fd("Cannot allocate memory\n", 2), g_status = 12, (void)0);
			index_new++;
		}
		i++;
	}
	new[i] = NULL;
	tmp = env;
	(void)environnement(new);
	free_dup(tmp);
}

int	valid_delete(char *argument)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argument[i]) && argument[i] != '_')
		return (0);
	i++;
	while (argument[i] && argument[i] != '=')
	{
		if (!ft_isalnum(argument[i]))
			return (0);
		i++;
	}
	if (argument[i] == '=')
		return (0);
	return (1);
}

void	delete_env(t_command *command, int i)
{
	int	j;
	int	size_arg;
	char	**new_env;

	j = 0;
	size_arg = 0;
	new_env = *(environnement(NULL));
	while (command->arguments[i][size_arg])
		size_arg++;
	size_arg++;
	while (new_env[j])
	{
		if (ft_strncmp(new_env[j], command->arguments[i], size_arg) == '=')
			delete_variable(new_env, j);
		j++;
	}
}

void	unset_ms(t_command *command)
{
	int	i;

	g_status = 0;
	i = 0;
	if (command->position != 2)
		return ;
	if (!command->arguments[1])
		return ;
	while (command->arguments[++i])
		if (valid_delete(command->arguments[i]))
			delete_env(command, i);
}