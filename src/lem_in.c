/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:29:21 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/28 13:57:11 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		*get_path(t_node *n)
{
	int	i;
	int	*path;
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (n[j].end != 1)
		j++;
	i = j;
	while (n[i].start != 1)
	{
		i = n[i].parent;
		count++;
	}
	if (!(path = malloc(sizeof(int) * (count + 1))))
		error_exit();
	path[0] = count;
	i = 1;
	while (n[j].start != 1)
	{
		path[i++] = j;
		j = n[j].parent;
	}
	return (path);
}

int		**add_route(t_node *n, t_lem *l)
{
	int	**routes;
	int	i;

	i = -1;
	if (!(routes = malloc(sizeof(int *) * (l->route_no + 1))))
		error_exit();
	while (++i < l->route_no)
		routes[i] = l->routes[i];
	routes[i] = get_path(n);
	if (l->route_no != 0)
		free(l->routes);
	return (routes);
}

void	reset_nodes(t_node *n, t_lem *l)
{
	int	i;
	int	j;

	i = 0;
	while (i < l->rooms)
	{
		n[i].parent = -1;
		n[i].open = 1;
		n[i].distance = (n[i].start) ? 0 : INT_MAX;
		i++;
	}
	i = 0;
	while (i < l->route_no)
	{
		j = 2;
		while (j <= l->routes[i][0])
			n[l->routes[i][j++]].open = 0;
		i++;
	}
}

int		lem_in(t_node *n, t_lem *l)
{
	l->route_no = 0;
	while (l->route_no < l->ants && djikstra(n, l))
	{
		l->routes = add_route(n, l);
		l->route_no++;
		reset_nodes(n, l);
	}
	return ((l->route_no > 0) ? 1 : 0);
}
