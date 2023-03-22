#include "minishell.h"

int	handle_simple_left_redirection(t_command *command, char *file)
{
	if (command->input_file)
		close(command->input_file);
	command->input_file = open(file, O_WRONLY | O_TRUNC, 0644);
	if (command->input_file == -1)
		print_error("no such file or directory: ", file);
	return (command->input_file);
}

int	handle_simple_right_redirection(t_command *command, char *file)
{
	if (command->output_file)
		close(command->output_file);
	command->output_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->output_file == -1)
		print_error("could not open file: ", file);
	return (command->output_file);
}

char	*open_heredoc_file(t_command *command)
{
	char	*file_name;
	char	*temp_ptr;

	file_name = NULL;
	file_name = ft_strjoin(file_name, "0");
	while (!access(file_name, F_OK))
	{
		temp_ptr = file_name;
		file_name = ft_strjoin(file_name, "0");
		if (!file_name)
			return (free(temp_ptr), NULL);
		free(temp_ptr);
	}
	command->input_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->input_file == -1)
		print_error("error while opening file: ", file_name);
	return (file_name);
}

int	handle_heredoc(t_command *command, char *heredoc_limit)
{
	char	*file_name;
	char	*path;
	char	*temp_ptr;

	if (command->input_file)
		close(command->input_file);
	command->heredoc_limit = heredoc_limit;
	file_name = open_heredoc_file(command);
	if (!file_name)
		return (-1);
	path = getcwd(NULL, 0);
	if (!path)
		return (free(file_name), -1);
	temp_ptr = path;
	path = ft_strjoin(path, "/");
	if (!path)
		return (free(temp_ptr), free(file_name), -1);
	free(temp_ptr);
	temp_ptr = path;
	path = ft_strjoin(path, file_name);
	if (!path)
		return (free(temp_ptr), free(file_name), -1);
	free(temp_ptr);
	if (unlink(file_name) == -1)
		return (free(file_name), free(path), -1);
	free(file_name);
	free(path);
	return (command->input_file);
}

int	handle_double_right_redirection(t_command *command, char *file)
{
	if (command->output_file)
		close(command->output_file);
	command->output_file = open(file, O_WRONLY | O_CREAT, 0644);
	if (command->output_file == -1)
		print_error("could not open file: ", file);
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