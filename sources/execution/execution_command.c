#include "minishell.h"

int	is_builtin(t_command command)
{
	if (!strncmp(command.name, "echo", 5))
		return (1);
	if (!strncmp(command.name, "cd", 3))
		return (1);
	if (!strncmp(command.name, "pwd", 4))
		return (1);
	if (!strncmp(command.name, "export", 7))
		return (1);
	if (!strncmp(command.name, "unset", 6))
		return (1);
	if (!strncmp(command.name, "env", 4))
		return (1);
	if (!strncmp(command.name, "exit", 5))
		return (1);
	return (0);
}

void	execution_command()
{

}