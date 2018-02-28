/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:28:53 by slynn-ev          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/02/28 13:59:01 by slynn-ev         ###   ########.fr       */
=======
/*   Updated: 2018/02/28 19:35:06 by slynn-ev         ###   ########.fr       */
>>>>>>> tmp
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

<<<<<<< HEAD
int		main(int ac, char **av)
=======
int		main(void)
>>>>>>> tmp
{
	t_node	*nodes;
	t_lem	lem;

	if (!(lem.ants = get_ants(0)))
		error_exit();
	if (!(build_info(0, &lem)))
		error_exit();
	if (!(nodes = create_nodes(&lem)))
		error_exit();
	if (!(lem_in(nodes, &lem)))
		error_exit();
	print_paths(nodes, &lem);
	free_all(&lem, nodes);
}
