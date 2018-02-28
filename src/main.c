/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:28:53 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/02/28 13:59:01 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_exit(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

void	free_all(t_lem *l, t_node *n)
{
	int	i;

	i = 0;
	while (i < l->route_no)
		free(l->routes[i++]);
	free(l->routes);
	i = 0;
	while (i < l->rooms)
	{
		free(n[i].name);
		free(n[i].links);
		i++;
	}
	free(n);
}

int		main(int ac, char **av)
{
	int		fd;
	t_node	*nodes;
	t_lem	lem;

	if (ac != 2)
	{
		if (!(lem.ants = get_ants(0)))
			error_exit();
		fd = 0;
	}
	else
	{
		fd = open(av[1], O_RDONLY);
		if (!(lem.ants = get_ants(fd)))
			error_exit();
	}
	if (!(build_info(fd, &lem)))
		error_exit();
	if (!(nodes = create_nodes(&lem)))
		error_exit();
	if (!(lem_in(nodes, &lem)))
		error_exit();
	print_paths(nodes, &lem);
	free_all(&lem, nodes);
}
