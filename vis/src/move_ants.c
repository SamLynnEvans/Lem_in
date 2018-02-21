#include "vis.h"

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
		end_check = (j == 1) ? 1 : end_check;
		v->home[v->mv + 1] += (j == 1 && !v->done) ? 1 : 0;
	}
	v->home[v->mv + 1] += (v->done || v->mv == -1) ? 0 : v->home[v->mv];
	if (ant < v->ants)
		print_emoji(v->data, v->sl, &(v->e[ant % 15]), v->n[0].put);
}

void	print_title(t_vis *v)
{
	char *num;

	mlx_string_put(v->mlx, v->win, 590, 30, 0xFFFFFF, "ANTZ");
	mlx_string_put(v->mlx, v->win, 565, 55, 0xFFFFFF, "Turn : ");
	mlx_string_put(v->mlx, v->win, 640, 55, 0xFFFFFF, (num = ft_itoa(v->mv + 1)));
	free(num);
	mlx_string_put(v->mlx, v->win, 565, 70, 0xFFFFFF, "Home : ");
	mlx_string_put(v->mlx, v->win, 640, 70, 0xFFFFFF, (num = ft_itoa(v->home[v->mv + 1])));
	free(num);
}


int	put_room(t_vis *v, int i)
{
	int	p1[2];
	int	p2[2];

	p1[X] = (v->size + 8) * v->n[i].coords[0] + 1;
	p1[Y] = (v->size + 20) * v->n[i].coords[1] + 16;
	v->n[i].put = (p1[X] * 4) + p1[Y] * v->sl;
	p2[X] = (v->size + 8) * v->n[i].coords[0] + 1 + v->size;
	p2[Y] = (v->size + 20) * v->n[i].coords[1] + 16;
	draw_line(p1, p2, v, 0xFFFFFF);
	p2[X] = (v->size + 8) * v->n[i].coords[0] + 1;
	p2[Y] = (v->size + 20) * v->n[i].coords[1] + 16 + v->size;
	draw_line(p1, p2, v, 0xFFFFFF);
	p1[X] = (v->size + 8) * v->n[i].coords[0] + 1 + v->size;
	p1[Y] = (v->size + 20) * v->n[i].coords[1] + 16 + v->size;
	draw_line(p2, p1, v, 0xFFFFFF);
	p2[X] = (v->size + 8) * v->n[i].coords[0] + 1 + v->size;
	p2[Y] = (v->size + 20) * v->n[i].coords[1] + 16;
	draw_line(p2, p1, v, 0xFFFFFF);
	draw_links(v, i);
	return (1);
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
	print_ants(v);
	mlx_clear_window(v->mlx, v->win);
	mlx_put_image_to_window(v->mlx, v->win, v->img, (1200 - v->width) / 2, (700 - v->height) / 2);
	print_title(v);
	free(v->data);
	free(v->img);
	return (1);
}
