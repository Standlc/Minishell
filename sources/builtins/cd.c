#include "minishell.h"

void	cd_ms(t_command *command)
{
	char	*str;

	if (command->argument[0] && command->argument[1])
		ft_putstr_fd("too many arguments", 2);
	else if (chdir(command->argument[0]) == -1)
		ft_putstr_fd("No such directory", 2);
	else
	{
		str = getenv("HOME");
		if (!str)
			ft_putstr_fd("HOME not set", 2);
		if (chdir(command->argument[0]) == -1)
			ft_putstr_fd("No such directory", 2);
	}
}
