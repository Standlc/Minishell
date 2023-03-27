#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_pipe(char *line)
{
	return (*line == '|' && *(line + 1) != '|');
}

int	is_redirection(char *line)
{
	if (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2))
		return (2);
	if (*line == '<' || *line == '>')
		return (1);
	return (0);
}

int	is_parenthesis(char *line)
{
	return (*line == '(' || *line == ')');
}

int	is_env_var(char *line, char quote_type)
{
	if (!ft_isalnum(*(line + 1)))
		return (0);
	return (*line == '$' && *(line + 1)
		&& (!quote_type || (quote_type == '"' && *(line + 1) != '"')));
}