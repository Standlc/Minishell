#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT	"➜  minishell "

# include <signal.h>
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
	SIMPLE_LEFT = 3,
	SIMPLE_RIGHT = 4,
	DOUBLE_LEFT = 5,
	DOUBLE_RIGHT = 6,
	PIPE = 7,
};

typedef struct s_command
{
	char	*name;
	char	**options;
	char	**arguments;
	int		operator;
}				t_command;

typedef struct s_data
{
	t_command	*commands;
}				t_data;

int		parse_line(t_data *data, char *line);
int		is_operator(char *line);
int		word_len(char *str);
void	skip_spaces(char **line);
int		get_options_amount(char *line);
int		get_arguments_amount(char *line);
int		get_commands_amount(char *line);

void	free_data(t_data *data);

#endif