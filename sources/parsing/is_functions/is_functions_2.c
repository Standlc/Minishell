#include "minishell.h"

int	is_operator(char *line)
{
	return (!ft_strncmp(line, "&&", 2) || !ft_strncmp(line, "||", 2));
}

int	is_meta_char(char *line)
{
	return (is_pipe(line) || is_operator(line) || is_quote(*line) || is_redirection(line) || is_parenthesis(line) || *line == '&');
}
