#include "vis.h"
#include <locale.h>

void	print_toscreen(t_vis *v)
{
	while (1)
	{
		v->img = mlx_new_image(v->mlx, 500, 500);
		v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->sl), &(v->endian));
		v->data[0] = 0xFF;
		v->data[1] = 0xFF;
		v->data[2] = 0xFF;
		mlx_clear_window(v->mlx, v->win);
		sleep(1);
		mlx_put_image_to_window(v->mlx, v->win, v->img, 100, 100);
		sleep(1);
	}
}

void	print_start(t_vis *v)
{
	mlx_string_put(v->mlx, v->win, 570, 300, 0xFFFFFF, "ANTZ");
	mlx_string_put(v->mlx, v->win, 490, 330, 0xFFFFFF, "press enter to begin");
}

int	get_move(int *ant, char *room, char *moves, int i)
{
	int	j;
	int entered;

	j = 0;
	entered = 0;
	while (moves[i])
	{
		entered = 1;
		if (ft_isdigit(moves[i]))
			*ant = ft_atoi(moves + i);
		while (ft_isdigit(moves[i]))
			i++;
		if (moves[i] == '-')
		{
			i++;
			while (moves[i] != ' ' && moves[i] != '\0')
				room[j++] = moves[i++];
			room[j] = '\0';
			break ;
		}
		i++;
	}
	if (!moves[i] && !entered)
		return (0);
	return (i);
}

void	print_ants(t_vis *v)
{
	int	i;
	int	ant;
	char room[200];
	int	j;
	int	end_check;

	end_check = 0;
	i = 0;
	ant = 0;
	while (v->mv != -1)
	{
		j = -1;
		if (!(i = get_move(&ant, room, v->moves[v->mv], i)))
			break ;
		while (++j < v->rooms)
			if (!(ft_strcmp(v->n[j].name, room)))
				break;
		if (!v->n[j].end || !end_check)
			print_emoji(v->data, v->sl, &(v->e[(ant - 1) % 15]), v->n[j].put);
		end_check = (v->n[j].end) ? 1 : end_check;
	}
	if (ant < v->ants)
		print_emoji(v->data, v->sl, &(v->e[ant % 15]), v->n[0].put);
}

int	play_game(t_vis *v)
{
	int	i;

	i = 0;
	v->img = mlx_new_image(v->mlx, v->width, v->height);
	v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->sl), &(v->endian));
	while (i < v->rooms)
	{
		if (!(put_room(v, i)))
			return (0);
		i++;
	}
	print_emoji(v->data, v->sl, &(v->e[16]), v->n[1].put - 15 * v->sl + 20);
	print_emoji(v->data, v->sl, &(v->e[15]), v->n[0].put - 15 * v->sl - 12);
	mlx_clear_window(v->mlx, v->win);
	print_ants(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img, (1200 - v->width) / 2, (700 - v->height) / 2);
	mlx_string_put(v->mlx, v->win, 570, 30, 0xFFFFFF, "ANTZ");
	return (1);
}

int		begin_game(int key, t_vis *v)
{
	static int first = 0;

	ft_intdebug(key, "key");
	if (key == 53)
			exit(1);
	if (key == 124 && v->mv >= -1 && first)
	{
		if (v->mv + 1 < v->mv_count)
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
	v->mv = -1;
	get_dimensions(v);
	v->height = (v->size + 20) * (v->height) + v->size + 20;
	v->width = (v->size + 8) * (v->width) + v->size + 10;
	if (v->width > 1200 || v->height > 700)
	{
		ft_putstr("map too large");
		error_exit();
	}
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, 1200, 700, "ANTS");
	mlx_key_hook(v->win, begin_game, v);
	print_start(v);
	mlx_loop(v->mlx);
}
