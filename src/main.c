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

int main(int ac, char **av)
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
	if (!(lem.lines = build_info(fd, &lem)))
		error_exit();
	if (!(nodes = create_nodes(&lem)))
		error_exit();
	if (!(lem_in(nodes, &lem)))
		error_exit();
	print_paths(nodes, &lem);
	free_all(&lem, nodes);
}
