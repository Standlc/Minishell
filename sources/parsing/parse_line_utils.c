#include "minishell.h"

void	skip_spaces(char **line)
{
	while (**line == ' ')
		*line += 1;
}

void	get_operator(char **line, t_pipeline *pipeline)
{
	skip_spaces(line);
	if (!is_operator(*line))
		return ;
	if (!ft_strncmp(*line, "&&", 2))
		pipeline->operator = AND;
	else if (!ft_strncmp(*line, "||", 2))
		pipeline->operator = OR;
	*line += 2;
	skip_spaces(line);
}

int	file_or_dir_check(char *str)
{
	DIR				*directory;

	if (!str || !str[0] || (str[0] != '.' && str[0] != '/'))
		return (0);
	if (!access(str, F_OK))
	{
		if (access(str, X_OK))
		{
			print_error("permission denied: ", str);
			return (1);
		}
		directory = opendir(str);
		if (directory)
		{
			print_error("is a directory: ", str);
			return (closedir(directory), 1);
		}
		return (0);
	}
	return (print_error("no such file or directory: ", str), 1);
}

void	realloc_memcpy(void *dest, void *src, int data_type, int index)
{
	if (data_type == PIPELINES)
		((t_pipeline *)dest)[index] = ((t_pipeline *)src)[index];
	else if (data_type == COMMANDS)
		((t_command *)dest)[index] = ((t_command *)src)[index];
	else
		((char **)dest)[index] = ((char **)src)[index];
}

int	ft_sizeof(int data_type)
{
	if (data_type == PIPELINES)
		return (sizeof(t_pipeline));
	if (data_type == COMMANDS)
		return (sizeof(t_command));
	return (sizeof(char **));
}

void	*ft_realloc(void *src, int prev_size, int new_size, int data_type)
{
	void	*res;
	int		i;

	res = ft_calloc(new_size, ft_sizeof(data_type));
	if (!res || !src)
		return (res);
	i = 0;
	while (i < prev_size)
	{
		realloc_memcpy(res, src, data_type, i);
		i++;
	}
	free(src);
	return (res);
}
