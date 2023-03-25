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
# include <dirent.h>

enum e_realloc_data_types {
	PIPELINES,
	COMMANDS,
	ARGUMENTS
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
	char	**arguments;
	int		input_file;
	int		output_file;
	char	*heredoc_limit;
	int		is_end;
}				t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			operator;
	int			parenthesis;
}				t_pipeline;

//PARSING
t_pipeline	*parse_line(char *line);
char		*copy_line_word(char **line);
int			add_char(char **line, char **str);

int			check_syntax(char *line, int is_inside_parenthesis);
int			check_redirection_error(char **line);
int			check_operator_error(char **line);
int			is_last_special_symbol(char *line);
int			check_missing_quotes(char **line);
void		skip_special_symbol(char **line);
int			check_parenthesis_error(char **line, char *ptr, int is_inside_parenthesis);

int			is_parenthesis(char *line);
int			is_redirection(char *line);
int			is_pipe(char *line);
int			is_quote(char c);
int			is_env_var(char *line, char quote_type);;
int			is_operator(char *line);
int			is_meta_char(char *line);

int			get_redirections(char **line, t_command *command);
int			handle_simple_right_redirection(t_command *command, char *file);
int			handle_simple_left_redirection(t_command *command, char *file);
int			handle_double_right_redirection(t_command *command, char *file);

void		skip_spaces(char **line);
void		get_operator(char **line, t_pipeline *pipeline);
int			is_directory(char *str);
void		*ft_realloc(void *src, int nmemb, int size, int data_type);

void		print_error(char *message, char *line);
char		*strjoin_handler(char *str, char *join);

char		**read_dir(char *line, char **arguments, int size);

void		free_pipelines(t_pipeline *pipelines);

int			hook_signals(void);

#endif