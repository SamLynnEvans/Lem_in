# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/28 14:49:23 by slynn-ev          #+#    #+#              #
#    Updated: 2018/02/28 14:50:19 by slynn-ev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = -Iincludes/ \
-Ilibft/Includes/ \

DEPS = includes/lem_in.h

SRC_PATH = src

SRC_NAME = main.c lem_in.c path_printer.c build_nodes.c djikstra.c read.c

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = obj

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

NAME = lem-in

LIB = libft

LIBA = libft.a

FLAGS = -Wall -Wextra -Werror

all : library $(NAME)

library :
	make -C $(LIB)

$(NAME) : $(OBJ) $(DEPS)
	gcc -o $@ $(OBJ) $(LIB)/$(LIBA)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@gcc $(FLAGS) -o $@ -c $< $(INCLUDES)

clean :
	make clean -C $(LIB)
	rm -fr $(OBJ_PATH)

fclean : clean
	make fclean -C $(LIB)
	rm -fr $(NAME)

re : fclean all
