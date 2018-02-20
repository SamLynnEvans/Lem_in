#include "vis.h"

void	error_exit(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

int	build_info(t_vis *v, int fd)
{
	char	*line;
	int		sa[2];

	sa[0] = 0;
	sa[1] = 0;
	v->count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp("##start", line) == 0)
		{
			sa[0]++;
			v->start = v->count;
			free(line);
		}
		else if (ft_strcmp("##end", line) == 0)
		{
			sa[1]++;
			v->end = v->count;
			free(line);
		}
		else if (line[0] == '\0')
		{
			free(line);
			break ;
		}
		else if (line[0] != '#')
		{
			v->lines = ft_add_charpointer(v->lines, line, v->count);
			v->count++;
		}
		else
			free(line);
	}
	return ((sa[0] != 1 || sa[1] != 1 || v->start == v->end) ? 0 : 1);
}

int	get_ants(int fd)
{
	char	*line;
	int		i;

	i = 0;
	if (get_next_line(fd, &line) != 1)
	{
		free(line);
		return (0);
	}
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
	{
		free(line);
		return (0);
	}
	i = ft_atoi(line);
	free(line);
	return (i);
}

char	**get_moves(int fd, t_vis *v)
{
	char	**moves;
	char	*line;

	v->mv_count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		moves = ft_add_charpointer(moves, line, v->mv_count);
		v->mv_count++;
	}
	return (moves);
}

int main(int ac, char **av)
{
	t_vis	v;
	int	fd;

	ft_printf("%C\n", L'😇');
	v.e = get_emo();
	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	else
		fd = 0;
	if (!(v.ants = get_ants(fd)))
		error_exit();
	if (!(build_info(&v, fd)))
		error_exit();
	ft_putstr("entered");
	if (!(v.n = create_nodes(&v)))
		error_exit();
	if (!(v.moves = get_moves(fd, &v)))
		error_exit();
	visualiser(&v);
}
