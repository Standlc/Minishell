#include "minishell.h"

char	*open_heredoc_file(t_command *command)
{
	char	*file_name;

	file_name = NULL;
	file_name = ft_strjoin(file_name, "0");
	while (!access(file_name, F_OK))
	{
		file_name = strjoin_handler(file_name, "0");
		if (!file_name)
			return (NULL);
	}
	command->input_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->input_file == -1)
	{
		print_error("error while opening file: ", file_name);
		return (free(file_name), NULL);
	}
	return (file_name);
}

char	*dup_line_word(char **line)
{
	char	*str;

	str = NULL;
	while (**line && **line != ' ' && !is_pipe(*line) && !is_operator(*line) && !is_redirection(*line))
	{
		if (add_char(line, &str))
			return (NULL);
	}
	return (str);
}

int	handle_heredoc(char **line, t_command *command)
{
	int		size;
	char	*file_name;
	char	*path;

	if (command->input_file > 2)
		close(command->input_file);
	size = str_arr_size(command->heredoc_limits);
	command->heredoc_limits = ft_realloc(command->heredoc_limits, size, size + 2, STR_ARR);
	if (!command->heredoc_limits)
		return (1);
	command->heredoc_limits[size] = dup_line_word(line);
	if (!command->heredoc_limits[size])
		return (1);
	file_name = open_heredoc_file(command);
	if (!file_name)
		return (-1);
	path = getcwd(NULL, 0);
	if (!path)
		return (free(file_name), -1);
	path = strjoin_handler(path, "/");
	if (!path)
		return (free(file_name), -1);
	path = strjoin_handler(path, file_name);
	if (!path)
		return (free(file_name), -1);
	if (unlink(file_name) == -1)
		return (free(file_name), free(path), -1);
	return (free(file_name), free(path), command->input_file == -1);
}