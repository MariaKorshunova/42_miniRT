# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpoetess <bpoetess@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 16:43:25 by jmabel            #+#    #+#              #
#    Updated: 2022/10/06 18:06:03 by bpoetess         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY		:	all clean fclean re libft

NAME		=	miniRT

HEADER		=	$(addprefix include/,\
					minirt.h\
					vector.h\
					parser.h\
					scene.h\
					get_next_line.h)

CFLAGS		=	-I include

CFLAGS		+=	-Wall -Wextra -Werror

RM			=	rm -rf

LIBFT		=	./libft/libft.a
LIBFT_H		=	./libft/libft.h

LIBMLX		=	./libmlx/libmlx.a

FILE_C		=	main.c

FILE_C		+=	$(addprefix vector/,\
				scalar_product.c\
				vector_create.c\
				vector_length_normalizing.c\
				vector_linear_operations.c\
				vector_print.c)

FILE_C		+=	$(addprefix utils/,\
				get_next_line.c\
				print_scene.c)
				
FILE_C		+=	$(addprefix parser/,\
				parser.c\
				free_scene.c\
				parser_readscene.c\
				parser_utils.c\
				parser_readfloat.c)

SRCS		=	$(addprefix src/, $(FILE_C))

OBJ			=	$(addprefix objects/, $(FILE_C:%.c=%.o))

FOLDER		=	$(sort $(dir objects/ $(OBJ)))

all			:	$(FOLDER) $(LIBFT) $(LIBMLX) $(NAME)

$(NAME)		:	$(OBJ) $(LIBFT) $(LIBMLX)
				$(CC) $(CFLAGS) $(LIBFT) $(LIBMLX) -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)

$(LIBFT)		:	libft_obj
				make -C ./libft

libft_obj	:
				mkdir libft_obj

$(LIBMLX)		:
				make -C ./libmlx


$(FOLDER)	:
				mkdir -p $@

objects/%.o	:	./src/%.c $(HEADER) Makefile $(LIBFT_H)
				$(CC) $(CFLAGS) -c $< -o $@

clean		:
				$(RM) $(OBJ)
				$(RM) $(FOLDER)
				make clean -C ./libft
				make clean -C ./libmlx
				$(RM) libft_obj

fclean		:	clean
				$(RM) $(NAME)
				make fclean -C ./libft

re			:	fclean all