#include "minishell.h"

extern int	g_status;

void	cd_ms(t_command *command)
{
	char	*str;

	if (command->arguments[1] && command->arguments[2])
		return (ft_putstr_fd("too many arguments\n", 2), g_status = 1, (void)0);
	if (command->arguments[1])
	{
		if (chdir(command->arguments[0]) == -1)
			return (ft_putstr_fd("No such directory\n", 2), g_status = 1, (void)0);
	}
	else
	{
		str = getenv("HOME");
		if (!str)
			return (ft_putstr_fd("HOME not set\n", 2), g_status = 1, (void)0);
		if (chdir(str) == -1)
			return (ft_putstr_fd("No such directory\n", 2), g_status = 1, (void)0);
	}
}
