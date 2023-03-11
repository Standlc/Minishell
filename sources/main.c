#include "minishell.h"

void	display_data(t_data *data)
{
	int	i = 0;
	printf("[\n");
	while (data->commands[i].name)
	{
		printf("	{\n");
		printf("		name: %s,\n", data->commands[i].name);
		int	h = 0;
		printf("		options: [");
		while (data->commands[i].options[h])
		{
			printf("%s, ", data->commands[i].options[h]);
			h++;
		}
		printf("\b],\n");
		h = 0;
		printf("		arguments: [");
		while (data->commands[i].arguments[h])
		{
			printf("%s, ", data->commands[i].arguments[h]);
			h++;
		}
		printf("\b],\n");
		printf("		opertor: %d\n", data->commands[i].operator);
		printf("	},\n");
		i++;
	}
	printf("\n]\n");
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;

	line = readline("minishell$>");
	while (line)
	{
		if (line && *line)
			add_history(line);
		parse_line(&data, line);
		display_data(&data);
		free_data(&data);
		free(line);
		line = readline(NULL);
	}
	return (0);
}
