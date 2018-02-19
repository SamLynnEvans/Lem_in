#include "vis.h"

void	print_emoji(char *data, int sl, t_emo *e, int pos)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (i < e->y_max)
	{
		j = 0;
		x = 0;
		while (j < e->x_max)
		{
			if (e->emoji[i][j] || e->emoji[i][j + 1] || e->emoji[i][j + 2])
			{
			data[pos + y *sl + x] =  e->emoji[i][j + 2];
			data[pos + y *sl + x + 2] =  e->emoji[i][j];
			data[pos + y *sl + x + 1] =  e->emoji[i][j + 1];
			}
			j+=8;
			x+=4;
		}
		y++;
		i += 2;
	}
}

char	**read_lines(int fd, t_emo *emo)
{
	char 	**lines;
	char	*line;
	int		i;

	i = 0;
	emo->y_max = 0;
	emo->x_max = 0;
	while (get_next_line(fd, &line) > 0)
	{
		lines = ft_add_charpointer(lines, line, emo->y_max);
		emo->y_max++;
	}
	i = 0;
	while (lines[0][i])
		{
			if (lines[0][i++] == ' ')
			emo->x_max++;
		}
	emo->x_max++;
	ft_intdebug(emo->x_max, "x");
	ft_intdebug(emo->y_max, "y");
	return (lines);
}

int	*str_to_intdata(char *str, int size)
{
	int *data;
	int	i;

	i = 0;
	data = malloc(sizeof(int) * size);
	while (*str)
	{
		if (ft_isdigit(*str) || (*str == '-' && ft_isdigit(*(str + 1))))
		{
			if (i > size)
				return (NULL);
			data[i++] = ft_atoi(str);
			while (ft_isdigit(*str) || *str == '-')
				str++;
		}
		else
			str++;
	}
	return (data);
}


t_emo	*get_emo(void)
{
	int	fd;
	int	i;
	t_emo *e;
	char **lines;

	i = 0;
	e = malloc(sizeof(t_emo));
	fd = open("emoji/test.txt", O_RDONLY);
	if (fd == -1)
		error_exit();
	lines = read_lines(fd, e);
	e->emoji = malloc(sizeof(int *) * e->y_max + 1);
	while (i < e->y_max)
	{
		e->emoji[i] = str_to_intdata(lines[i], e->x_max);
		i++;
	}
	return (e);
}
