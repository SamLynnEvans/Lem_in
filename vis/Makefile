INCLUDES = -I../libft/Includes/ -Iminilibx/

SRC = main.c build_rooms.c draw.c

NAME = vis

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

VFLAGS = -framework Appkit -framework OpenGL

all : library $(NAME)

$(NAME) : $(OBJ)
	gcc -o $@ $^ $(INCLUDES) $(FLAGS) ../libft/libft.a minilibx/libmlx.a $(VFLAGS)

%.o : %.c
	gcc -o $@ -c $^ $(INCLUDES) $(FLAGS)

library :
	make -C minilibx/
	make -C ../libft/

clean :
	make clean -C minilibx/
	make clean -C ../libft/
	rm -f *.o
