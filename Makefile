
NAME	=	minishell

SOURCES_LIST	= 	main.c \
					signals.c \
					preparse/preparse.c \
					preparse/preparse1.c \
					lexer/init_lexer.c \
					lexer/lexer.c \
					lexer/lexer1.c \
					lexer/lexer2.c \
					lexer/lexer_utils.c \
					redir/pipes.c \
					redir/pipes1.c \
					redir/here_doc.c \
					executor/var_handling.c \
					executor/start_executing.c \
					executor/builtins.c \
					executor/execution.c \
					executor/exec_utils.c \
					executor/ft_cd.c \
					executor/ft_echo.c \
					executor/ft_export.c \
					executor/make_redirection.c \

CC		= gcc
CFLAGS	=	-Werror -Wall -Wextra -g -I $(READLINE_INC)
LIBRARIES =	-lft -lreadline\
	-L$(LIBFT_DIRECTORY) \

INCLUDES = -I$(LIBFT_HEADERS) -I$(HEADERS_DIR)

HEADERS_LIST = \
	minishell.h\

HEADERS_DIR	=	./includes/
HEADERS =	$(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

LIBFT	=	$(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

#READLINE_INC = /opt/homebrew/Cellar/readline/8.1.2/include
#READLINE_LIB = /opt/homebrew/Cellar/readline/8.1.2/lib

#READLINE_INC = ~/.brew/opt/readline/include
#READLINE_LIB = ~/.brew/opt/readline/lib

READLINE_INC = /usr/local/opt/readline/include
READLINE_LIB =/usr/local/opt/readline/lib

OBJECTS	=	$(patsubst %.c, %.o, $(SOURCES_LIST))

.PHONY:	all clean fclean re

all	: 	$(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
		@$(CC) $(CFLAGS) $(LIBRARIES) $(INCLUDES) -I $(READLINE_INC) -L $(READLINE_LIB) $(OBJECTS) -o $(NAME)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
		@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
		@$(MAKE) clean -sC $(LIBFT_DIRECTORY)
		@rm -f $(OBJECTS)

fclean:	clean
		@rm -f $(NAME)
		@rm -f $(LIBFT)

re:		fclean all
