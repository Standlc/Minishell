#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT	"➜  minishell $> "

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

enum e_data_types {
	PIPELINE = 0,
	COMMAND = 1,
	CHAR = 2,
};

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
	int		input_file;
	int		output_file;
}				t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			operator;
	int			status;
	int			start_priority;
	int			end_priority;
}				t_pipeline;

t_pipeline	*parse_line(char *line);
char		*copy_line_word(char **line);
int			is_redirection(char *line);
int			is_operator(char *line);
int			word_len(char *str);
void		skip_spaces(char **line);

int			is_quote(char c);
int			is_pipe(char *line);
int			is_redirection(char *line);
int			is_parenthesis(char *line);
int			is_env_var(char *line, char quote_type);

void		free_pipelines(t_pipeline *pipelines);

int			hook_signals(void);

int	check_syntax(char *line);

void		print_error(char *message, void (*f)(char *), char *line);

int			get_redirections(char **line, t_command *command);

#endif