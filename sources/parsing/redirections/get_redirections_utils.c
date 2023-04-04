/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:52 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 20:27:26 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_status;

int	handle_simple_left_redirection(t_command *command, char *file)
{
	if (file_or_dir_check(file, READ, 0))
		return (-1);
	if (command->input_file > 2)
		close(command->input_file);
	command->input_file = open(file, O_RDONLY);
	if (command->input_file == -1)
	{
		g_status = 1;
		print_error("no such file or directory: ", file);
	}
	return (command->input_file);
}

int	handle_simple_right_redirection(t_command *command, char *file)
{
	if (file_or_dir_check(file, WRITE, 0))
		return (-1);
	if (command->output_file != 1)
		close(command->output_file);
	command->output_file = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->output_file == -1)
	{
		g_status = errno;
		print_error("could not open file: ", file);
	}
	return (command->output_file);
}

int	handle_double_right_redirection(t_command *command, char *file)
{
	if (file_or_dir_check(file, WRITE, 0))
		return (-1);
	if (command->output_file != 1)
		close(command->output_file);
	command->output_file = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (command->output_file == -1)
	{
		g_status = errno;
		print_error("could not open file: ", file);
	}
	return (command->output_file);
}
