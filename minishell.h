/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:52:36 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/27 12:53:01 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

enum operators {
    NONE = 0,
    AND = 1,
    OR = 2,
};

typedef struct s_command
{
	char	*command;
	char	**options;
}				t_command;

typedef struct s_pipe_commands
{
	t_command	*commands;
	int		operator;
}				t_pipe_commands;

typedef struct s_data
{
	t_pipe_commands	*s_pipe_commands;
	//OTHER
}				t_data;

#endif