#include "minishell.h"

int	check_operator_before_parenthesis(char *line, char *ptr)
{
	printf("%c\n", *line);

	line -= line != ptr;
	printf("%c\n", *line);

	while (line != ptr && *line == ' ')
		line--;
	printf("%c\n", *line);
	if (*line == '(')
		return (0);
	line -= line != ptr;
	return (!is_operator(line) && *line);
}

int	check_operator_after_parenthesis(char **line)
{
	*line += 1;
	skip_spaces(line);
	return (!is_operator(*line) && **line != ')' && **line);
}

int	check_missing_parenthesis(char **line)
{
	while (**line && **line != ')')
	{
		if (**line == '(')
		{
			*line += 1;
			if (check_missing_parenthesis(line))
				return (1);
		}
		*line += 1;
	}
	return (!**line);
}

int	check_empty_parenthesis(char **line)
{
	skip_spaces(line);
	return (**line == ')');
}

int	check_parenthesis_error(char **line, char *ptr, int is_inside_parenthesis)
{
	if (!is_inside_parenthesis && **line == ')')
		return (print_error("10 unexpected token error: ", *line), 1);
	if (**line == '(')
	{
		if (check_operator_before_parenthesis(*line, ptr))
			return (print_error("11 unexpected token error: ", *line), 1);
		*line += 1;
		if (check_empty_parenthesis(line))
			return (print_error("12 unexpected token error: ", *line), 1);
		if (check_syntax(*line, 1))
			return (1);
		if (check_missing_parenthesis(line))
			return (print_error("13 syntax error: missing parenthesis", NULL), 1);
		if (check_operator_after_parenthesis(line))
			return (print_error("14 unexpected token error: ", *line), 1);
	}
	return (0);
}
