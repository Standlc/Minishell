#include "minishell.h"

void	export(t_command *command)
{
	int	i;

	i = 0;
	while (command->env[i])
		i++;
	
}
