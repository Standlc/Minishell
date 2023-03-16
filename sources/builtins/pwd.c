#include "minishell.h"

void	pwd(t_command *command)
{
	char	*str;

	str = getcwd(NULL, 1024);
	status = errno;
	if (!str)
	{
		if (errno == ERANGE)
			ft_putstr_fd("Path exceeds max buffer lenght.\n", 2);
		else if (errno == ENOMEM)
			ft_putstr_fd("Memory cannot be allocated for path\n", 2);
	}
	else
		ft_putstr_fd(str, 1);
	free(str);
	exit(status);
}
