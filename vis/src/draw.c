#include "vis.h"

void	print_start(t_vis *v)
{
	mlx_string_put(v->mlx, v->win, 570, 300, 0xFFFFFF, "ANTZ");
	mlx_string_put(v->mlx, v->win, 490, 330, 0xFFFFFF, "press enter to begin");
}

int		deal_key(int key, t_vis *v)
{
	static int first = 0;

	if (v->mv + 1 == v->mv_count)
		v->done = 1;
	if (key == 53)
			exit(1);
	if (key == 124 && v->mv >= -1 && first && v->mv + 1 < v->mv_count)
	{
		v->mv++;
		play_game(v);
	}
	if (key == 123 && v->mv >= 0)
	{
		v->mv--;
		play_game(v);
	}
	if (key == 36 && v->mv == -1 && !first)
	{
		play_game(v);
		first = 1;
	}
	return (1);
}

void	get_dimensions(t_vis *v)
{
	int	i;
	int x[2];
	int y[2];

	i = 0;
	x[0] = 1000;
	x[1] = 0;
	y[0] = 1000;
	y[1] = 0;
	while (i < v->rooms)
	{
		x[0] = (v->n[i].coords[0] < x[0]) ? v->n[i].coords[0] : x[0];
		x[1] = (v->n[i].coords[0] > x[1]) ? v->n[i].coords[0] : x[1];
		y[0] = (v->n[i].coords[1] < y[0]) ? v->n[i].coords[1] : y[0];
		y[1] = (v->n[i].coords[1] > y[1]) ? v->n[i].coords[1] : y[1];
		i++;
	}
	v->height = y[1] - y[0];
	v->width = x[1] - x[0];
	i = 0;
	while (i < v->rooms)
	{
		v->n[i].coords[0] -= x[0];
		v->n[i++].coords[1] -= y[0];
	}
}


void	visualiser(t_vis *v)
{
	int	i;
	
	v->size = 35;
	i = 0;
	while (i < v->rooms)
		free(v->lines[i++]);
	free(v->lines);
	v->done = 0;
	v->home = malloc(sizeof(int) * (v->mv_count + 1));
	i = 0;
	while (i < v->mv_count + 1)
		v->home[i++] = 0; 
	v->mv = -1;
	get_dimensions(v);
	v->height = (v->size + 20) * (v->height) + v->size + 20;
	v->width = (v->size + 8) * (v->width) + v->size + 10;
	if (v->width > 1200 || v->height > 700)
		error_exit(1);
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, 1200, 700, "ANTS");
	mlx_key_hook(v->win, deal_key, v);
	print_start(v);
	mlx_loop(v->mlx);
}
