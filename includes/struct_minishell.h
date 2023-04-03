#ifndef STRUCT_MINISHELL_H
# define STRUCT_MINISHELL_H

enum e_realloc_data_types {
	PIPELINES,
	COMMANDS,
	STR_ARR,
	INT_ARR
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
	int		position;
	int		close_pipe[2];
	int		is_end;
}				t_command;

typedef struct s_pipeline
{
	t_command	*commands;
	int			operator;
	int			parenthesis;
}				t_pipeline;

#endif