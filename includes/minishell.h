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
# include <dirent.h>
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
	int		input_file;
	int		output_file;
	int		position;
}				t_command;

typedef struct s_pipe
{
	int	link[2];
	int	fd[2];
}				t_pipe;

typedef struct s_pipeline
{
	t_command			*commands;
	enum e_operators	operator;
	int					start_priority;
	int					end_priority;
}				t_pipeline;



// int		parse_line(t_pipeline *pipelines, char *line);
// int		is_operator(char *line);
// int		word_len(char *str);
// void	skip_spaces(char **line);
// int		get_options_amount(char *line);
// int		get_arguments_amount(char *line);
// int		get_commands_amount(char *line);

// void	free_pipelines(t_pipeline *pipelines);

// int		hook_signals(void);

int		exit_max(char *value, char *max);
int		exit_min(char *value, char *min);
int		strcmp_for_exit(char *value, char *min, char *max);
long	ft_atoi_exit(char *str);
void	exit_ms(t_command *command);

int		directory_exist(char *dir);
void	env_ms(t_command *command);

void	delete_variable(char **env, int j);
int		valid_delete(char *argument);
void	delete_env(t_command *command, int i);
void	unset_ms(t_command *command);

void	replace_variable(char **new, char *argument, int lign);
int		is_variable(char **new, char *argument);
void	complete_env(char **new, char **arguments, int i);
int		validate_variable(char *argument);
int		variable_count(char **arguments);
char	**new_env(char **env, char **arguments);
void	export_ms(t_command *command);

void	pwd_ms(t_command *command);

void	cd_ms(t_command *command);

int		validate_option(t_command *command, int *i);
void	validate_n(t_command *command, int *i);
void	close_files(int fd_out);
void	echo_ms(t_command *command);

void	free_split(char **split);
void	*free_path(char **paths, char *fill_path, char *final_path);
char	*good_path(char **paths, char *fill_path, char *final_path, char *cmd);
char	*find_path(char	*env, char *cmd);
char	*path_for_execve(char **env, char *cmd);

char	**duplicate_for_execve(t_command *command);
void	duplicate_for_streams(t_command *command, t_pipe *pipes);
void	another_command(t_command *command, t_pipe *pipes);

void    set_position(t_command *commands);
void	set_pipe(t_command *command, t_pipe *pipes);

int		parenthesis_number(t_pipeline *pipelines);
void	parenthesis(t_pipeline *pipelines, int *index);

void	execution_command(t_command *command, t_pipe *pipes);
void	execution_pipeline(t_command *commands);
int		check_last_status(t_pipeline last);
void	execution_global(t_pipeline *pipelines);

int		bigarray_len(char **bigarray);
void	free_dup(char **dup_bigarray);
char	**duplicate_bigarray(char **bigarray);

char	***environnement(char **new_env);
t_pipeline	*test(t_pipeline *pipelines);
int		get_line(t_pipeline *pipelines, char **env);
int		main(int argc, char **argv, char **env);

#endif