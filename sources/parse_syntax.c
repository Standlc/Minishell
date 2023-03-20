#include "minishell.h"

void	print_special_symbol(char *line)
{
	if (is_operator(line) || is_redirection(line) == 2)
		write(2, line, 2);
	else if (is_pipe(line) || *line == '&' || is_redirection(line) == 1 || is_parenthesis(line))
		write (2, line, 1);
	else
		write(2, "newline", 7);
}

int	is_special_symbol(char *line)
{
	return (is_pipe(line) || is_operator(line) || is_quote(*line) || is_redirection(line) || is_parenthesis(line));
}

void	skip_special_symbol(char **line)
{
	if (is_operator(*line) || is_redirection(*line) == 2)
		*line += 2;
	else if (is_pipe(*line) || **line == '&' || is_redirection(*line) == 1 || is_parenthesis(*line))
		*line += 1;
}

int	check_missing_quotes(char **line)
{
	char	quote_type;

	skip_spaces(line);
	if (!is_quote(**line))
		return (0);
	quote_type = **line;
	*line += 1;
	while (**line && **line != quote_type)
		*line += 1;
	if (!**line)
		return (1);
	skip_spaces(line);
	*line += 1;
	return (0);
}

int	is_last_special_symbol(char *line)
{
	if (is_operator(line) || is_pipe(line) || is_redirection(line))
	{
		skip_special_symbol(&line);
		skip_spaces(&line);
		if (*line == '\0')
			return (1);
	}
	return (0);
}

int	check_operator_error(char **line)
{
	if ((**line == '&' && !is_operator(*line)) || is_last_special_symbol(*line))
		return (1);
	if (!is_pipe(*line) && !is_operator(*line) && **line != '&')
		return (0);
	skip_special_symbol(line);
	skip_spaces(line);
	return (is_pipe(*line) || is_operator(*line) || **line == '&');
}

int	check_redirection_error(char **line)
{
	if (!is_redirection(*line))
		return (0);
	skip_special_symbol(line);
	skip_spaces(line);
	return (is_pipe(*line) || is_operator(*line) || **line == '&' || is_redirection(*line) || !**line);
}

int	check_operator_before_parenthesis(char *line)
{
	line--;
	while (*line && *line == ' ')
		line--;
	line -= *line != '\0';
	return (!is_operator(line));
}

int	check_missing_parenthesis(char *line)
{
	while (*line && *line != ')')
	{
		if (*line == '(' && check_missing_parenthesis(line))
				return (1);
		line += 1;
	}
	return (!*line);
}

int	check_empty_parenthesis(char **line)
{
	skip_spaces(line);
	return (**line == ')');
}

int	check_parenthesis_error(char *line)
{
	if (*line == '(')
	{
		line += 1;
		// if (check_missing_parenthesis(line))
		// 	return (print_error("syntax error: missing parenthesis", NULL, line), 1);
		if (check_empty_parenthesis(&line))
			return (print_error("unexpected token error: ", print_special_symbol, line), 1);
		// if (check_operator_before_psarenthesis(*line))
		// 	return (print_error("unexpected token error: ", print_special_symbol, *line), 1);
	}
	return (0);
}

int	check_syntax(char *line)
{
	*(line - 1) = '\0';
	skip_spaces(&line);
	if ((is_operator(line) || is_pipe(line)))
		return (print_error("unexpected token error: ", print_special_symbol, line), 1);
	while (*line)
	{
		if (check_missing_quotes(&line))
			return (print_error("syntax error: missing quote", NULL, line), 1);
		if (check_operator_error(&line))
			return (print_error("unexpected token error: ", print_special_symbol, line), 1);
		if (check_redirection_error(&line))
			return (print_error("unexpected token error: ", print_special_symbol, line), 1);
		if (check_parenthesis_error(line))
			return (1);
		// line += *line && !is_special_symbol(line);
		line += 1;
	}
	return (0);
}

// ... && ( (...) || (...) ) || ...
// ( (...) || (...) )

// &&||
// &&|
// &&&
// cat &&
// cat |
// cat |&
// cat &|
// && cat
// & cat
// | cat
// cat < |
// cat < &&
// cat < <
// cat <
// "cat
// (cat
// cat)