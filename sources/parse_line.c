#include "minishell.h"

char	*copy_line_word(char **line)
{
	char	*str;
	int		i;

	// str = malloc(word_len(*line) + 1);
	str = malloc(20 + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (**line == '"')
	{
		*line += 1;
		while (**line && **line != '"')
		{
			str[i] = **line;
			(*line)++;
			i++;
		}
		*line += 1;
	}
	else
	{
		while (**line && **line != ' ')
		{
			str[i] = **line;
			(*line)++;
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}

void	get_operator(char **line, t_pipeline *pipeline)
{
	if (!ft_strncmp(*line, "&&", 2))
		pipeline->operator = AND;
	else if (!ft_strncmp(*line, "||", 2))
		pipeline->operator = OR;
	*line += 2;
	skip_spaces(line);
}

int	is_inside_quotes(char *line, int inside_quotes)
{
	if (!inside_quotes && *line == '"')
		return (1);
	if (inside_quotes && *line == '"')
		return (0);
}

int	is_pipe(char *line)
{
	return (*line == '|');
}

int	is_redirection(char *line)
{
	return (*line == '<' || *line == '>');
}

int	handle_redirection(char **line, char redirection_type, t_command *command)
{
	*line += 1;
	skip_spaces(line);
	if (redirection_type == '<')
	{
		command->input_file = copy_line_word(line);
		// open file
	}
	else
	{
		command->output_file = copy_line_word(line);
		// open file
	}
	skip_spaces(line);
	return (0);
}

int	get_redirections(char **line, int *inside_quotes, t_command *command)
{
	while (is_redirection(*line))
	{
		printf("red\n");
		handle_redirection(line, **line, command);
	}
	return (0);
}

int	get_arguments(char **line, int *inside_quotes, t_command *command)
{
	int	i;

	command->arguments = malloc(10 + 1);
	if (!command->arguments)
		return (1);
	i = 0;
	while (**line && !is_operator(*line) && !is_pipe(*line))
	{
		printf("args\n");
		skip_spaces(line);
		if (is_redirection(*line))
			get_redirections(line, inside_quotes, command);
		command->arguments[i] = copy_line_word(line);
		i++;
	}
	command->arguments[i] = NULL;
	return (0);
}

// > "file" > "file" "command" arg < file arg | command " arg < file arg" && "command" arg arg > file | command " arg arg"

int	get_command(char **line, int *inside_quotes, t_command *command)
{
	command->input_file = NULL;
	command->output_file = NULL;
	if (is_redirection(*line))
		get_redirections(line, inside_quotes, command);
	command->name = copy_line_word(line);
	get_arguments(line, inside_quotes, command);
	return (0);
}

int	get_pipeline(char **line, t_pipeline *pipeline)
{
	int	inside_quotes;
	int	i;

	skip_spaces(line);
	if (is_operator(*line))
		get_operator(line, pipeline);
	pipeline->commands = malloc(sizeof(t_command) * (5 + 1));
	if (!pipeline->commands)
		return (1);
	i = 0;
	while (**line && !is_operator(*line))
	{
		printf("name\n");
		if (get_command(line, &inside_quotes, pipeline->commands + i))
			return (1);
		i++;
	}
	pipeline->last_pipeline_status = 0;
	pipeline->commands[i].name = NULL;
	return (0);
}

t_pipeline	*parse_line(char *line)
{
	t_pipeline	*pipelines;
	int			i;

	if (!line)
		return (NULL);
	skip_spaces(&line);
	pipelines = malloc(sizeof(t_pipeline) * (5 + 1));
	if (!pipelines)
		return (NULL);
	i = 0;
	while (*line)
	{
		if (get_pipeline(&line, pipelines + i))
			return (NULL);
		i++;
	}
	pipelines[i].commands = NULL;
	return (pipelines);
}