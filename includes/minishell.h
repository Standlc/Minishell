/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:52:36 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/27 15:05:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

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