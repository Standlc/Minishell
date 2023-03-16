#include "minishell.h"

void	skip_spaces(char **line)
{
	while (**line == ' ')
		(*line)++;
}

int	word_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

int	is_operator(char *line)
{
	return (!ft_strncmp(line, "&&", 2) || !ft_strncmp(line, "||", 2));
}

int	get_arguments_amount(char *line)
{
	int	count;

	count = 0;
	while (*line && !is_operator(line))
	{
		while (*line && *line != ' ')
			line++;
		skip_spaces(&line);
		count++;
	}
	return (count);
}

int	get_commands_amount(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		while (*line && !is_operator(line))
			line++;
		while (is_operator(line))
			line++;
		count++;
	}
	return (count);
}