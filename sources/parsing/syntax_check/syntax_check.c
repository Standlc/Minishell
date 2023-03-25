#include "minishell.h"

// int	check_embeded_parenthesis(char *line)
// {
// 	while (*line && !is_parenthesis(line) && !is_operator(line))
// 		line += 1;
// 	if (*line == '(')
// 	{
// 		line += 1;
// 		while (*line && !is_parenthesis(line) && !is_operator(line))
// 			line += 1;
// 		if (*line == ')')
// 		{
// 			line += 1;
// 			while (*line && !is_parenthesis(line) && !is_operator(line))
// 				line += 1;
// 			return (*line == ')');
// 		}
// 	}
// 	return (0);
// }

int	check_wildcards(char **line)
{
	if (**line != '*')
		return (0);
	while (**line && **line == '*')
		*line += 1;
	return (0);
}

//AMBIGOUS REDIRECT

int	check_syntax(char *line, int is_inside_parenthesis)
{
	static char	*line_ptr_cpy = NULL;

	if (!line_ptr_cpy)
		line_ptr_cpy = line;
	skip_spaces(&line);
	if ((is_operator(line) || is_pipe(line)))
		return (print_error("0 unexpected token error: ", line), 1);
	while (*line && (*line != ')' || !is_inside_parenthesis))
	{
		if (check_missing_quotes(&line))
			return (print_error("1 syntax error: missing quote", NULL), 1);
		if (check_redirection_error(&line))
			return (print_error("3 unexpected token error: ", line), 1);
		if (check_operator_error(&line))
			return (print_error("2 unexpected token error: ", line), 1);
		if (check_wildcards(&line))
			return (print_error("2 unexpected token error: ", line), 1);
		if (check_parenthesis_error(&line, line_ptr_cpy, is_inside_parenthesis))
			return (1);
		line += *line && !is_meta_char(line);
	}
	return (0);
}

//UNSURE
// (()) -> ?
// ((cat)) -> ?
// ((cat file)) -> ?