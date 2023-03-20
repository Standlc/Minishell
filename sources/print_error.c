#include "minishell.h"

void	print_error(char *message, void (*f)(char *), char *line)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	if (f)
		f(line);
	ft_putstr_fd("\n", 2);
}
