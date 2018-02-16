/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 15:32:14 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/03 11:46:19 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	put_pixel_img(t_vis *v, int x, int y, int color)
{
	int	pos;

	pos = (x * 4) + (y * v->sl);
	v->data[pos++] = color;
	v->data[pos++] = color >> 8;
	v->data[pos] = color >> 16;
}

void	gentle_line(int p1[4], int p2[4], t_vis *v, int col)
{
	int dx;
	int dy;
	int	p;
	int	neg;

	neg = (p2[Y] - p1[Y] > 0) ? 1 : -1;
	dx = ft_abs(p2[X] - p1[X]);
	dy = ft_abs(p2[Y] - p1[Y]);
	p = 2 * dy - dx;
	while (p1[X] < p2[X])
	{
		if (p < 0)
			p = p + 2 * dy;
		else
		{
			p1[Y] += neg;
			p = p + 2 * dy - 2 * dx;
		}
		put_pixel_img(v, p1[X]++, p1[Y], col);
	}
}

void	steep_line(int p1[4], int p2[4], t_vis *v, int col)
{
	int dx;
	int dy;
	int	p;
	int	neg;

	neg = (p2[Y] - p1[Y] > 0) ? 1 : -1;
	dx = ft_abs(p2[X] - p1[X]);
	dy = ft_abs(p2[Y] - p1[Y]);
	p = 2 * dx - dy;
	while (p1[Y] < p2[Y])
	{
		if (p < 0)
			p = p + 2 * dx;
		else
		{
			p1[X]++;
			p = p + 2 * dx - 2 * dy;
		}
		put_pixel_img(v, p1[X] - 1, p1[Y], col);
		p1[Y] += neg;
	}
}

void	draw_line(int p1[2], int p2[2], t_vis *v, int col)
{
	int p1_copy[2];
	int	p2_copy[2];
	int	i;

	i = 0;
	while (i < 2)
	{
		p1_copy[i] = p1[i];
		p2_copy[i] = p2[i];
		i++;
	}
	if ((p2[X] - p1[X] == 0) || ft_abs((p2[Y] - p1[Y]) / (p2[X] - p1[X])) >= 1)
		steep_line(p1_copy, p2_copy, v, col);
	else
		gentle_line(p1_copy, p2_copy, v, col);
}

void	draw_links(t_vis *v, int i)
{
	int	j;
	int	p1[2];
	int	p2[2];

	j = 0;
	p1[X] = (v->size + 8) * v->n[i].coords[0] + 1 + v->size / 2;
	p1[Y] = (v->size + 16) * v->n[i].coords[1] + 1 + v->size / 2;
	while (v->n[i].links[j] != -1)
	{
		p2[X] = (v->size + 8) * v->n[v->n[i].links[j]].coords[0] + 1 + v->size / 2;
		p2[Y] = (v->size + 16) * v->n[v->n[i].links[j]].coords[1] + 1 + v->size / 2;
		if (p1[X] < p2[X])
			draw_line(p1, p2, v, 0xFF8134);
		else
			draw_line(p2, p1, v, 0xFF8134);
		j++;
	}
}

int	put_room(t_vis *v, int i)
{
	int	p1[2];
	int	p2[2];

	v->size = 30;
	p1[X] = (v->size + 8) * v->n[i].coords[0] + 1;
	p1[Y] = (v->size + 16) * v->n[i].coords[1] + 1;
	mlx_string_put(v->mlx, v->win, p1[X] - 10, p1[Y] - 10, 0xFFFFFF, v->n[i].name);
	p2[X] = (v->size + 8) * v->n[i].coords[0] + 1 + v->size;
	p2[Y] = (v->size + 16) * v->n[i].coords[1] + 1;
	draw_line(p1, p2, v, 0xFFFFFF);
	p2[X] = (v->size + 8) * v->n[i].coords[0] + 1;
	p2[Y] = (v->size + 16) * v->n[i].coords[1] + 1 + v->size;
	draw_line(p1, p2, v, 0xFFFFFF);
	p1[X] = (v->size + 8) * v->n[i].coords[0] + 1 + v->size;
	p1[Y] = (v->size + 16) * v->n[i].coords[1] + 1 + v->size;
	draw_line(p2, p1, v, 0xFFFFFF);
	p2[X] = (v->size + 8) * v->n[i].coords[0] + 1 + v->size;
	p2[Y] = (v->size + 16) * v->n[i].coords[1] + 1;
	draw_line(p2, p1, v, 0xFFFFFF);
	draw_links(v, i);
	return (1);
}
