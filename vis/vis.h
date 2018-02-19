#ifndef VIS_H
# define VIS_H
# define X 0
# define Y 1
# define W 50

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "mlx.h"

typedef struct	s_node
{
	char	*name;
	int		*links;
	int		coords[2];
	int		end;
	int		start;
//	int		put;
}				t_node;

typedef struct	s_emo
{
	int **emoji;
	int	x_max;
	int	y_max;
}				t_emo;

typedef struct	s_vis
{
	int		ants;
	int		rooms;
	int		start;
	int		end;
	char	**lines;
	int		count;
	void	*mlx;
	void	*win;
	char	*data;
	void	*img;
	int		sl;
	int		endian;
	int		bpp;
	int		size;
	t_node	*n;
	t_emo	*e;
}				t_vis;

t_emo	*get_emo(void);
t_node	*create_nodes(t_vis *v);
void	visualiser(t_vis *v);
int		put_room(t_vis *v, int i);
void	error_exit(void);
void	put_pixel_img(t_vis *v, int x, int y, int color);
void	print_emoji(char *data, int sl, t_emo *e, int pos);

#endif
