/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 13:09:11 by stde-la-          #+#    #+#             */
/*   Updated: 2023/04/02 13:10:16 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arguments(char **line, t_command *command, int **heredoc_fds)
{
	while (**line && !is_pipe(*line) && !is_operator(*line) && !is_parenthesis(*line))
	{
		if (!is_redirection(*line))
		{
			command->arguments = join_str_arr(command->arguments, get_line_args(line));
			if (!command->arguments)
				return (1);
		}
		else if (get_redirections(line, command, heredoc_fds))
				return (1);
		skip_spaces(line);
	}
	return (0);
}

int	get_command(char **line, t_command *command, int **heredoc_fds)
{
	command->output_file = 1;
	command->is_end = 1;
	if (get_arguments(line, command, heredoc_fds))
		return (1);
	if (command->arguments)
	{
		command->arguments = handle_widlcards(command->arguments);
		if (!command->arguments || file_or_dir_check(command->arguments[0]))
			return (1);
	}
	*line += is_pipe(*line);
	skip_spaces(line);
	return (0);
}

void	handle_parenthesis(char **line, t_pipeline *pipeline, char parenthesis_type, int increment)
{
	if (**line != parenthesis_type)
		return ;
	skip_spaces(line);
	while (**line == parenthesis_type)
	{
		*line += 1;
		pipeline->parenthesis += increment;
		skip_spaces(line);
	}
}

int	get_pipeline(char **line, t_pipeline *pipeline, int **heredoc_fds)
{
	int	i;
	int	command_amount;

	get_operator(line, pipeline);
	handle_parenthesis(line, pipeline, '(', 1);
	command_amount = get_pipeline_commands_amount(*line);
	pipeline->commands = ft_calloc(command_amount + 1, sizeof(t_command));
	if (!pipeline->commands)
		return (1);
	i = 0;
	while (**line && !is_operator(*line))
	{
		if (get_command(line, pipeline->commands + i, heredoc_fds))
			return (1);
		handle_parenthesis(line, pipeline, ')', -1);
		i++;
	}
	return (0);
}

t_pipeline	*parse_line(char *line, int *heredoc_fds)
{
	char		*line_ptr;
	t_pipeline	*pipelines;
	int			i;

	line_ptr = line;
	if (check_syntax(line))
		return (ft_calloc(1, sizeof(t_pipeline)));
	pipelines = ft_calloc(get_pipelines_amount(line) + 1, sizeof(t_pipeline));
	if (!pipelines)
		return (free(line_ptr), NULL);
	i = 0;
	while (*line)
	{
		if (get_pipeline(&line, pipelines + i, &heredoc_fds))
			return (free(line_ptr), free_pipelines(pipelines), NULL);
		i++;
	}
	return (free(line_ptr), pipelines);
}

// :
// #
// $'' $: $=
//"$'"

// cat a || (cat a && (cat b || cat a) || cat b)
// cat a || (cat a || ((cat b && cat a) || cat b))

// > "file" > "file" "command" arg < file arg | command " arg < file arg" && "command" arg arg > file | command " arg arg"
// rev | < a cat > b < 6.c > c | rev &&  < a echo yo > b > a | cat || ls
// echo "sdf$USER" -> sdfstde-la-
// echo "sdf$USERsdf" -> sdf
// echo "sdf$USER sdf" -> sdfstde-la-
// echo "sdf $USER" -> sdf stde-la- 
// com arg"$USER" -> argstan
// a"$USER"a"$USER" -> astanastan
// $USER"$USER"$USER -> stanstanstan
