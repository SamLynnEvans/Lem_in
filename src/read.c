/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:30:33 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/03/07 12:47:51 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	start_end(t_lem *l, int start)
{
	if (start)
		l->start = l->count;
	else
		l->end = l->count;
	return (1);
}

int	build_info(int fd, t_lem *l)
{
	char	*line;
	int		sa[2];

	sa[0] = 0;
	sa[1] = 0;
	l->count = 0;
	l->maplines = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!(ft_strcmp("##start", line)))
			sa[0] += start_end(l, 1);
		else if (ft_strcmp("##end", line) == 0)
			sa[1] += start_end(l, 0);
		else if (line[0] != '#')
		{
			if (!(l->lines = ft_add_charpointer(l->lines, line, l->count)))
				return (0);
			l->count++;
		}
		l->map = ft_add_charpointer(l->map, line, l->maplines++);
	}
	return ((sa[0] != 1 || sa[1] != 1 || l->start == l->end) ? 0 : 1);
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
