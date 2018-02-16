#ifndef VIS_H
# define VIS_H

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"
#include "mlx.h"

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
}				t_vis;

typedef struct	s_node
{
	char	*name;
	int		*links;
	int		coords[2];
	int		end;
	int		start;
}				t_node;

t_node *create_nodes(t_vis *v);
void	visualiser(t_node *n, t_vis *v);

#endif
