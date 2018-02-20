#include "vis.h"

void	error_exit(int a)
{
	if (a == 0)
		ft_putstr("ERROR\n");
	if (a == 1)
		ft_putstr("map too large\n");
	exit(1);
}

int	start_end(t_vis *v, char *line, int start)
{
	if (start)
		v->start = v->count;
	else
		v->end = v->count;
	free(line);
	return (1);
}

int main(int ac, char **av)
{
	t_vis	v;
	int	fd;

//	ft_printf("%C\n", L'😇');
	get_emo(&v);
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
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
