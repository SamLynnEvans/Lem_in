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
	mlx_string_put(v->mlx, v->win, 470, 300, 0xFFFFFF, "ANTZ");
	mlx_string_put(v->mlx, v->win, 390, 330, 0xFFFFFF, "press enter to begin");
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

	if (v->mv == -1)
	{
		print_emoji(v->data, v->sl, v->e, v->n[0].put);
		return ;
	}
	i = 0;
	while (1)
	{
		j = -1;
		if (!(i = get_move(&ant, room, v->moves[v->mv], i)))
			break ;
		while (++j < v->rooms)
			if (!(ft_strcmp(v->n[j].name, room)))
				break;
		print_emoji(v->data, v->sl, &(v->e[(ant - 1) % 17]), v->n[j].put);
	}
	if (ant < v->ants)
		print_emoji(v->data, v->sl, &(v->e[ant % 17]), v->n[0].put);
}

int	play_game(t_vis *v)
{
	int	i;

	i = 0;
	v->img = mlx_new_image(v->mlx, 1200, 800);
	v->data = mlx_get_data_addr(v->img, &(v->bpp), &(v->sl), &(v->endian));
	while (i < v->rooms)
	{
		if (!(put_room(v, i)))
			return (0);
		i++;
	}
	mlx_clear_window(v->mlx, v->win);
	print_ants(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	return (1);
}

int		begin_game(int key, t_vis *v)
{
	static int first = 0;

	ft_intdebug(key, "key");
	if (key == 53)
			exit(1);
	if (key == 124 && first)
	{
		if (v->mv + 1 < v->mv_count)
			v->mv++;
		play_game(v);
	}
	if (key == 36 && !first)
	{
		play_game(v);
		first = 1;
	}
	return (1);
}

void	visualiser(t_vis *v)
{
	int	i;
	i = 0;
	while (i < v->rooms)
		free(v->lines[i++]);
	free(v->lines);
	v->mv = -1;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, 1200, 800, "ANTS");
	mlx_key_hook(v->win, begin_game, v);
	print_start(v);
//	print_toscreen(v);
//	start_game(v);
	mlx_loop(v->mlx);
//	ft_putstr("poo");
}
