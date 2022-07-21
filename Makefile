SRC =	src/main.c		\
		src/map/map_utils.c \

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME 		= minishell
LIBFT		= src/libft/libft.a
LIBFTDIR	= src/libft
CFLAGS 		=  -g
CPPFLAGS 	= -MMD -I./include

all:		$(LIBFT) $(NAME) Makefile

$(LIBFT):
	@make -C $(LIBFTDIR) all

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
