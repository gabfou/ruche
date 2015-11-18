#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfournie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/04 12:38:41 by gfournie          #+#    #+#              #
#    Updated: 2015/11/18 09:23:44 by gfournie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_gkrellm

FLAG = -Wall -Werror -Wextra #-framework OpenGL -framework AppKit#

SRC = src/main.cpp src/Processor.class.cpp src/Host.class.cpp src/render.cpp src/graphic.cpp #mlx/mlx_shaders.cpp mlx/mlx_new_window.m mlx/mlx_init_loop.m mlx/mlx_new_image.m mlx/mlx_xpm.cpp mlx/mlx_int_str_to_wordtab.cpp

OBJ = src/main.o src/Processor.class.o src/Host.class.o src/render.o# -lncurses -framework OpenGL -framework AppKit

all:$(NAME)

$(NAME):
	g++ -o $(NAME) $(FLAG) $(SRC) -lncurses libmlx.a -framework OpenGL -framework AppKit

clean:
#	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all