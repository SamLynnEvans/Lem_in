/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:28:17 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/08 13:10:57 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_exit(t_lem *l, int need_free)
{
	int	i;

	i = 0;
	if (need_free)
	{
		while (i < l->maplines)
			free(l->map[i++]);
		free(l->map);
		free(l->lines);
	}
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

int		main(void)
{
	t_node	*nodes;
	t_lem	lem;

	if ((lem.ants = get_ants(0)) <= 0)
		error_exit(&lem, 0);
	if (!(build_info(0, &lem)))
		error_exit(&lem, 1);
	if (!(nodes = create_nodes(&lem)))
		error_exit(&lem, 1);
	if (!(lem_in(nodes, &lem)))
		error_exit(&lem, 1);
	print_paths(nodes, &lem);
	free_all(&lem, nodes);
}
