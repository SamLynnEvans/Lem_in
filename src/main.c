#include "lem_in.h"

void	error_exit(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

char	**ft_add_charpointer(char**array, char *content, int count)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * (count + 1));
	i = -1;
	while (++i < count)
		ret[i] = array[i];
	ret[i] = content;
	if (count != 0)
		free(array);
	return (ret);
}

t_node **create_nodes(char **lines, int count)
{
	

}

t_node	**build_info(int fd)
{
	char	*line;
	char	**lines;
	int		count;

	count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		lines = ft_add_charpointer(lines, line, count);
		count++;
	}
	return (create_nodes(lines, count));
}

int main(int ac, char **av)
{
	int		fd;
	t_node	**nodes;

	if (ac != 2)
		error_exit();
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error_exit();
	nodes = build_info(fd);
}
