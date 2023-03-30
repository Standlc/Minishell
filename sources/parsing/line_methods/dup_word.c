#include "minishell.h"

int	word_len(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != ' ' && !is_pipe(line + len)
		&& !is_operator(line + len) && !is_redirection(line + len))
		len++;
	return (len);
}

char	*dup_line_word(char **line)
{
	char	*str;
	int		i;

	str = ft_calloc(word_len(*line) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (**line && **line != ' ' && !is_pipe(*line)
		&& !is_operator(*line) && !is_redirection(*line))
	{
		str[i] = **line;
		i++;
		*line += 1;
	}
	return (str);
}

int	word_len_quotes(char *line, char quote_type)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != quote_type)
		len++;
	return (len);
}

char	*dup_line_word_quotes(char **line, char quote_type)
{
	char	*str;
	int		i;

	*line += **line == quote_type;
	str = ft_calloc(word_len_quotes(*line, quote_type) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (**line && **line != quote_type)
	{
		str[i] = **line;
		i++;
		*line += 1;
	}
	return (str);
}
