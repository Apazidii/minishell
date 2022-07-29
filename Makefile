SRC =	src/main.c						\
		src/dict/dict_utils.c			\
		src/lexer/lexer.c				\
		src/lexer/lexer_utils.c			\
		src/parser/parser.c				\
		src/parser/parser_utils.c		\
		src/parser/parser_str.c			\
		src/parser/parser_int.c			\
		src/parser/parser_redirect.c	\






OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME 		= minishell
LIBFT		= src/libft/libft.a
LIBFTDIR	= src/libft
CFLAGS 		=  -g
CPPFLAGS 	= -MMD -I./hdr

all:		$(LIBFT) $(NAME) Makefile

$(LIBFT):
	@make -C $(LIBFTDIR) all
	@make -C $(LIBFTDIR) bonus

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@

clean:
	@make -C $(LIBFTDIR) clean
	$(RM) $(OBJ) $(DEP)

fclean:		clean
	@make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)

