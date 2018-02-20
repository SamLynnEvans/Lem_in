#include "vis.h"

int	fill_nodes(t_node *node, t_vis *v, int j)
{
	int	i;

	i = 0;
	while (v->lines[j][i] != ' ')
		i++;
	if (!i || !(node[j].name = malloc(i + 1)))
		return (0);
	ft_strncpy(node[j].name, v->lines[j], i);
	node[j].name[i++] = '\0';
	node[j].coords[0] = ft_atoi(v->lines[j] + i);
	while (ft_isdigit(v->lines[j][i]))
		i++;
	node[j].coords[1] = ft_atoi(v->lines[j] + i + 1);
	node[j].start = (j == v->start) ? 1 : 0;
	node[j].end = (j == v->end) ? 1 : 0;
	node[j].links = malloc(sizeof(int) * 1);
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
	links = malloc(sizeof(int) * (i + 4));
	i = -1;
	while (node->links[++i] != -1)
		links[i] = node->links[i];
	links[i++] = j;
	links[i] = -1;
	free(node->links);
	node->links = links;
}

void	free_split(char **split)
{
	free(split[0]);
	free(split[1]);
	free(split);
}

int	link_nodes(t_node *nodes, t_vis *v, char *line)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	split = malloc(sizeof(char *) * 2);
	while (line[i] != '-')
		i++;
	split[0] = ft_strsub(line, 0, i++);
	split[1] = ft_strsub(line, i, ft_strlen(line));
	i = -1;
	j = -1;
	while (++i < v->rooms)
		if (ft_strcmp(nodes[i].name, split[0]) == 0)
			while (++j < v->rooms)
				if (ft_strcmp(nodes[j].name, split[1]) == 0)
				{
					add_link(&nodes[i], j);
					add_link(&nodes[j], i);
					free_split(split);
					return ((i == j) ? 0 : 1);
				}
	free_split(split);
	return (0);
}

t_node *create_nodes(t_vis *v)
{
	int		i;
	t_node	*nodes;
	int		j;

	i = -1;
	while (++i < v->count)
		if (ft_strchr(v->lines[i], '-'))
			break ;
	if (i == v->count)
		return (NULL);
	v->rooms = i;
	nodes = malloc(sizeof(t_node) * (i + 1));
	j = -1;
	while (++j < i)
		if (!(fill_nodes(nodes, v, j)))
			return (NULL);
	while (i < v->count)
		if (!(link_nodes(nodes, v, v->lines[i++])))
			return (NULL);
	return (nodes);
}
