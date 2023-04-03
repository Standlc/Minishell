/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:10:18 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/02 13:10:18 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_handler(char *str, char *join)
{
	char	*temp_ptr;

	if (!join)
		return (str);
	temp_ptr = str;
	str = ft_strjoin(str, join);
	free(temp_ptr);
	return (str);
}

void	print_line_component(char *line)
{
	if (*line == '\0')
	{
		write(2, "`newline`", 9);
		return ;
	}
	write(2, "`", 1);
	if (is_operator(line) || is_redirection(line) == 2)
		write(2, line, 2);
	else if (is_pipe(line) || *line == '&' || is_redirection(line) == 1 || is_parenthesis(line))
		write (2, line, 1);
	else
	{
		while (*line && *line != ' ' && (!is_meta_char(line) || *line == '*'))
			write(2, line++, 1);
	}
	write(2, "'", 1);
}

void	print_error(char *message, char *line)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(message, 2);
	if (line)
		print_line_component(line);
	ft_putstr_fd("\n", 2);
}
