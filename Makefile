SRC			=	main.c							parse_line.c \
				parse_line_utils.c				close_program.c \

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
