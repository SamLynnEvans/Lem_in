#include "lem_in.h"

int	start_end(t_lem *l, char *line, int start)
{
	if (start)
		l->start = l->count;
	else
		l->end = l->count;
	free(line);
	return (1);
}

int	build_info(int fd, t_lem *lem)
{
	char	*line;
	int		sa[2];

	sa[0] = 0;
	sa[1] = 0;
	lem->count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(ft_strcmp("##start", line)))
			sa[0] += start_end(lem, line, 1);
		else if (ft_strcmp("##end", line) == 0)
			sa[1] += start_end(lem, line, 0);
		else if (line[0] != '#')
		{
			lem->lines = ft_add_charpointer(lem->lines, line, lem->count);
			lem->count++;
		}
		else
			free(line);
	}
	return ((sa[0] != 1 || sa[1] != 1 || lem->start == lem->end) ? 0 : 1);
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
