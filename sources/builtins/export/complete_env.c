#include "minishell.h"

void	replace_variable(char *new, char *argument)
{
	char	*tmp;

	tmp = new;
	new = ft_strdup(argument);
	if (!new)
		exit(errno);
	free(tmp);
}

int	is_variable(char **new, char *argument)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (new[i])
	{
		while (new[i][j] != '=')
			j++;
		if (!strncmp(new[i], argument, j))
			return (1);
		i++;
	}
	return (0);
}

void	complete_env(char **new, char **arguments, int i)
{
	int	j;

	j = 0;
	while (arguments[j])
	{
		if (arguments[j][0])
		{
			if (!is_variable(new, arguments[j]))
			{
				new[i] = ft_strdup(arguments[j]);
				if (!new)
					return (free_dup(new));
			}
			else
				replace_variable(new[i], arguments[j]);
		}
		i++;
		j++;
		new[i] = NULL;
	}
	new[i] = NULL;
}