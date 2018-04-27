/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 13:35:18 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/27 11:44:42 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H
# define X 0
# define Y 1
# define W 50

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "mlx.h"
# include <fcntl.h>
# include <limits.h>

typedef struct	s_node
{
	char		*name;
	int			*links;
	int			coords[2];
	int			end;
	int			start;
	int			put;
}				t_node;

typedef struct	s_emo
{
	int			**emoji;
	int			x_max;
	int			y_max;
}				t_emo;

typedef struct	s_vis
{
	char		**moves;
	int			mv_count;
	int			mv;
	int			ants;
	int			rooms;
	int			done;
	int			*home;
	int			start;
	int			end;
	char		**lines;
	int			count;
	void		*mlx;
	void		*win;
	char		*data;
	void		*img;
	int			sl;
	int			endian;
	int			bpp;
	int			size;
	int			width;
	int			height;
	t_node		*n;
	t_emo		*e;
}				t_vis;

void			get_emo(t_vis *v);
int				get_coords(char *str, int coords[2]);
t_node			*create_nodes(t_vis *v);
void			visualiser(t_vis *v);
void			error_exit(int a);
void			put_pixel_img(t_vis *v, int x, int y, int color);
void			print_emoji(char *data, int sl, t_emo *e, int pos);
int				play_game(t_vis *v);
void			draw_links(t_vis *v, int i);
void			draw_line(int p1[2], int p2[2], t_vis *v, int col);
int				build_info(t_vis *v, int fd);
int				get_ants(int fd);
char			**get_moves(int fd, t_vis *v);

#endif
