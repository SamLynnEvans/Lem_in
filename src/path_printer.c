/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_printer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:30:48 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/07 12:50:05 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_info(t_lem *l)
{
	int	i;

	i = 0;
	ft_putnbr(l->ants);
	ft_printf("\n");
	while (i < l->maplines)
	{
		ft_printf("%s\n", l->map[i]);
		free(l->map[i]);
		i++;
	}
	free(l->map);
	free(l->lines);
	ft_printf("\n");
}

int		move_ants(t_lem *l, int a[l->ants][2], t_node *n, int moving_ants)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (i < moving_ants)
	{
		if (a[i][0] == -1)
			i++;
		else
		{
			if (ret)
				ft_putchar(' ');
			ft_printf("L%d-%s", i + 1, n[l->routes[a[i][0]][a[i][1]]].name);
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

void	set_ant(int dist, int ants[2], int j)
{
	ants[0] = j;
	ants[1] = dist;
}

void	print_paths(t_node *n, t_lem *l)
{
	int	a[l->ants][2];
	int	i;
	int	j;

	print_info(l);
	i = 0;
	while (i < l->ants)
	{
		j = 0;
		move_ants(l, a, n, i);
		while (j < l->route_no && i < l->ants)
		{
			if (j == 0)
				set_ant(l->routes[j][0], a[i++], j);
			else if (l->routes[j][0] == l->routes[0][0])
				set_ant(l->routes[j][0], a[i++], j);
			else if (l->routes[j][0] - l->routes[0][0] <= (l->ants - i) / j)
				set_ant(l->routes[j][0], a[i++], j);
			j++;
		}
	}
	while (move_ants(l, a, n, i))
		;
}
