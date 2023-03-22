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
