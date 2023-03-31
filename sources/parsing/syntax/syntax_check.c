#include "minishell.h"

extern int	g_status;

int	check_line(char *line, int is_inside_parenthesis, char *line_ptr_cpy)
{
	skip_spaces(&line);
	if ((is_operator(line) || is_pipe(line)))
		return (print_error("0 unexpected token error: ", line), 1);
	while (*line && (*line != ')' || !is_inside_parenthesis))
	{
		if (check_quotes(&line))
			return (print_error("1 syntax error: missing quote", NULL), 1);
		if (check_redirection_error(&line))
			return (print_error("3 unexpected token error: ", line), 1);
		if (check_operator_error(&line))
			return (print_error("2 unexpected token error: ", line), 1);
		if (check_parenthesis_error(&line, line_ptr_cpy, is_inside_parenthesis))
			return (1);
		line += *line && !is_meta_char(line);
	}
	return (0);
}

int	check_syntax(char *line)
{
	char	*line_ptr_cpy;

	line_ptr_cpy = line;
	if (check_line(line, 0, line_ptr_cpy))
	{
		g_status = 2;
		return (1);
	}
	return (0);
}

//UNSURE
// (()) -> ?
// ((cat)) -> ?
// ((cat file)) -> ?