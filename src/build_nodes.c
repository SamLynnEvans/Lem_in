/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:01:21 by slynn-ev          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/02/28 14:00:29 by slynn-ev         ###   ########.fr       */
=======
/*   Updated: 2018/02/28 14:30:00 by slynn-ev         ###   ########.fr       */
>>>>>>> tmp
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		fill_nodes(t_node *node, t_lem *l, int j)
{
	int	i;

	i = 0;
	while (l->lines[j][i] != ' ')
		i++;
	if (!i || !(node[j].name = malloc(i + 1)))
		return (0);
	ft_strncpy(node[j].name, l->lines[j], i);
	node[j].name[i] = '\0';
	if (ft_strchr(node[j].name, '-'))
		error_exit();
	node[j].distance = (j == l->start) ? 0 : INT_MAX;
	node[j].open = 1;
	node[j].parent = -1;
	node[j].start = (j == l->start) ? 1 : 0;
	node[j].end = (j == l->end) ? 1 : 0;
	if (!(node[j].links = malloc(sizeof(int) * 1)))
		error_exit();
	node[j].links[0] = -1;
	return (1);
}

void	add_link(t_node *node, int j)
{
	int	i;
	int	*links;

	i = 0;
	while (node->links[i] != -1)
		i++;
	if (!(links = malloc(sizeof(int) * (i + 3))))
		error_exit();
	i = -1;
	while (node->links[++i] != -1)
		links[i] = node->links[i];
	links[i++] = j;
	links[i] = -1;
	free(node->links);
	node->links = links;
}

int		free_split(char **split)
{
	free(split[0]);
	free(split[1]);
	free(split);
	return (0);
}

int		link_nodes(t_node *nodes, t_lem *l, char *line)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	while (line[i] != '-' && line[i] != '\0')
		i++;
	if (!(split = malloc(sizeof(char *) * 2)) || !line[i])
		error_exit();
	split[0] = ft_strsub(line, 0, i++);
	split[1] = ft_strsub(line, i, ft_strlen(line));
	i = -1;
	j = -1;
	while (++i < l->rooms)
		if (ft_strcmp(nodes[i].name, split[0]) == 0)
			while (++j < l->rooms)
				if (ft_strcmp(nodes[j].name, split[1]) == 0)
				{
					add_link(&nodes[i], j);
					add_link(&nodes[j], i);
					free_split(split);
					return ((i == j) ? 0 : 1);
				}
	return (free_split(split));
}

t_node	*create_nodes(t_lem *l)
{
	int		i;
	t_node	*nodes;
	int		j;

	i = -1;
	while (++i < l->count)
		if (ft_strchr(l->lines[i], '-'))
			break ;
	if (i == l->count)
		return (NULL);
	l->rooms = i;
	if (!(nodes = malloc(sizeof(t_node) * (i + 1))))
		error_exit();
	j = -1;
	while (++j < i)
		if (!(fill_nodes(nodes, l, j)))
			return (NULL);
	while (i < l->count)
		if (!(link_nodes(nodes, l, l->lines[i++])))
			return (NULL);
	return (nodes);
}
