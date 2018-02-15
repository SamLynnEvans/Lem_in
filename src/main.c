#include "lem_in.h"

void	error_exit(void)
{
	ft_putstr("ERROR\n");
	exit(1);
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

void print_node(t_node *node, int rooms)
{
	int i = 0;

	while (i < rooms)
	{
	ft_printf("name: %s\ndistance = %d\nstart = %d\nend = %d\n", node[i].name, node[i].distance, node[i].start, node[i].end);
//	if (node[i].start == 0)
//		ft_printf("parent = %s\n",  node[node[i].parent].name);
	ft_putstr ("links = ");
	int j = 0;
	while (node[i].links[j] != -1)
	{
		ft_putstr(node[node[i].links[j++]].name);
		ft_putchar(',');
	}
	ft_putchar('\n');
	ft_putchar('\n');
	i++;
	}
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
	if (!(nodes = create_nodes(&lem)))
		error_exit();
	if (!(lem_in(nodes, &lem)))
		error_exit();
	print_paths(nodes, &lem);
	free_all(&lem, nodes);
}
