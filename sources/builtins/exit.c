#include <minishell.h>

void	exit(t_command *command)
{
	(void)command;
	ft_putstr_fd("exit", 1);
	exit(g_status);
}
