#include "minishell.h"

extern int	g_status;

int	execution_env(t_command *command)
{
	if (!command->arguments[0])
		return (g_status = 0, 1);
	if (!strncmp(command->arguments[0], "cd", 3))
		return (cd_ms(command), 1);
	if (!strncmp(command->arguments[0], "export", 7))
		return (export_ms(command), 1);
	if (!strncmp(command->arguments[0], "unset", 6))
		return (unset_ms(command), 1);
	if (!strncmp(command->arguments[0], "exit", 5))
		return (exit_ms(command), 1);
	return (0);
}

void	execution_command(t_command *command)
{
	if (!strncmp(command->arguments[0], "echo", 5))
		return (echo_ms(command));
	if (!strncmp(command->arguments[0], "pwd", 4))
		return (pwd_ms(command));
	if (!strncmp(command->arguments[0], "env", 4))
		return (env_ms(command));
	another_command(command);
}
