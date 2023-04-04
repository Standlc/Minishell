/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_or_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:29:02 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 16:36:37 by stde-la-         ###   ########.fr       */
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

int	file_or_dir_check(char *str, int access_type)
{
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
	g_status = 127;
	return (print_error("no such file or directory: ", str), 1);
}
