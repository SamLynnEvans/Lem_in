#include "lem_in.h"

void	evaluate_node(t_node *n, int i)
{
	int	j;
	int	link;

	j = 0;
	while (n[i].links[j] != -1)
	{
		link = n[i].links[j];
		if (n[link].open == 1 &&
		n[link].distance > n[i].distance + 1)
		{
			n[link].distance = n[i].distance + 1;
			n[link].parent = i;
		}
		j++;
	}
	n[i].open = 0;
}

int	djikstra(t_node *n, t_lem *l)
{
	int	i;
	int	d_min;
	int	closest;
	int	all_close;

	closest = 0;
	while (1)
	{
		i = -1; 
		d_min = INT_MAX;
		all_close = 1;
		while (++i < l->rooms)
		{
			if (n[i].open)
				all_close = 0;
			if (n[i].open && d_min > n[i].distance)
			{
				d_min = n[i].distance;
				closest = i;
			}
		}
		if (d_min == INT_MAX)
			return (all_close == 1) ? 1 : 0;
		evaluate_node(n, closest);
	}
}

int	*get_path(t_node *n)
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
	path = malloc(sizeof(int) * (count + 2));
	path[0] = count + 2;
	i = 1;
	while (n[j].start != 1)
	{
		path[i++] = j;
		j = n[j].parent;
	}
	path[i++] = j;
	return (path);
}

int	**get_route(t_node *n, t_lem *l)
{
	int	**routes;
	int	i;

	i = -1;
	routes = malloc(sizeof(int *) * (l->route_no + 1));
	while (++i < l->route_no)
		routes[i] = l->routes[i];
	routes[i] = get_path(n);
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
		while (j < l->routes[i][0] - 1)
			n[l->routes[i][j++]].open = 0;
		i++;
	}
}

int	lem_in(t_node *n, t_lem *l)
{
	l->route_no = 0;
	while (l->route_no < l->ants && djikstra(n , l))
	{
		l->routes = get_route(n, l);
		l->route_no++;
		reset_nodes(n, l);
	}
	int i;
	int	j;

	i = 0;
	while (i < l->route_no)
	{
		j = 1;	
		while (j < l->routes[i][0])
		{
			ft_putstr(n[l->routes[i][j++]].name);
			ft_putstr(", ");
		}
		ft_putchar('\n');
		i++;
	}
	return ((l->route_no > 0) ? 1 : 0);
}

/*

	int i;
	int	j;

	i = 0;
	while (i < l->route_no)
	{
		j = 1;	
		while (j < l->routes[i][0])
		{
			ft_putstr(n[l->routes[i][j++]].name);
			ft_putstr(", ");
		}
		ft_putchar('\n');
		i++;
	}
*/
