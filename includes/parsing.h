#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

int	*handle_heredocs(char *line, int *heredoc_fds);
int	*do_the_heredoc(int *heredoc_fds, char **limits);
int	get_heredoc_amount(char *line);
char	*get_heredoc_limit(char **line, char *heredoc_limit);

t_pipeline	*parse_line(char *line, int *heredoc_fds);

char		**get_line_args(char **line);
char	**handle_env_var(char **line, int is_inside_quotes);
char	*dup_line_word(char **line);
char	*dup_line_word_quotes(char **line, char quote_type);

int	get_pipeline_commands_amount(char *line);
int	get_pipelines_amount(char *line);

int			add_char(char **line, char **str);

int			str_arr_size(char **arr);
char	**join_arr_strjoin(char **arr1, char **arr2);
char	**join_str_arr(char **dest, char **arr2);
char	**insert_str_arr_at_index(char **arr1, char **arr2, int index);
int	get_index_str_arr(char **str_arr, char *str);

int			check_syntax(char *line, int is_inside_parenthesis);
int			check_redirection_error(char **line);
int			check_operator_error(char **line);
int			is_last_special_symbol(char *line);
int	check_for_missing_quote(char *line);
int	check_quotes(char **line);
void		skip_special_symbol(char **line);
int			check_parenthesis_error(char **line, char *ptr, int is_inside_parenthesis);

int			is_parenthesis(char *line);
int			is_redirection(char *line);
int			is_pipe(char *line);
int			is_quote(char c);
int			is_env_var(char *line, char quote_type);;
int			is_operator(char *line);
int			is_meta_char(char *line);
int			is_wildcard(char *str);
int			is_heredoc(char *line);
int	is_directory(char *file);

int			get_redirections(char **line, t_command *command, int **heredoc_fds);
int			handle_simple_right_redirection(t_command *command, char *file);
int			handle_simple_left_redirection(t_command *command, char *file);
int			handle_double_right_redirection(t_command *command, char *file);

int			assign_heredoc_fd(char **line, t_command *command, int **heredoc_fds);
char	*dup_line_word(char **line);

void		skip_spaces(char **line);
void		get_operator(char **line, t_pipeline *pipeline);
int	file_or_dir_check(char *str);
void	*ft_realloc(void *src, int prev_size, int new_size, int data_type);

void		print_error(char *message, char *line);
char		*strjoin_handler(char *str, char *join);

// WILDCARDS
char		**handle_widlcards(char **args);
int	compare(char *wildcard, char *file);
char	*get_curr_dir_wildcard(char *wildcard, int *is_directory_match);
char		**get_wildcard_matches(char *wildcard);
void	sort(char **arr, int size);
int	is_match(char *curr_dir_wildcard, int is_directory_match, char *file);
int	wildcard_matches_amount(char *curr_dir_wildcard, int is_directory_match);

void		free_pipelines(t_pipeline *pipelines);
void		free_str_arr(char **str_arr);

int			hook_signals(void);

#endif