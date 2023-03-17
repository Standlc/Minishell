#include "minishell.h"

void	env_ms(t_command *command)
{
	int	i;
	int	fd_out;

	i = -1;
	open_files(command, &fd_out);
	if (!command->env)
		return ;
	while (command->env[++i])
		ft_putstr_fd(command->env, fd_out);
	close_files(&fd_out);
}
