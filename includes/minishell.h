#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT	"➜  minishell $> "
# define MEM "minishell: Cannot allocate memory\n"

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
# include <dirent.h>
# include <string.h>

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
	int		position;
	int		file_close;
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
int			arguments_count(char **arguments);

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


void	exit_pipeline(t_pipeline *pipelines, int i);
int		exit_max(char *value, char *max);
int		exit_min(char *value, char *min);
int		strcmp_for_exit(char *value, char *min, char *max);
long	ft_atoi_exit(char *str);
int		exit_ms(t_command *command);

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

char	*getenv_ms(char *variable);
void	complete_env_pwd(t_command *command, char *old_pwd, char *pwd);
void	env_pwd(char *old_pwd);
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

void	close_file_pipe(t_command *command);
void	duplicate_for_streams(t_command *command);
int		valide_argument_for_path(char *argument);
void	another_command(t_command *command);

int		execution_env(t_command *command);
void	execution_command(t_command *command);

void	set_position(t_command *commands);
void	set_pipe(t_command *command, int fd[2]);
void	set_files(t_command *command, int link[2], int fd);
int		multi_pipes(t_command *commands, int *fd);

void	pipeline_start(t_command *commands, int fd[2]);
int		fork_command(t_command *command);
int		until_last_command(t_command *commands, int fd[2]);
int		is_child(t_command command);
void	end_of_pipeline(t_command *commands, int fd[2], int end);

void	parenthesis(t_pipeline *pipelines, int *index);

// void	fill_here_doc(t_command command);
// void	check_here_doc(t_pipeline *pipelines);

void	execution_pipeline(t_command *commands);
int		check_last_status(t_pipeline last);
void	execution_global(t_pipeline *pipelines);

int		bigarray_len(char **bigarray);
void	free_dup(char **dup_bigarray);
char	**duplicate_bigarray(char **bigarray);

char	***environnement(char **new_env);
t_pipeline	*test(t_pipeline *pipelines);
t_pipeline	*get_line(t_pipeline *pipelines, char **env);
int		main(int argc, char **argv, char **env);

#endif