INCLUDES = -I../libft/Includes/ -Iminilibx/ -I.

SRC_PATH = src

SRC_NAME = main.c build_rooms.c draw.c lines.c emo.c

NAME = vis

DEPS = vis.h

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = obj

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

FLAGS = -Wall -Werror -Wextra

VFLAGS = -framework Appkit -framework OpenGL

all : library $(NAME)

$(NAME) : $(OBJ) $(DEPS)
	gcc -o $@ $(OBJ) $(INCLUDES) $(FLAGS) ../libft/libft.a minilibx/libmlx.a $(VFLAGS)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	gcc -o $@ -c $^ $(INCLUDES) $(FLAGS)

library :
	make -C minilibx/
	make -C ../libft/

clean :
	make clean -C minilibx/
	make clean -C ../libft/
	rm -fr $(OBJ_PATH)

fclean : clean
	make fclean -C ../libft/
	rm -f $(NAME)

re : fclean all
