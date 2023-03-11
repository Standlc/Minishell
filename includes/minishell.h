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
	SIMPLE_LEFT = 3,
	SIMPLE_RIGHT = 4,
	DOUBLE_LEFT = 5,
	DOUBLE_RIGHT = 6,
	PIPE = 7,
};

typedef struct s_command
{

	char	*name;			//nom de la commande ex : ls

	char	**options;		//option de la commande ex : "-la" ou "-l -a"

	char	**arguments;	//argument ex : "test1.c test2.c" ou "test*" (les wilcards *)

	char	*input_file;	//fichier d'entree, stdin par defaut ex : "< a", "< a <c <p" -> input_file = "p", "<a < h [cmd] [flags] < u <k" -> input_file = "k", NULL si il n'y a pas de redirection "<" ou "<<", gerer aussi "<&"

	char	*output_file;	//fichier de sortie, stdout par defaut ex : "> a", "> a >c >p" -> input_file = "p", ">a < h [cmd] [flags] > u <k" -> output_file = "u" NULL si il n'y a pas de redirection ">" ou ">>" gerer aussi ">&"

	int		pipe_before;	//PIPE si la commande etait pecedee d'un "|", NONE sinon

	int		pipe_after;		//PIPE si la commande a un "|" a la fin, NONE sinon

}				t_command;

typedef struct s_data
{

	t_command	*commands;		//un groupe de commandes du type : "echo -n yes | <a cat <b >&2 >h | rev"

	int			operator_left;	//AND si avant le groupe de commande correspondant se trouvait "&&", de meme OR si "||", NONE si c'est le premier groupe de commandes

	int			last_status;	//status du groupe de commande precedant : 0 si succes, autre si echec (correspondant au status de sortie du groupe de commande)

}				t_data


int		parse_line(t_data *data, char *line);
int		is_operator(char *line);
int		word_len(char *str);
void	skip_spaces(char **line);
int		get_options_amount(char *line);
int		get_arguments_amount(char *line);
int		get_commands_amount(char *line);

void	free_data(t_data *data);

#endif