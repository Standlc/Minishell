#include "minishell.h"

extern int	g_status;

void	replace_variable(char **new, char *argument, int lign)
{
	char	*tmp;

	tmp = new[lign];
	new[lign] = ft_strdup(argument);
	if (!new)
		return (ft_putstr_fd("Cannot allocate memory\n", 2), g_status = 12, (void)0);
	free(tmp);
}

int	is_variable(char **new, char *argument)
{
	int	i;
	int	j;

	i = 0;
	while (new[i])
	{
		j = 0;
		while (new[i][j] != '=')
			j++;
		if (!strncmp(new[i], argument, j))
			return (i);
		i++;
	}
	return (-1);
}

void	complete_env(char **new, char **arguments, int i)
{
	int	j;
	int	lign;

	j = 1;
	while (arguments[j])
	{
		if (arguments[j][0])
		{
			lign = is_variable(new, arguments[j]);
			if (lign == -1)
			{
				new[i] = ft_strdup(arguments[j]);
				if (!new)
					return (free_dup(new));
				i++;
				new[i] = NULL;
			}
			else
				replace_variable(new, arguments[j], lign);
		}
		j++;
	}
}