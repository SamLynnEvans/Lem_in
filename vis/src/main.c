/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:41:13 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/13 12:08:22 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

void	error_exit(int a)
{
	if (a == 0)
		ft_putstr("ERROR\n");
	if (a == 1)
		ft_putstr("map too large\n");
	exit(1);
}

int		main(void)
{
	t_vis	v;
	int		fd;

	get_emo(&v);
		fd = 0;
	if (!(v.ants = get_ants(fd)))
		error_exit(0);
	if (!(build_info(&v, fd)))
		error_exit(0);
	if (!(v.n = create_nodes(&v)))
		error_exit(0);
	if (!(v.moves = get_moves(fd, &v)))
		error_exit(0);
	visualiser(&v);
}
