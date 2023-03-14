#include "minishell.h"

execution_command

void	execution_pipeline(t_pipeline pipeline)
{
	int	i;

	i = 0;
	pipeline.commands[i];
	while (pipeline.commands[i])
	{
		execution_command(pipeline.commands[i]);
		i++;
	}
}
