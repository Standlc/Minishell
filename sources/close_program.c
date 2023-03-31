#include "minishell.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr && str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	if (str_arr)
		free(str_arr);
}

void	free_pipelines(t_pipeline *pipelines)
{
	int	i = 0;
	int	j = 0;

	while (pipelines[i].commands)
	{
		j = 0;
		while (!pipelines[i].commands[j].is_end)
		{
			free_str_arr(pipelines[i].commands[j].arguments);
			if (pipelines[i].commands[j].input_file > 2)
				close(pipelines[i].commands[j].input_file);
			if (pipelines[i].commands[j].output_file > 2)
				close(pipelines[i].commands[j].output_file);
			j++;
		}
		free(pipelines[i].commands);
		i++;
	}
	free(pipelines);
}