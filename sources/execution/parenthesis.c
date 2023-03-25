#include <minishell.h>

void	parenthesis(t_pipeline *pipelines, int *index)
{
	int	number;
	int	i;

	i = 0;
	number = 1;
	while (number != 0)
	{
		number += pipelines[i].parenthesis;
		i++;
	}
	i++;
	*index = i;
}
