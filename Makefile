SRC			=	main.c							parsing/parse_line.c parsing/redirections/heredoc.c \
				parsing/parse_line_utils.c				close_program.c \
				signals.c						parsing/print_error.c parsing/array_methods/join_str_arr.c parsing/array_methods/insert.c \
				parsing/redirections/get_redirections.c			parsing/syntax/syntax_check.c parsing/line_methods/env_var.c \
				parsing/line_methods/get_line_args.c parsing/line_methods/dup_word.c parsing/is_functions/is_functions_1.c parsing/ft_realloc.c \
				parsing/is_functions/is_functions_2.c	parsing/redirections/get_redirections_utils.c \
				parsing/syntax/utils.c 	parsing/syntax/check_parenthesis.c \
				parsing/wildcards/wildcards.c parsing/wildcards/get_wildcard_matches.c parsing/wildcards/utils.c 					parsing/heredocs/heredocs.c parsing/heredocs/heredocs_utils.c \
				parsing/heredocs/heredoc_child.c execution/execution.c execution/for_dup.c execution/parenthesis.c execution/execute_command.c\
				execution/another.c execution/path.c execution/pipe.c execution/pipelines_steps.c\
				execution/builtins/cd.c execution/builtins/echo.c execution/builtins/env.c execution/builtins/exit/exit.c \
				execution/builtins/exit/exit_pipelines.c execution/builtins/pwd.c execution/builtins/unset.c \
				execution/builtins/export/export.c execution/builtins/export/complete_env.c		parsing/is_functions/is_functions_3.c	\
				parsing/check_file_or_dir.c parsing/skip_pipelines.c \

SRCS		=	${addprefix sources/, ${SRC}}

OBJ			=	${addprefix binaries/, ${SRC}}

OBJS		=	$(OBJ:%.c=%.o)

INCLUDES	=	Libft/includes/gnl Libft/includes/libc Libft/includes/ptf includes/

HEADERS 		=	includes/minishell.h includes/parsing.h

NAME		=	minishell

CC			=	cc

CFLAGS		=	-g3 -Wall -Wextra #-Werror

RM			=	rm -f

MAKEFLAGS 	+= --no-print-directory

binaries/%.o : sources/%.c ${HEADERS} Libft/libft.a Makefile | binaries
		@mkdir -p $(@D)
		$(CC) $(CFLAGS) -c $< -o $@ ${addprefix -I, ${INCLUDES}} 

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS} -LLibft -lft -lreadline

all: $(NAME)

Libft/libft.a :
	@make -C Libft

binaries :
	@mkdir -p binaries/

bonus: all

clean:
		@$(RM) -r binaries
		@make clean -C Libft

fclean:	clean
		@${RM} $(NAME)
		@make fclean -C Libft

re:		fclean all

.PHONY: all bonus clean fclean re
