SRC =	src/main.c							\
		src/dict/dict_utils.c				\
											\
		src/lexer/lexer.c					\
		src/lexer/lexer_utils.c				\
		src/lexer/type_lexer.c				\
		src/lexer/add_to_lst_lexer.c		\
											\
		src/parser/parser.c					\
		src/parser/parser_utils.c			\
		src/parser/parser_free.c			\
		src/parser/parser_redirect.c		\
		src/parser/parser_arg.c				\
											\
		src/pre_action/pre_action.c			\
		src/pre_action/pre_action_fork.c	\
		src/pre_action/pre_action_utils.c	\
		src/pre_action/redirect.c			\
		src/pre_action/redirect_utils.c		\
		src/pre_action/heredoc.c			\
		src/pre_action/dup.c				\
											\
		src/pipe/pipe.c						\
											\
		src/pre_action/pre_builtins.c		\
											\
		src/builtin/echo.c					\
		src/builtin/pwd.c					\
		src/builtin/cd.c					\
        src/builtin/exit.c					\
        src/builtin/export.c				\
        src/builtin/export_utils.c			\
		src/builtin/export_utils2.c			\
        src/builtin/unset.c					\
        src/builtin/env.c					\
											\
		src/executer/executer.c				\
        src/executer/executer_utils.c		\
											\
		src/utils/main_utils.c				\
		src/utils/main_utils2.c				\
		src/utils/env_utils.c				\
		src/utils/env_utils2.c				\
		src/utils/env_utils3.c				\
											\
		src/signal/signal.c









OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

NAME 		= minishell
LIBFT		= src/libft/libft.a
LIBFTDIR	= src/libft
CFLAGS 		=  -g	-Wall -Wextra -Werror
#CFLAGS		+= -fsanitize=address
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

flcean:		clean
	@make -C $(LIBFTDIR) fclean
	$(RM) $(NAME)


re:			fclean all

.PHONY:		all clean fclean re

-include $(DEP)

