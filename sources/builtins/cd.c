#include "minishell.h"

extern int	g_status;

void	cd_ms(t_command *command)
{
	char	*str;

	if (command->arguments[0] && command->arguments[1])
		ft_putstr_fd("too many arguments", 2);
	else if (chdir(command->arguments[0]) == -1)
		ft_putstr_fd("No such directory", 2);
	else
	{
		str = getenv("HOME");
		if (!str)
			ft_putstr_fd("HOME not set", 2);
		if (chdir(command->arguments[0]) == -1)
			ft_putstr_fd("No such directory", 2);
	}
}
