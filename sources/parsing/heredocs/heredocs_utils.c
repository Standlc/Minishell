#include "minishell.h"

int	read_heredoc(int fd, char *limit)
{
	int		limit_len;
	char	*heredoc_line;

	limit_len = ft_strlen(limit);
	heredoc_line = readline("> ");
	while (heredoc_line)
	{
		if (!ft_strncmp(limit, heredoc_line, limit_len))
			return (0);
		else
			write(fd, heredoc_line, ft_strlen(heredoc_line));
		free(heredoc_line);
		heredoc_line = readline("> ");
	}
	return (0);
}

// CLOSE FD?
int	*do_the_heredoc(int *heredoc_fds, char **limits)
{
	int		pipe_fds[2];
	int		i;

	heredoc_fds = malloc(str_arr_size(limits) * sizeof(int));
	if (!heredoc_fds)
		return (NULL);
	i = 0;
	while (limits[i])
	{
		if (pipe(pipe_fds) == -1)
			return (NULL);
		// close(pipe_fds[0]);
		heredoc_fds[i] = pipe_fds[1];
		read_heredoc(pipe_fds[1], limits[i]);
		i++;
	}
	return (heredoc_fds);
}

int	get_heredoc_amount(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (is_heredoc(line))
		{
			line += 2;
			while (*line && !is_heredoc(line))
				line++;
			count++;
		}
		else
			line++;
	}
	return (count);
}
