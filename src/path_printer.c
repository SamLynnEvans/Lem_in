#include "lem_in.h"

void	print_info(t_lem *l)
{
	int	i;

	i = 0;
	ft_printf("%d\n##start\n%s\n##end\n%s\n", l->ants, l->lines[l->start], l->lines[l->end]);
	while (i < l->count)
	{
		if (i != l->start && i != l->end)
			ft_printf("%s\n", l->lines[i]);
		free(l->lines[i]);
		i++;
	}
	free(l->lines);
	ft_printf("\n");
}

int		move_ants(t_lem *l, int a[l->ants][2], t_node *n, int moving_ants)
{
	int	i;
	int	ret;
	int	first;

	first = 0;
	ret = 0;
	i = 0;
	while (i < moving_ants)
	{
		if (a[i][0] == -1)
			i++;
		else
		{
			if (first++)
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
	ants[1] = dist - 2;
}

void	print_paths(t_node *n, t_lem *l)
{
	int	a[l->ants][2];
	int	i;
	int	j;

	print_info(l);
	i = 0;
//	set_ants(l->ants, a);
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
			else if (l->routes[j][0] - l->routes[0][0] < l->ants - i - (j - 1))
				set_ant(l->routes[j][0], a[i++], j);
			j++;
		}
	}
	while (move_ants(l, a, n, i))
		;
}
