/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:26:09 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/05 18:31:41 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "limits.h"

typedef struct	s_node
{
	char		*name;
	int			*links;
	int			open;
	int			parent;
	int			distance;
	int			start;
	int			end;
}				t_node;

typedef struct	s_lem
{
	char		**lines;
	char		**map;
	int			ants;
	int			start;
	int			end;
	int			rooms;
	int			count;
	int			maplines;
	int			route_no;
	int			**routes;
}				t_lem;

void			error_exit(t_lem *l, int need_free);
int				lem_in(t_node *nodes, t_lem *lem);
void			print_paths(t_node *nodes, t_lem *lem);
t_node			*create_nodes(t_lem *l);
int				djikstra(t_node *n, t_lem *l);
int				build_info(int fd, t_lem *lem);
int				get_ants(int fd);
void			free_all(t_lem *l, t_node *n);

#endif
