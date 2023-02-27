NAME		=	minishell

SRCS		=	sources/main.c						 \

OBJS		=	$(SRCS:.c=.o)

LIB			=	libft.a

LIBFT		=	libft

INCLUDES	=	-Ilibft

CC			=	cc

CFLAGS		=	-Wall -Wextra #-Werror

RM			=	rm -f

all:	libs $(NAME)

$(NAME): $(OBJS)
		$(CC) $(OBJS) $(LIBFT)/libft.a -lreadline -o $(NAME)

%.o:	%.c minishell.h Makefile
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libs:
		@$(MAKE) -C $(LIBFT)

clean:
		@$(RM) $(OBJS)
		@$(MAKE) clean -C $(LIBFT)

fclean:	clean
		@$(RM) $(NAME)
		@$(MAKE) fclean -C $(LIBFT)

re:		fclean all

.PHONY: all libs clean fclean re
