/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:11 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/04 16:22:41 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arguments_conditions(char *line)
{
	return (!is_pipe(line) && !is_operator(line) && !is_parenthesis(line));
}

int	get_arguments(char **line, t_command *command, t_heredoc_fds **heredoc_fds)
{
	char	**args;

	while (**line && arguments_conditions(*line))
	{
		if (!is_redirection(*line))
		{
			args = get_line_args(line);
			command->arguments = join_str_arr(command->arguments, args);
			if (!command->arguments)
				return (1);
		}
		else if (get_redirections(line, command, heredoc_fds))
			return (1);
		skip_spaces(line);
	}
	return (0);
}

int	get_command(char **line, t_command *command, t_heredoc_fds **heredoc_fds)
{
	command->output_file = 1;
	command->is_end = 1;
	if (get_arguments(line, command, heredoc_fds))
		return (1);
	if (str_arr_size(command->arguments) == 0)
	{
		free_str_arr(command->arguments);
		command->arguments = NULL;
	}
	if (command->arguments)
	{
		command->arguments = handle_widlcards(command->arguments);
		if (!command->arguments)
			return (1);
		if (file_or_dir_check(command->arguments[0], EXEC))
			return (1);
	}
	*line += is_pipe(*line);
	return (0);
}

void	handle_parenthesis(char **line, t_pipeline *pipeline, char parenthesis)
{
	skip_spaces(line);
	if (**line != parenthesis)
		return ;
	skip_spaces(line);
	while (**line == parenthesis)
	{
		*line += 1;
		pipeline->parenthesis += parenthesis == '(' * 2 - 1;
		skip_spaces(line);
	}
}

int	get_pipeline(char **line, t_pipeline *pipeline, t_heredoc_fds **heredoc_fds)
{
	int	i;
	int	size;

	pipeline->parenthesis = 0;
	handle_parenthesis(line, pipeline, '(');
	size = get_pipeline_commands_amount(*line);
	pipeline->commands = ft_calloc(size + 1, sizeof(t_command));
	if (!pipeline->commands)
		return (1);
	i = 0;
	while (**line && !is_operator(*line))
	{
		if (get_command(line, pipeline->commands + i, heredoc_fds))
			return (1);
		handle_parenthesis(line, pipeline, ')');
		i++;
	}
	get_operator(line, pipeline);
	return (0);
}

// :
// #
// $'' $: $=
//"$'"

// cat a || (cat a && (cat b || cat a) || cat b)
// cat a || (cat a || ((cat b && cat a) || cat b))

// rev | < a cat > b < 6.c > c | rev &&  < a echo yo > b > a | cat || ls
// echo "sdf$USER" -> sdfstde-la-
// echo "sdf$USERsdf" -> sdf
// echo "sdf$USER sdf" -> sdfstde-la-
// echo "sdf $USER" -> sdf stde-la- 
// com arg"$USER" -> argstan
// a"$USER"a"$USER" -> astanastan
// $USER"$USER"$USER -> stanstanstan
