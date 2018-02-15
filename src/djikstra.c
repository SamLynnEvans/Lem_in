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

int		djikstra(t_node *n, t_lem *l)
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
