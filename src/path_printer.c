/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:30:48 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/27 11:38:37 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		move_ants(t_lem *l, int a[1000][3], t_node *n, int moving_ants)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (i < moving_ants && i < 1000)
	{
		if (a[i][0] == -1)
			i++;
		else
		{
			if (ret)
				ft_putchar(' ');
			ft_printf("L%d-%s", a[i][2], n[l->routes[a[i][0]][a[i][1]]].name);
			a[i][1]--;
			ret = 1;
			if (a[i][1] == 0)
				a[i][0] = -1;
			i++;
		}
	}
	if (ret)
		ft_putchar('\n');
	return (ret);
}

void	set_ant(int start, int ants[3], int route, int ant_no)
{
	ants[0] = route;
	ants[1] = start;
	ants[2] = ant_no + 1;
}

void	print_paths(t_node *n, t_lem *l)
{
	int	a[1000][3];
	int	i;
	int	j;

	i = 0;
	while (i < l->ants)
	{
		j = 0;
		while (j < l->route_no && i < l->ants)
		{
			if (j == 0)
				set_ant(l->routes[j][0], a[i % 1000], j, i);
			else if (l->routes[j][0] == l->routes[0][0])
				set_ant(l->routes[j][0], a[i % 1000], j, i);
			else if (l->routes[j][0] - l->routes[0][0] <= (l->ants - i) / j)
				set_ant(l->routes[j][0], a[i % 1000], j, i);
			else
				i--;
			i++;
			j++;
		}
		move_ants(l, a, n, i);
	}
	while (move_ants(l, a, n, i))
		;
}
