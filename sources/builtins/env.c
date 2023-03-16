#include "minishell.h"

void	env(t_command *command)
{
	int	i;
	int	fd_out;

	i = -1;
	open_files(command, &fd_out);
	if (!command->env)
		return (ft_putstr_fd("minishell haven't environment\n", 2));
	while (command->env[++i])
		ft_putstr_fd(command->env, fd_out);
}
