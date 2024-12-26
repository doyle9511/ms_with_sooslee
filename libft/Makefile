# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donghwi2 <donghwi2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 22:02:53 by donghwi2          #+#    #+#              #
#    Updated: 2024/03/08 01:47:32 by donghwi2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	=	libft.a
SRCS 	=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
B_SRCS	=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
HEADR	=	libft.h
CC 		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
OBJS 	=	$(SRCS:.c=.o)
B_OBJS 	=	$(B_SRCS:.c=.o)
AL_OBJS	=	$(OBJS) $(B_OBJS)

.PHONY	: all clean fclean re bonus

all		: make_a

bonus 	: make_b

make_a	: $(OBJS) $(HEADR)
	ar rcs $(NAME) $(OBJS)
	touch $@

make_b	: $(AL_OBJS)
	ar rcs $(NAME) $^
	touch $@

%.o		: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	rm -f $(AL_OBJS)
	rm -f make_a make_b

fclean	: clean
	rm -f $(NAME)

re		: fclean all
