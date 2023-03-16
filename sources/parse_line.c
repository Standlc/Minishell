#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*copy_line_word(char **line, int *missing_quote)
{
	char	quote_type;
	char	*str;
	int		i;

	str = malloc(20 + 1);
	if (!str)
		return (NULL);
	i = 0;
	if (is_quote(**line))
	{
		quote_type = **line;
		*line += 1;
		while (**line && **line != quote_type)
		{
			str[i] = **line;
			(*line)++;
			i++;
		}
		if (**line != quote_type)
			return (*missing_quote = 1, str);
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

int	is_pipe(char *line)
{
	return (*line == '|');
}

int	is_redirection(char *line)
{
	return (*line == '<' || *line == '>');
}

int	handle_redirection(char **line, char redirection_type, t_command *command, int *missing_quote)
{
	int	file;

	*line += 1;
	skip_spaces(line);
	if (redirection_type == '<')
	{
		command->input_file = copy_line_word(line, missing_quote);
	}
	else
	{
		command->output_file = copy_line_word(line, missing_quote);
		file = open(command->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
		{
			// handle error
		}
	}
	skip_spaces(line);
	return (0);
}

int	get_redirections(char **line, t_command *command, int *missing_quote)
{
	while (is_redirection(*line))
	{
		// printf("red\n");
		handle_redirection(line, **line, command, missing_quote);
	}
	return (0);
}

int	get_arguments(char **line, t_command *command, int *missing_quote)
{
	int	i;

	command->arguments = malloc(10 + 1);
	if (!command->arguments)
		return (1);
	i = 0;
	while (**line && !is_operator(*line) && !is_pipe(*line))
	{
		// printf("args\n");
		if (is_redirection(*line))
			get_redirections(line, command, missing_quote);
		else
			command->arguments[i] = copy_line_word(line, missing_quote);
		skip_spaces(line);
		i++;
	}
	command->arguments[i] = NULL;
	return (0);
}

// > "file" > "file" "command" arg < file arg | command " arg < file arg" && "command" arg arg > file | command " arg arg"
// rev | < a cat > b < 6.c > c | rev &&  < a echo yo > b > a | cat || ls

int	get_command(char **line, t_command *command, int *missing_quote)
{
	command->input_file = NULL;
	command->output_file = NULL;
	if (is_redirection(*line))
		get_redirections(line, command, missing_quote);
	command->name = copy_line_word(line, missing_quote);
	skip_spaces(line);
	if (!is_operator(*line) && !is_pipe(*line))
		get_arguments(line, command, missing_quote);
	if (**line == '|' && !is_operator(*line))
		*line += 1;
	skip_spaces(line);
	return (0);
}

int	get_pipeline(char **line, t_pipeline *pipeline, int *missing_quote)
{
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
		// printf("name\n");
		if (get_command(line, pipeline->commands + i, missing_quote))
			return (1);
		i++;
	}
	pipeline->last_pipeline_status = 0;
	pipeline->commands[i].name = NULL;
	return (0);
}

t_pipeline	*parse_line(char *line)
{
	int			missing_quote;
	t_pipeline	*pipelines;
	int			i;

	if (!line)
		return (NULL);
	skip_spaces(&line);
	pipelines = malloc(sizeof(t_pipeline) * (5 + 1));
	if (!pipelines)
		return (NULL);
	missing_quote = 0;
	i = 0;
	while (*line)
	{
		if (get_pipeline(&line, pipelines + i, &missing_quote))
			return (NULL);
		i++;
	}
	pipelines[i].commands = NULL;
	if (missing_quote)
	{
		print_error("missing closing quote");
		free_pipelines(pipelines);
		return (NULL);
	}
	return (pipelines);
}