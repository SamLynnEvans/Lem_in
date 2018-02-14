#include "lem_in.h"

void	error_exit(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

char	**ft_add_charpointer(char **array, char *content, int count)
{
	char	**ret;
	int		i;

	if (content == NULL || count < 0)
		return (NULL);
	ret = malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (++i < count)
		ret[i] = array[i];
	ret[i] = content;
	if (count != 0)
		free(array);
	return (ret);
}

int	fill_nodes(t_node *node, t_lem *l, int j)
{
	int	i;

	i = 0;
	while (l->lines[j][i] != ' ')
		i++;
	if (!i || !(node[j].name = malloc(i + 1)))
		return (0);
	ft_strncpy(node[j].name, l->lines[j], i);
	node[j].name[i] = '\0';
	node->distance = (j == l->start) ? 0 : INT_MAX;
	node->open = 1;
	node->parent = -1;
	node->start = (j == l->start) ? 1 : 0;
	node->end = (j == l->end) ? 1 : 0;
	node->links = malloc(sizeof(int));
	node->links[0] = -1;
	return (1);
}

void	add_link(t_node *node, int j)
{
	int	i;
	int	*links;

	i = 0;
	while (node->links[i] != -1)
		i++;
	links = malloc(sizeof(int) * (i + 2));
	i = -1;
	while (node->links[++i] != -1)
		links[i] = node->links[i];
	links[i++] = j;
	links[i] = -1;
	free(node->links);
	node->links = links;
}

int	link_nodes(t_node *nodes, t_lem *l, char *line)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	split = malloc(sizeof(char *) * 2);
	while (line[i] != '-')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (0);
	split[0] = ft_strsub(line, 0, i++);
	split[1] = ft_strsub(line, i, ft_strlen(line));
	i = 0;
	j = -1;
	while (i < l->rooms)
	{
		if (ft_strcmp(nodes[i].name, split[0]) == 0)
			while (++j < l->rooms)
				if (ft_strcmp(nodes[j].name, split[1]) == 0)
					add_link(&nodes[i], j);
		i++;
	}
	return ((i == l->rooms) ? 0 : 1);
}

t_node *create_nodes(t_lem *l)
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
	nodes = malloc(sizeof(t_node) * (i + 1));
	j = -1;
	while (++j < i)
		if (!(fill_nodes(nodes, l, j)))
			return (NULL);
	while (i < l->count)
		if (!(link_nodes(nodes, l, l->lines[i++])))
			return (NULL);
	return (nodes);
}

char	**build_info(int fd, t_lem *lem)
{
	char	*line;
	char	**lines;

	lem->count = 0;
	lem->start = -1;
	lem->end = -1;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp("##start", line) == 0)
			lem->start = lem->count;
		else if (ft_strcmp("##end", line) == 0)
			lem->end = lem->count;
		else if (line[0] == '#')
			continue ;
		else
		{
			lines = ft_add_charpointer(lines, line, lem->count);
			lem->count++;
		}
	}
	if (lem->end == -1 || lem->start == -1 || lem->start == lem->end)
		return (NULL);
	return (lines);
}

int	get_ants(int fd)
{
	char	*line;
	int		i;

	i = 0;
	if (get_next_line(fd, &line) != 1)
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (ft_atoi(line));
}

/*print_node(t_node *node)
{


}*/

int main(int ac, char **av)
{
	int		fd;
	t_node	*nodes;
	t_lem	lem;

	if (ac != 2)
		error_exit();
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || fd == 0)
		error_exit();
	if (!(lem.ants = get_ants(fd)))
		error_exit();
	if (!(lem.lines = build_info(fd, &lem)))
		error_exit();
	nodes = create_nodes(&lem);
}
