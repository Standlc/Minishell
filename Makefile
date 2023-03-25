SRC			=	main.c							parsing/parse_line.c \
				parsing/parse_line_utils.c				close_program.c \
				signals.c						parsing/print_error.c \
				parsing/redirections/get_redirections.c			parsing/syntax_check/syntax_check.c \
				parsing/copy_line_word.c 				parsing/is_functions/is_functions_1.c \
				parsing/is_functions/is_functions_2.c	parsing/redirections/get_redirections_utils.c \
				parsing/syntax_check/check_syntax_utils.c 	parsing/syntax_check/check_parenthesis.c \
				parsing/wildcards.c 						\

SRCS		=	${addprefix sources/, ${SRC}}

OBJ			=	${addprefix binaries/, ${SRC}}

OBJS		=	$(OBJ:%.c=%.o)

INCLUDES	=	Libft/includes/gnl Libft/includes/libc Libft/includes/ptf includes/

HEADER 		=	includes/minishell.h

NAME		=	minishell

CC			=	cc

CFLAGS		=	-Wall -Wextra #-Werror

RM			=	rm -f

MAKEFLAGS 	+= --no-print-directory

binaries/%.o : sources/%.c ${HEADER} Libft/libft.a Makefile | binaries
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
