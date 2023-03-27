#include "minishell.h"

int	is_wildcard(char *line)
{
	int	has_wildcard;
	int	slash_count;

	has_wildcard = 0;
	slash_count = 0;
	if (!ft_strncmp(line, "./", 2))
		line += 2;
	while (*line && *line != ' ' && !is_pipe(line) && !is_operator(line) && !is_redirection(line))
	{
		has_wildcard += *line == '*';
		slash_count += *line == '/';
		if (slash_count && *line && *line != '/')
			return (0);
		line++;
	}
	return (has_wildcard);
}

int	arguments_count(char **arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
		i++;
	return (i);
}

int	handle_wild_card(char **line, t_command *command, int index)
{
	char	*wildcard;
			printf("2\n");

	wildcard = copy_line_word(line);
	if (!wildcard)
		return (1);
	command->arguments = read_dir(wildcard, command->arguments, index);
	if (!command->arguments)
		return (free(wildcard), 1);
	if (index != arguments_count(command->arguments))
		return (free(wildcard), 0);
	command->arguments = ft_realloc(command->arguments, index + 2, sizeof(char **), ARGUMENTS);
	if (!command->arguments)
		return (free(wildcard), 1);
	command->arguments[index] = wildcard;
	return (0);
}

int	get_arguments(char **line, t_command *command)
{
	int	i;

	i = 0;
	while (**line && !is_pipe(*line) && !is_operator(*line) && !is_parenthesis(*line))
	{
		command->arguments = ft_realloc(command->arguments, (i + 2), sizeof(char *), ARGUMENTS);
		if (!command->arguments)
			return (1);
		if (is_wildcard(*line))
		{
			if (handle_wild_card(line, command, i) || (!i && is_directory(command->arguments[i])))
				return (write(1, "8\n", 2), 1);
			i = arguments_count(command->arguments);
		} 
		else if (!is_redirection(*line))
		{
			command->arguments[i] = copy_line_word(line);
			if ((!command->arguments[i] && errno == ENOMEM) || (!i && is_directory(command->arguments[i])))
				return (write(1, "7\n", 2),1);
			i++;
		}
		else if (get_redirections(line, command))
				return (write(1, "6\n", 2), 1);
		skip_spaces(line);
	}
	return (0);
}

int	get_command(char **line, t_command *command)
{
	command->is_end = 1;
	command->output_file = 1;
	if (get_arguments(line, command))
		return (write(1, "5\n", 2), 1);
	*line += is_pipe(*line);
	skip_spaces(line);
	return (0);
}

void	handle_parenthesis(char **line, t_pipeline *pipeline, char parenthesis_type, int increment)
{
	if (**line == parenthesis_type)
	{
		skip_spaces(line);
		while (**line == parenthesis_type)
		{
			*line += 1;
			pipeline->parenthesis += increment;
			skip_spaces(line);
		}
	}
}

int	get_pipeline(char **line, t_pipeline *pipeline)
{
	int	i;

	get_operator(line, pipeline);
	handle_parenthesis(line, pipeline, '(', 1);
	i = 0;
	while (**line && !is_operator(*line))
	{
		pipeline->commands = ft_realloc(pipeline->commands, (i + 2), sizeof(t_command), COMMANDS);
		if (!pipeline->commands)
			return (write(1, "1\n", 2), 1);
		if (get_command(line, pipeline->commands + i))
			return (write(1, "2\n", 2), 1);
		handle_parenthesis(line, pipeline, ')', -1);
		i++;
	}
	return (0);
}

t_pipeline	*parse_line(char *line)
{
	t_pipeline	*pipelines;
	int			i;

	if (!line || check_syntax(line, 0))
		return (NULL);
	pipelines = NULL;
	i = 0;
	while (*line)
	{
		pipelines = ft_realloc(pipelines, i + 2, sizeof(t_pipeline), PIPELINES);
		if (!pipelines)
			return (NULL);
		if (get_pipeline(&line, pipelines + i))
			return (free_pipelines(pipelines), pipelines = NULL, NULL);
		i++;
	}
	return (pipelines);
}

// :
// #
// $'' $: $=
//"$'"

// cat a || (cat a && (cat b || cat a) || cat b)
// cat a || (cat a || ((cat b && cat a) || cat b))

// > "file" > "file" "command" arg < file arg | command " arg < file arg" && "command" arg arg > file | command " arg arg"
// rev | < a cat > b < 6.c > c | rev &&  < a echo yo > b > a | cat || ls
// echo "sdf$USER" -> sdfstde-la-
// echo "sdf$USERsdf" -> sdf
// echo "sdf$USER sdf" -> sdfstde-la-
// echo "sdf $USER" -> sdf stde-la- 
// com arg"$USER" -> argstan
// a"$USER"a"$USER" -> astanastan
// $USER"$USER"$USER -> stanstanstan

// int	get_command(char **line, t_command *command)
// {
// 	command->is_end = 1;
// 	if (get_redirections(line, command))
// 		return (write(1, "3\n", 2), 1);
// 	command->name = copy_line_word(line);
// 	if ((!command->name && errno == ENOMEM) || is_directory(command->name))
// 		return (write(1, "4\n", 2), 1);
// 	if (get_arguments(line, command))
// 		return (write(1, "5\n", 2), 1);
// 	*line += is_pipe(*line);
// 	skip_spaces(line);
// 	return (0);
// }