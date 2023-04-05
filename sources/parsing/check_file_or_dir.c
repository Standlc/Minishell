/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_or_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:29:02 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 22:39:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	check_file_accessibility(char *file, int access_type)
{
	if (access_type == EXEC && access(file, X_OK))
	{
		g_status = 126;
		print_error("permission denied: ", file);
		return (1);
	}
	else if (access_type == WRITE && access(file, W_OK))
	{
		g_status = 1;
		print_error("permission denied: ", file);
		return (1);
	}
	else if (access_type == READ && access(file, R_OK))
	{		
		g_status = 1;
		print_error("permission denied: ", file);
		return (1);
	}
	return (0);
}

int	file_or_dir_check(char *str, int access_type, int is_command_name)
{
	// int dir_type;

	// dir_type = str[0] == '/';
	if (!str || (access_type == EXEC && (str[0] != '/' && str[0] != '.')))
		return (0);
	if (!access(str, F_OK))
	{
		if (is_directory(str))
		{			
			g_status = 126;
			print_error("is a directory: ", str);
			return (1);
		}
		if (check_file_accessibility(str, access_type))
			return (1);
		return (0);
	}
	if (is_command_name)
		g_status = 127;
	else
		g_status = 1;
	return (print_error("no such file or directory: ", str), 1);
}
