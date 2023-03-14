#include "minishell.h"

int	check_last_status(t_pipeline last)
{
	if (last.operator == AND)
	{
		if (last.last_pipeline_status)
			return (1);
		if (!last.last_pipeline_status)
			return (0);
	}
	if (last.operator == OR)
	{
		if (last.last_pipeline_status)
			return (0);
		if (!last.last_pipeline_status)
			return (1);
	}
	return (-1);
}

void	execution_global(t_pipeline *pipelines)
{
	int	i;

	i = 0;
	while (pipelines[i])
	{
		if (i == 0 || (i != 0 && !check_last_status(pipeline[i])))
			execution_pipeline(pipelines[i]);
		else if (pipelines[i + 1])
			pipelines[i + 1]->last_status = pipelines[i]->last_status;
		i++;
	}
}
