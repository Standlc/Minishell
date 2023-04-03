#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT	"➜  minishell $> "
# define MEM "minishell: Cannot allocate memory\n"
# define LMIN "-9223372036854775808"
# define LMAX "9223372036854775807"

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
# include <dirent.h>
# include <string.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
#include "struct_minishell.h"
# include "parsing.h"
# include "execution.h"

char		***environnement(char **new_env);
int			get_line(t_pipeline *pipelines, char **env);
int			main(int argc, char **argv, char **env);

#endif