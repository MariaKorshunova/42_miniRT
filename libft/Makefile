# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmabel <jmabel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 16:09:09 by jmabel            #+#    #+#              #
#    Updated: 2022/09/29 17:33:38 by jmabel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY		:	all clean fclean re bonus

NAME		=	libft.a

HEADER		=	libft.h

CFLAGS 		= 	-Wall -Wextra -Werror

RM 			= 	rm -rf
CC 			= 	cc 

SRCS		=	ft_isalpha.c	ft_isdigit.c	ft_isalnum.c	ft_isascii.c\
				ft_isprint.c	ft_strlen.c		ft_memset.c		ft_bzero.c\
				ft_memcpy.c		ft_memmove.c	ft_strlcpy.c	ft_strlcat.c\
				ft_toupper.c	ft_tolower.c	ft_strchr.c		ft_strrchr.c\
				ft_strncmp.c	ft_memchr.c		ft_memcmp.c		ft_strnstr.c\
				ft_atoi.c		ft_calloc.c		ft_strdup.c		ft_substr.c\
				ft_strjoin.c	ft_strtrim.c	ft_putchar_fd.c	ft_putstr_fd.c\
				ft_putendl_fd.c	ft_putnbr_fd.c	ft_itoa.c		ft_split.c\
				ft_striteri.c	ft_strmapi.c\
				ft_lstnew.c			ft_lstadd_front.c\
				ft_lstsize.c		ft_lstlast.c\
				ft_lstadd_back.c	ft_lstdelone.c\
				ft_lstclear.c		ft_lstiter.c\
				ft_lstmap.c

OBJ			=	$(addprefix ../libft_obj/, $(SRCS:.c=.o))

all					:	$(NAME)

$(NAME)				:	$(OBJ)
	ar rcs $(NAME) $(OBJ)

../libft_obj/%.o	: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean 		:
	$(RM) $(OBJ)

fclean		: clean
	$(RM) $(NAME)

re			: fclean all