#include <minishell.h>

int	parentesis_number(t_pipeline *pipelines)
{
	int	i;
	int	count;
	int	number;

	i = 1;
	count = 1;
	number = 1;
	while (count != 0)
	{
		if (pipelines[i].start_priority)
		{
			count++;
			number++;
		}
		if (pipelines[i].end_priority)
			count--;
		i++;
	}
	return (number);
}

void	parenthesis(t_pipeline *pipelines, int *index)
{
	int	i;
	int	number;
	int	end;

	number = parenthesis_number(pipelines);
	i = 0;
	if (pipelines[i].start_priority)
	{
		while (number != 0)
		{
			if (pipelines[i].end_priority)
				number--;
			i++;
		}
		i++;
	}
	*index = i;
}
