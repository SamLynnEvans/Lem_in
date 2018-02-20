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

void	set_emojis(char emojis[25][30])
{
	ft_strcpy(emojis[0], "emoji/glasses");
	ft_strcpy(emojis[1], "emoji/laugh");
	ft_strcpy(emojis[2], "emoji/angry");
	ft_strcpy(emojis[3], "emoji/cool");
	ft_strcpy(emojis[4], "emoji/cry");
	ft_strcpy(emojis[5], "emoji/mono");
	ft_strcpy(emojis[6], "emoji/tongue");
	ft_strcpy(emojis[7], "emoji/nuke");
	ft_strcpy(emojis[8], "emoji/injure");
	ft_strcpy(emojis[9], "emoji/robot");
	ft_strcpy(emojis[10], "emoji/rolling");
	ft_strcpy(emojis[11], "emoji/bull");
	ft_strcpy(emojis[12], "emoji/angel");
	ft_strcpy(emojis[13], "emoji/poo");
	ft_strcpy(emojis[14], "emoji/goofy");
	ft_strcpy(emojis[15], "emoji/start");
	ft_strcpy(emojis[16], "emoji/end");
}


t_emo	*get_emo(void)
{
	int	fd;
	int	i;
	int	j;
	t_emo *e;
	char **lines;
	char emojis[25][30];

	i = 0;
	set_emojis(emojis);
	e = malloc(sizeof(t_emo) * 17);
	while (i < 17)
	{
		fd = open(emojis[i], O_RDONLY);
		if (fd == -1)
			error_exit();
		lines = read_lines(fd, e + i);
		e[i].emoji = malloc(sizeof(int *) * e[i].y_max + 1);
		j = 0;
		while (j < e[i].y_max)
		{
			e[i].emoji[j] = str_to_intdata(lines[j], e[i].x_max);
			free(lines[j]);
			j++;
		}
		i++;
		free(lines);
	}
	return (e);
}
