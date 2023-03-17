#include "minishell.h"

int	validate_variable(char *argument)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argument[i]) || argument[i] != '_')
		return (0);
	i++;
	while (argument[i] && argument[i] != '=')
	{
		if (!ft_isalnum(argument[i]))
			return (0);
		i++;
	}
	if (argument[i] == '\0')
		return (0);
	return (1);
}

int	variable_count(char **arguments)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arguments[i])
	{
		if (validate_variable(arguments[i]))
			count++;
		else
			arguments[i][0] = "\0";        // leak?
		i++;
	}
	return (count);
}

char	**new_env(char **env, char **arguments)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (ft_strlen(env) + variable_count(arguments) + 1));
	if (!new)
		return (NULL);
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new)
			return (free_dup(new), NULL);
		i++;
	}
	new[i] = NULL; // leak ?
	return (new);
}

void	export_ms(t_command *command)
{
	int		i;
	char	**tmp;
	char	**new;

	i = 0;
	while (command->env[i])
		i++;
	new = new_env(command->env, command->arguments);
	if (!new)
		(ft_putstr_fd("Cannot allocate memory\n", 2), exit(errno));
	complete_env(new, command->arguments, i);
	if (!new)
		(ft_putstr_fd("Cannot allocate memory\n", 2), exit(errno));
	tmp = command->env;
	command->env = new;
	free_dup(tmp);
}
