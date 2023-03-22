#include "minishell.h"

void	print_line_component(char *line)
{
	if (*line == '\0')
	{
		write(2, "newline", 7);
		return ;
	}
	write(2, "`", 1);
	if (is_operator(line) || is_redirection(line) == 2)
		write(2, line, 2);
	else if (is_pipe(line) || *line == '&' || is_redirection(line) == 1 || is_parenthesis(line))
		write (2, line, 1);
	else
	{
		while (*line && *line != ' ' && !is_special_symbol(line))
			write(2, line++, 1);
	}
	write(2, "`", 1);
}

void	print_error(char *message, char *line)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	if (line)
		print_line_component(line);
	ft_putstr_fd("\n", 2);
}
