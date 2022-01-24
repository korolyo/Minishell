
NAME	= libft.a
CC		= gcc
CFLAGS	=	-Werror -Wall -Wextra -O3 -c
INCLUDES =	-I$(HEADERS_DIR)

HEADERS_LIST	= libft.h\

HEADERS_DIR	= includes/
HEADERS =	$(addprefix $(HEADERS_DIR), $(HEADERS_LIST))

LIST	= 	ft_atoi.c		ft_bzero.c			ft_isalnum.c\
			ft_isalpha.c	ft_isascii.c		ft_isdigit.c\
			ft_isprint.c	ft_itoa.c			ft_memccpy.c\
			ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c\
			ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c\
			ft_lstclear.c	ft_lstiter.c		ft_lstmap.c\
			ft_memchr.c		ft_memcmp.c			ft_memcpy.c\
			ft_memmove.c	ft_memset.c			ft_putchar_fd.c\
			ft_putendl_fd.c	ft_putnbr_fd.c		ft_putstr_fd.c\
			ft_strchr.c		ft_strdup.c			ft_calloc.c\
			ft_strjoin.c	ft_strlen.c			ft_strlcat.c\
			ft_split.c		ft_strlcpy.c		ft_strncmp.c\
			ft_strnstr.c	ft_strmapi.c		ft_strrchr.c\
			ft_substr.c		ft_strtrim.c		ft_tolower.c\
			ft_toupper.c	get_next_line.c		ft_atol.c\

OBJS	=	$(patsubst %.c, %.o, $(LIST))

.PHONY:	all clean fclean re

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

%.o	:	%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

clean:
		@rm -f $(OBJS)

fclean:	clean
		@rm -f $(NAME)

re:		fclean all

