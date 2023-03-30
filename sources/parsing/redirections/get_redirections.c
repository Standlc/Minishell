#include "minishell.h"

int	get_redirect_type(char **line)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (DOUBLE_LEFT);
	else if (!ft_strncmp(*line, ">>", 2))
		return (DOUBLE_RIGHT);
	else if (**line == '<' && *(*line + 1) != '<')
		return (SIMPLE_LEFT);
	return (SIMPLE_RIGHT);
}

void	*get_red_function(int redirect_type)
{
	if (redirect_type == SIMPLE_RIGHT)
		return (handle_simple_right_redirection);
	else if (redirect_type == DOUBLE_RIGHT)
		return (handle_double_right_redirection);
	return (handle_simple_left_redirection);
}

int	handle_redirections(char **line, t_command *command, int f(t_command *, char *))
{
	char	*line_cpy;
	char	**file_names;

	line_cpy = *line;
	file_names = get_line_args(line);
	if (!file_names)
		return (1);
	if (file_names)
		file_names = handle_widlcards(file_names);
	if (str_arr_size(file_names) != 1)
		return (print_error("ambiguous redirect: ", line_cpy), 1);
	if (file_or_dir_check(file_names[0]))
		return (1);
	if (f(command, file_names[0]) == -1)
		return (free_str_arr(file_names), 1);
	return (free_str_arr(file_names), 0);
}

int	get_redirections(char **line, t_command *command, int **heredoc_fds)
{
	int		redirect_type;

	while (is_redirection(*line))
	{
		redirect_type = get_redirect_type(line);
		*line += 1;
		*line += redirect_type == DOUBLE_LEFT || redirect_type == DOUBLE_RIGHT;
		skip_spaces(line);
		if (redirect_type == DOUBLE_RIGHT || redirect_type == SIMPLE_LEFT || redirect_type == SIMPLE_RIGHT)
		{
			if (handle_redirections(line, command, get_red_function(redirect_type)))
				return (1);
		}
		else if (assign_heredoc_fd(line, command, heredoc_fds))
			return (1);
		skip_spaces(line);
	}
	return (0);
}
