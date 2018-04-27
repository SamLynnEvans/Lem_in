/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slynn-ev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 12:43:16 by slynn-ev          #+#    #+#             */
/*   Updated: 2018/04/27 12:36:42 by slynn-ev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

int		get_coords(char *str, int coords[2])
{
	long	n;
	int		i;

	i = 0;
	n = ft_atol(str);
	if (str[i] < '0' || str[i] > '9' || n > 50 || n < 0)
		return (0);
	coords[0] = (int)n;
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	n = ft_atol(str + i);
	if (str[i] < '0' || str[i] > '9' || n > 50 || n < 0)
		return (0);
	coords[1] = n;
	return (1);
}

int		start_end(t_vis *v, char *line, int start)
{
	if (start)
		v->start = v->count;
	else
		v->end = v->count;
	free(line);
	return (1);
}

int		build_info(t_vis *v, int fd)
{
	char	*line;
	int		sa[2];

	sa[0] = 0;
	sa[1] = 0;
	v->count = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp("##start", line) == 0)
			sa[0] += start_end(v, line, 1);
		else if (ft_strcmp("##end", line) == 0)
			sa[1] += start_end(v, line, 0);
		else if (line[0] == '\0')
			break ;
		else if (line[0] != '#')
		{
			v->lines = ft_add_charpointer(v->lines, line, v->count);
			v->count++;
		}
		else
			free(line);
	}
	free(line);
	return ((sa[0] != 1 || sa[1] != 1 || v->start == v->end) ? 0 : 1);
}

int		get_ants(int fd)
{
	char	*line;
	int		i;
	long	num;

	i = 0;
	if (get_next_line(fd, &line) != 1)
		return (0);
	while (line[0] == '#')
	{
		if (get_next_line(fd, &line) <= 0)
			return (0);
		free(line);
	}
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	num = ft_atol(line);
	if ((num = ft_atol(line)) > INT_MAX || num <= 0)
		return (0);
	return ((int)(num));
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
