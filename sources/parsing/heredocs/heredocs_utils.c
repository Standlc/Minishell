#include "minishell.h"

int	handle_write(int fd, char *heredoc_line)
{
	char	**env_var_values;

	while (*heredoc_line)
	{
		if (is_env_var(heredoc_line, 0))
		{
			env_var_values = handle_env_var(&heredoc_line, 1);
			if (!env_var_values)
				return (1);
			write(fd, env_var_values[0], ft_strlen(env_var_values[0]));
			free_str_arr(env_var_values);
		}
		else
		{
			write(fd, heredoc_line, 1);
			heredoc_line++;
		}
	}
	write(fd, "\n", 1);
	return (0);
}

int	read_heredoc(int fd, char *limit)
{
	int		limit_len;
	char	*heredoc_line;

	limit_len = ft_strlen(limit);
	heredoc_line = readline("> ");
	while (heredoc_line)
	{
		if (!ft_strncmp(limit, heredoc_line, limit_len + 1))
			return (0);
		else
			handle_write(fd, heredoc_line);
		free(heredoc_line);
		heredoc_line = readline("> ");
	}
	return (0);
}

int	*do_the_heredoc(int *heredoc_fds, char **limits)
{
	int		pipe_fds[2];
	int		i;

	heredoc_fds = ft_calloc(str_arr_size(limits), sizeof(int));
	if (!heredoc_fds)
		return (NULL);
	i = 0;
	while (limits[i])
	{
		if (pipe(pipe_fds) == -1)
			return (NULL);
		heredoc_fds[i] = pipe_fds[0];
		read_heredoc(pipe_fds[1], limits[i]);
		close(pipe_fds[1]);
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
