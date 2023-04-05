/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_or_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:29:02 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/05 21:33:10 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	check_file_access(t_command *command, char *file, int access_type)
{
	if (access_type == EXEC && access(file, X_OK))
	{
		command->status = 126;
		print_error("permission denied: ", file);
		return (1);
	}
	else if (access_type == WRITE && access(file, W_OK))
	{
		command->status = 1;
		print_error("permission denied: ", file);
		return (1);
	}
	else if (access_type == READ && access(file, R_OK))
	{		
		command->status = 1;
		print_error("permission denied: ", file);
		return (1);
	}
	return (0);
}

int	check_is_directory_str(char *str)
{
	skip_spaces(&str);
	while (*str == '.')
		str++;
	while (*str == '/')
		str++;
	while (*str)
	{
		if (*str == '/' && *(str + 1) == '\0')
			return (1);
		str++;
	}
	return (0);
}

void	handle_dir_error(t_command *command, char *str, int access_type)
{
	if (has_dot_slash_prefix(str))
		command->status = 127;
	else if (access_type == EXEC)
		command->status = 126;
	else
		command->status = 1;
	print_error("is a directory: ", str);
}

int	file_or_dir_check(t_command *command, char *str, int access_type)
{
	if (!str
		|| (access_type == EXEC
			&& !has_dot_slash_prefix(str) && !has_slash_prefix(str)))
		return (0);
	if (access_type == WRITE && check_is_directory_str(str))
	{
		command->status = 1;
		return (print_error("is a directory: ", str), 1);
	}
	if (!access(str, F_OK))
	{
		if (is_directory(str))
			return (handle_dir_error(command, str, access_type), 1);
		return (check_file_access(command, str, access_type));
	}
	if (access_type == WRITE)
		return (0);
	if (access_type == EXEC)
		command->status = 127;
	else
		command->status = 1;
	return (print_error("no such file or directory: ", str), 1);
}
