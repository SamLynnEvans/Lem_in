#include "vis.h"

void	error_exit(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

int	build_info(t_vis *v)
{
	char	*line;
	int		sa[2];

	sa[0] = 0;
	sa[1] = 0;
	v->count = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strcmp("##start", line) == 0)
		{
			sa[0]++;
			v->start = v->count;
		}
		else if (ft_strcmp("##end", line) == 0)
		{
			sa[1]++;
			v->end = v->count;
		}
		else if (line[0] != '#')
		{
			v->lines = ft_add_charpointer(v->lines, line, v->count);
			v->count++;
		}
	}
	return ((sa[0] != 1 || sa[1] != 1 || v->start == v->end) ? 0 : 1);
}

int	get_ants(void)
{
	char	*line;
	int		i;

	i = 0;
	if (get_next_line(0, &line) != 1)
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
	free(line);
	return (ft_atoi(line));
}

int main()
{
	t_vis	v;
	t_node *nodes;

	if (!(v.ants = get_ants()))
		error_exit();
	if (!(build_info(&v)))
		error_exit();
	if (!(nodes = create_nodes(&v)))
		error_exit();
	visualiser(nodes, &v);
}
