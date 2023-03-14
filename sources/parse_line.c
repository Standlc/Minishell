#include "minishell.h"

// char	*copy_line_word(char **line)
// {
// 	char	*str;
// 	int		i;

// 	str = malloc(word_len(*line) + 1);
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (**line && **line != ' ')
// 	{
// 		str[i] = **line;
// 		(*line)++;
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// int	get_command_arguments(char **line, t_command *command)
// {
// 	int	i;

// 	command->arguments = malloc(sizeof(char **) * (get_arguments_amount(*line) + 1));
// 	if (!command->arguments)
// 		return (1);
// 	i = 0;
// 	while (**line && !is_operator(*line))
// 	{
// 		command->arguments[i] = copy_line_word(line);
// 		if (!command->arguments[i])
// 			return (1);
// 		skip_spaces(line);
// 		i++;
// 	}
// 	command->arguments[i] = NULL;
// 	return (0);
// }

// int	get_command_options(char **line, t_command *command)
// {
// 	int	i;

// 	command->options = malloc(sizeof(char **) * (get_options_amount(*line) + 1));
// 	if (!command->options)
// 		return (1);
// 	i = 0;
// 	while (**line == '-')
// 	{
// 		command->options[i] = copy_line_word(line);
// 		if (!command->options[i])
// 			return (1);
// 		skip_spaces(line);
// 		i++;
// 	}
// 	command->options[i] = NULL;
// 	return (0);
// }

// void	get_command_operator(char **line, t_command *command)
// {
// 	if (**line == '<' && *(*line + 1) != '<')
// 		command->operator = SIMPLE_LEFT;
// 	else if (**line == '>' && *(*line + 1) != '>')
// 		command->operator = SIMPLE_RIGHT;
// 	else if (**line == '|' && *(*line + 1) != '|')
// 		command->operator = PIPE;
// 	else {
// 		if (!ft_strncmp(*line, "&&", 2))
// 			command->operator = AND;
// 		else if (!ft_strncmp(*line, "||", 2))
// 			command->operator = OR;
// 		else if (!ft_strncmp(*line, "<<", 2))
// 			command->operator = DOUBLE_LEFT;
// 		else if (!ft_strncmp(*line, ">>", 2))
// 			command->operator = DOUBLE_RIGHT;
// 		(*line)++;
// 	}
// 	(*line)++;
// 	skip_spaces(line);
// }

// int	get_command(char **line, t_command *command)
// {
// 	if (is_operator(*line))
// 		get_command_operator(line, command);
// 	command->name = copy_line_word(line);
// 	if (!command->name)
// 		return (1);
// 	skip_spaces(line);
// 	if (get_command_options(line, command))
// 		return (1);
// 	if (get_command_arguments(line, command))
// 		return (1);
// 	return (0);
// }

int	parse_line(t_pipeline *pipelines, char *line)
{
	// int	i;

	// if (!line)
	// 	return (0);
	// skip_spaces(&line);
	// data->commands = malloc(sizeof(t_command) * (get_commands_amount(line) + 1));
	// if (!data->commands)
	// 	return (1);
	// i = 0;
	// while (*line)
	// {
	// 	if (get_command(&line, data->commands + i))
	// 		return (1);
	// 	i++;
	// }
	// data->commands[i].name = NULL;
	// return (0);
}