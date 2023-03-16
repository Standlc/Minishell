#include "minishell.h"

void	unset(t_command *command)
{
	int	i;
	int	fd_out;

	i = -1;
	open_files(command, &fd_out);
	while (command->arguments[++i])
		ft_putstr_fd(command->arguments[i], fd_out);
}
