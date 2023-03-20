#include "minishell.h"

int	handle_simple_left_redirection(t_command *command, char *file)
{
	command->input_file = open(file, O_WRONLY | O_TRUNC, 0644);
	if (command->output_file == -1)
		printf("minishell: %s: no such file or directory\n", file);
	return (command->output_file);
}

int	handle_simple_right_redirection(t_command *command, char *file)
{
	command->output_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->output_file == -1)
		printf("minishell: %s: could not open file\n", file);
	return (command->output_file);
}

int	handle_heredoc(t_command *command, char *file)
{
	command->input_file = open(file, O_WRONLY, 0644);
	if (command->output_file == -1)
		printf("minishell: %s: no such file or directory\n", file);
	return (command->output_file);
}

int	handle_double_right_redirection(t_command *command, char *file)
{
	command->output_file = open(file, O_WRONLY | O_CREAT, 0644);
	if (command->output_file == -1)
		printf("minishell: %s: could not open file\n", file);
	return (command->output_file);
}

int	get_redirection_type(char **line)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (DOUBLE_LEFT);
	else if (!ft_strncmp(*line, ">>", 2))
		return (DOUBLE_RIGHT);
	else if (**line == '<' && *(*line + 1) != '<')
		return (SIMPLE_LEFT);
	return (SIMPLE_RIGHT);
}

int	handle_redirection_type(t_command *command, int redirection_type, char *file)
{
	int	return_status;

	if (redirection_type == DOUBLE_LEFT)
		return_status = handle_heredoc(command, file);
	else if (redirection_type == DOUBLE_RIGHT)
		return_status = handle_double_right_redirection(command, file);
	else if (redirection_type == SIMPLE_LEFT)
		return_status = handle_simple_left_redirection(command, file);
	else
		return_status = handle_simple_right_redirection(command, file);
	return (return_status);
}

int	get_redirections(char **line, t_command *command)
{
	int		redirection_type;
	char	*file_name;

	while (is_redirection(*line))
	{
		redirection_type = get_redirection_type(line);
		*line += 1;
		*line += redirection_type == DOUBLE_LEFT || redirection_type == DOUBLE_RIGHT;
		skip_spaces(line);
		file_name = copy_line_word(line);
		if (!file_name)
			return (1);
		if (handle_redirection_type(command, redirection_type, file_name) == -1)
			return (free(file_name), 1);
		skip_spaces(line);
	}
	return (0);
}