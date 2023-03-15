#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT	"➜  minishell $>"

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

enum e_operators {
	NONE = 0,
	AND = 1,
	OR = 2,
};

enum e_redirections {
	SIMPLE_LEFT = 1,
	SIMPLE_RIGHT = 2,
	DOUBLE_LEFT = 3,
	DOUBLE_RIGHT = 4,
	PIPE = 5,
};

typedef struct s_command
{
	char	*name;
	char	**arguments;
	char	*input_file;
	char	*output_file;
}				t_command;

typedef struct s_pipeline
{
	t_command			*commands;
	enum e_operators	operator;
	int					last_pipeline_status;
}				t_pipeline;

t_pipeline	*parse_line(char *line);
int		is_operator(char *line);
int		word_len(char *str);
void	skip_spaces(char **line);
int		get_options_amount(char *line);
int		get_arguments_amount(char *line);
int		get_commands_amount(char *line);

void	free_pipelines(t_pipeline *pipelines);

int		hook_signals(void);

#endif