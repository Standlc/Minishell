#include "minishell.h"

int	assign_heredoc_fd(char **line, t_command *command, int **heredoc_fds)
{
	char		*heredoc_limit;
	static int	i = 0;

	if (command->input_file > 2)
		close(command->input_file);
	command->input_file = **heredoc_fds;
	*heredoc_fds += 1;
	heredoc_limit = NULL;
	heredoc_limit = get_heredoc_limit(line, heredoc_limit);
	if (!heredoc_limit)
		return (1);
	free(heredoc_limit);
	i++;
	return (0);
}

// int	handle_heredoc(char **line, t_command *command)
// {
// 	int		size;
// 	char	*file_name;
// 	char	*path;

// 	if (command->input_file > 2)
// 		close(command->input_file);
// 	size = str_arr_size(command->heredoc_limits);
// 	command->heredoc_limits = ft_realloc(command->heredoc_limits, size, size + 2, STR_ARR);
// 	if (!command->heredoc_limits)
// 		return (1);
// 	command->heredoc_limits[size] = dup_line_word(line);
// 	if (!command->heredoc_limits[size])
// 		return (1);
// 	file_name = open_heredoc_file(command);
// 	if (!file_name)
// 		return (-1);
// 	path = getcwd(NULL, 0);
// 	if (!path)
// 		return (free(file_name), -1);
// 	path = strjoin_handler(path, "/");
// 	if (!path)
// 		return (free(file_name), -1);
// 	path = strjoin_handler(path, file_name);
// 	if (!path)
// 		return (free(file_name), -1);
// 	if (unlink(file_name) == -1)
// 		return (free(file_name), free(path), -1);
// 	return (free(file_name), free(path), command->input_file == -1);
// }
